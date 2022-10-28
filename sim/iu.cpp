// iu.cpp
//   by Derek Chiou
//      March 4, 2007
// 

// STUDENTS: YOU ARE EXPECTED TO MAKE MOST OF YOUR MODIFICATIONS IN THIS FILE.
// for 382N-10

#include "types.h"
#include "helpers.h"
#include "my_fifo.h"
#include "cache.h"
#include "iu.h"

/**
 * Initialize Intersection Unit with the node
 *
 * @param __node Node ID
 */
iu_t::iu_t(int __node) {
    node = __node;
    for (int i = 0; i < MEM_SIZE; ++i)
        for (int j = 0; j < CACHE_LINE_SIZE; ++j)
            mem[i][j] = 0;
}

/**
 * Bind cache and network
 *
 * @param c Cache
 * @param n Network
 */
void iu_t::bind(cache_t *c, network_t *n) {
    cache = c;
    net = n;
}

/**
 * Simulate one cycle of Intersection Unit
 *
 * IU can only execute one request per cycle
 * The priority is REPLY > REQUEST > PROC.
 *
 * TODO: New priority: REPLY > WRITEBACK > FORWARD > REQUEST > PROC; SEND_REPLY > SEND_FORWARD
 */
void iu_t::advance_one_cycle() {
    // fixed priority: reply from network
    if (net->from_net_p(node, REPLY)) {
        process_net_reply(net->from_net(node, REPLY));
        NOTE_ARGS("node #%d processes a %s\n", node, "REPLY");

    } else if (net->from_net_p(node, WRITEBACK)) {
        process_net_writeback(net->from_net(node, WRITEBACK));
        NOTE_ARGS("node #%d proceses a %s\n", node, "WRITEBACK");

    } else if (net->from_net_p(node, FORWARD)) {
        process_net_forward(net->from_net(node, FORWARD));
        NOTE_ARGS("node #%d processes a %s\n", node, "FORWARD");

    } else if (net->from_net_p(node, REQUEST)) {
        process_net_request(net->from_net(node, REQUEST));
        NOTE_ARGS("node #%d processes a %s\n", node, "REQUEST");

    } else if (proc_cmd_p && !proc_cmd_processed_p) {
        // TODO: proc_cmd_processed_p depends on whether the network request is submitted successfully
        proc_cmd_processed_p = true;
        process_proc_request(proc_cmd);
    }
}

// processor side

// this interface method only takes and buffers a request from the
// processor.
/**
 * Register command from processor
 *
 * @param pc Processor command
 * @return Boolean value for whether there is one command registered.
 */
bool iu_t::from_proc(proc_cmd_t pc) {
    if (!proc_cmd_p) {
        proc_cmd_p = true;
        proc_cmd = pc;

        proc_cmd_processed_p = false;
        return (false);
    } else {
        return (true);
    }
}

/**
 * Deal with process request
 *
 * Two parts:
 *  1. Local access
 *      * Three operations: READ, Write, Invalidate
 *      * local access is determined by getting the node from address
 *  2. Global access
 *      * Send request through network (to_net method)
 *
 * Processor request
 *  1. Cache read miss
 *      * Local memory access
 *          -x If it is owned by other nodes, then it needs to downgrade the owner node, get the newest copy, and update owner
 *          x If it is shared with other nodes, update sharer list
 *          x If it is the only copy, then change request state to exclusive state and setup sharer list (not initial shared state)
 *      * Global memory access
 *          - Send request through network (read request)
 *  2. Cache write miss
 *      * Local memory access
 *          -x If it is owned by other nodes, then it needs to downgrade owner node to invalidate, get the newest copy, and update owner
 *          -x If it is shared by other nodes, then it needs to invalidate all the sharers, wait for all acknowledgement, and update sharer list
 *          x If it is the only copy, setup owner
 *      * Global memory access
 *          - send request through network (write request)
 *  3. Replacement write back (modified/exclusive state)
 *      * Local memory access
 *          - Copy the data into memory and change directory state to be Invalid
 *      * Global memory access
 *          - send request through network (invalidate request, need to downgrade the directory state)
 *          - Buffer the data into victim buffer
 *  4. Replacement write back (shared state)
 *      * Local memory access
 *          - Update sharer list
 *      * Global memory access
 *          - send request through network (invalidate request, need to update the sharer list)
 *
 * @param pc Processor command
 * @return Success or not (???)
 */
bool iu_t::process_proc_request(proc_cmd_t pc) {
    int dest = gen_node(pc.addr);
    int lcl = gen_local_cache_line(pc.addr);

    NOTE_ARGS(("%d: addr = %d, dest = %d", node, pc.addr, dest));

    if (dest == node) { // local

        ++local_accesses;

        switch (pc.busop) {
            case READ:
                // Read from memory
                if (dir[lcl].state == DIR_INVALID) {
                    // first time request, change cache state to exclusive and setup sharer list
                    dir[lcl].shared_nodes = (1 << node);
                    dir[lcl].owner = node;

                    copy_cache_line(pc.data, mem[lcl]);
                    pc.permit_tag = EXCLUSIVE;

                    cache->reply(pc);
                    proc_cmd_p = false; // clear proc_cmd

                } else if (dir[lcl].state == DIR_SHARED) {
                    // If it is shared with other nodes, update sharer list
                    dir[lcl].shared_nodes |= (1 << node);

                    copy_cache_line(pc.data, mem[lcl]);
                    pc.permit_tag = SHARED;

                    cache->reply(pc);
                    proc_cmd_p = false; // clear proc_cmd
                } else if (dir[lcl].state == DIR_OWNED) {
                    // If it is owned by other nodes, it needs to generate a net_cmd and forward the proc_cmd
                    if (dir[lcl].owner == node) {
                        ERROR("should not see this proc request, the node is already the owner");
                    }

                    net_cmd_t net_cmd;
                    net_cmd.src = node;
                    net_cmd.dest = dir[lcl].owner;
                    net_cmd.proc_cmd = pc;

                    bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                    if (enqueue_status) {
                        proc_cmd_p = false; // clear proc_cmd if successfully enqueued
                    }
                    // no cache reply for now
                    // owner won't be changed for now

                } else {
                    ERROR("invalid directory state seen at node %d\n", node);
                }
                break;

            case WRITE:
                // Write to memory
                if (dir[lcl].state == DIR_INVALID) {
                    // first time request, change cache state to modified and setup owner
                    dir[lcl].shared_nodes = (1 << node);
                    dir[lcl].owner = node;
                    pc.permit_tag = MODIFIED;

                    cache->reply(pc);
                    proc_cmd_p = false; // clear proc_cmd
                } else if (dir[lcl].state == DIR_SHARED) {
                    // If it is shared with other nodes, send invalidates to all sharers

                    if (dir[lcl].shared_nodes == 0) {
                        ERROR("sharer list should not be zero");
                    } else if (check_onehot(dir[lcl].shared_nodes)) {
                        ERROR("should have at least two sharers");
                    }

                    for (int i_node = 0; i_node < 32; i++) {
                        if ((dir[lcl].shared_nodes >> i_node) & 0x1) {
                            if (i_node != node) {
                                // don't send invalidates to the requestor if it is in the sharer list
                                net_cmd_t net_cmd;
                                net_cmd.src = node;
                                net_cmd.dest = i_node;
                                net_cmd.proc_cmd = pc;

                                to_net_req_q.push(net_cmd);
                                // enqueue to the local to_net_req_q rather than directly send to the network                             
                            }
                        }
                    }

                    proc_cmd_p = false; // clear proc_cmd

                    // sharer list won't be updated for now
                    // dir state won't be updated to OWNED for now
                    // the requestor won't be the owner for now 
                    // no cache reply for now 
                } else if (dir[lcl].state == DIR_OWNED) {
                    // If it is owned by other nodes, generate network request to invalidate the old owner
                    // get the newest copy, and update owner
                    if (dir[lcl].owner == node) {
                        ERROR("should not see this proc request, the node is already the owner");
                    }

                    net_cmd_t net_cmd;
                    net_cmd.src = node;
                    net_cmd.dest = dir[lcl].owner;
                    net_cmd.proc_cmd = pc;

                    to_net_req_q.push(net_cmd);
                    // enqueue to the local to_net_req_q rather than directly send to the network 

                    proc_cmd_p = false; // clear proc_cmd
                    // sharer list won't be updated for now
                    // dir state won't be updated to OWNED for now
                    // the requestor won't be the owner for now 
                    // no cache reply for now                
                } else {
                    ERROR("invalid directory state seen at node %d\n", node);
                }

                break;

            case INVALIDATE:
                // replacement
                // no cache reply generated
                if (dir[lcl].state == DIR_SHARED) {
                    // shared: update sharer list
                    uint temp = ~(1 << node);
                    dir[lcl].shared_nodes &= temp;

                } else if (dir[lcl].state == DIR_OWNED) {
                    // owned: copy the data into memory and change directory state to be Invalid
                    if (dir[lcl].owner != node) {
                        ERROR("Non-owner write-back: owner %d, node %d\n", dir[lcl].owner, node);
                    }
                    copy_cache_line(mem[lcl], pc.data);
                    dir[lcl].state = DIR_INVALID;

                } else {
                    ERROR("Invalid write-back request from node %d\n", dest);
                }
                break;
        }

    } else { // global
        ++global_accesses;

        net_cmd_t net_cmd;
        net_cmd.src = node;
        net_cmd.dest = dest;
        net_cmd.proc_cmd = pc;
                
        to_net_req_q.push(net_cmd); 
        // enqueue to the local to_net_req_q rather than directly send to the network 

        to_net_req_q.push(net_cmd);
        // enqueue to the local to_net_req_q rather than directly send to the network 

        proc_cmd_p = false; // clear proc_cmd
        // no cache reply for now 
    }
}


// receive a net request
/**
 * Process requests from network (Other nodes)
 *
 * Network request
 *  1. Read request (Not forwarded request)
 *      * This cache block is Shared
 *          - Return the data in the memory and update sharer list
 *      * This cache block is Shared-no-data
 *          - Forward request to the owner
 *      * This cache block is Modified
 *          - If the owner is current node, access the cache to get the newest copy, downgrade the cache state,
 *            change the directory state to be Shared, and update sharer list.
 *          - If the owner is other nodes, change state to be Shared-no-data, and forward the request to the owner
 *      * This cache block is Invalid
 *          - Change state to modified state, setup owner, and return data with exclusive
 *
 *  2. Read request (forwarded request)
 *      * Access the cache
 *          - If cache miss,
 *              + If it is in victim buffer, return data to the source
 *              + else, return non-ack response to the source
 *          - If cache hit
 *              + If cache block is modified/exclusive, return data directly to directory (Update sharer list) and source (Downgrade to shared)
 *              + If cache block is shared, return data to the source
 *
 *  3. Write request (Not forwarded request)
 *      * This cache block is Shared
 *          - If the permitted tag is Modified:
 *              + Change the block to be Modified state
 *              + Send invalidation requests until all the sharers acknowledge (Push requests into the queue)
 *                  TODO: If request queue is not enough, What should do to avoid deadlock?
 *                        One possible solution is add one internal request queue and buffer the request temporarily
 *                        If the buffer is full, and invalidation queue is still not enough, non-ack response is sent
 *              + Send acknowledge back to source node
 *          - If the permitted tag is Shared:
 *              + Update sharer list (Change 1 to 0)
 *      * This cache block is Modified
 *          - If the owner is request node, write data (Exclusive do not need this), and change state to be Invalid
 *              + Return ack to the requestor
 *          - If the owner is other nodes
 *              + If there are sharers
 *                  # If the requestor is one of sharers, return non-ack response
 *                  # If the requestor is not one of sharers, forward the request to the owner
 *              + If there aren't sharers, forward the request to the owner
 *      * This cache block is Shared-no-data
 *          - If the dest is current node, Copy data to the directory and change to Invalid state
 *          - Else, return non-ack response
 *      * This cache block is Invalid
 *          - Change state to modified state, setup owner, and return data with exclusive
 *
 *  4. Write request (forwarded request)
 *      * Access the cache
 *          - If cache miss,
 *              + If it is in victim buffer, return data to the source
 *              + else, return non-ack response to the source
 *          - If cache hit, return data directly to the source (Downgrade to Invalid) and send ack to directory
 *
 *  5. Invalidation request
 *      * No directory access
 *      * Modify cache state and return ack response (No matter whether it hit or not)
 *
 *  TODO: New queue on network (Forward Queue) / New internal queue (Send-Forward Queue and Send-reply Queue)
 *
 * @param net_cmd Network command
 * @return Success or not
 */
bool iu_t::process_net_request(net_cmd_t net_cmd) {
    proc_cmd_t pc = net_cmd.proc_cmd;

    int lcl = gen_local_cache_line(pc.addr);
    int src = net_cmd.src;
    int dest = net_cmd.dest;

    // ***** FYTD *****
    // sanity check
    // TODO: Forward request don't need this line
    if (gen_node(pc.addr) != node) ERROR("sent to wrong home site!");

    switch (pc.busop) {
        case READ: // assume local
            // TODO: Transient state change in directory
            // TODO: Probe cache line
            net_cmd.dest = src;
            net_cmd.src = dest;
            copy_cache_line(pc.data, mem[lcl]);
            net_cmd.proc_cmd = pc;


            return (net->to_net(node, REPLY, net_cmd));

        case WRITE:
            // TODO: Reply with write acknowledge
            copy_cache_line(mem[lcl], pc.data);
            return (false);

        case INVALIDATE:
            // ***** FYTD *****
            // TODO: Invalidation from other nodes (Reply with invalidation acknowledge)
            return (false);  // need to return something for now
    }
}

/**
 * Process reply from network (Other nodes)
 *
 * Network request (Based on different bus tag)
 *  1. Invalidation request ack
 *      * Update sharer list (1 -> 0)
 *  2. Read request ack (Not forwarded request)
 *      * Fill cache (may trigger replacement write back)
 *      * End the processor command processing signal
 *  3. Invalidation request non-ack (Impossible)
 *      * Retry
 *  4. Write request ack (Not forwarded request)
 *      * Write back
 *          - Evict the victim
 *      * Not Write back
 *          - Fill cache (may trigger replacement write back)
 *          - End the processor command processing signal
 *  5. Read request non-ack
 *      * Retry (Need proc do again)
 *  6. Write request non-ack
 *      * Retry (Need proc do again)
 *  7. Write request ack (forwarded request)
 *      * Update owner id
 *  8. Read request ack (forwarded request)
 *      * Fill memory
 *      * Change state from Shared-no-data/Invalid to Shared and update sharer list
 *
 * @param net_cmd Network command
 * @return Success or not
 */
bool iu_t::process_net_reply(net_cmd_t net_cmd) {
    proc_cmd_t pc = net_cmd.proc_cmd;

    // ***** FYTD *****

    // TODO: Cannot finish processor request in one reply (Sharers invalidation)
    proc_cmd_p = false; // clear out request that this reply is a reply to

    // TODO: Support retry based on reply (proc_cmd_processed_p = false)
    switch (pc.busop) {
        case READ: // assume local
            // Deal with read request
            // TODO: Transient state change in directory
            cache->reply(pc);
            return (false);

        case WRITE:
        case INVALIDATE:
            // TODO: Invalidation or write acknowledge
            // TODO: Transient state change in directory
        ERROR("should not have gotten a reply back from a write or an invalidate, since we are incoherent");
            return (false);  // need to return something for now
    }
}

void iu_t::print_stats() {
    printf("------------------------------\n");
    printf("%d: iu\n", node);

    printf("num local  accesses = %d\n", local_accesses);
    printf("num global accesses = %d\n", global_accesses);
}

dir_t iu_t::get_dir_entry(int index) {
    return dir[index];
}

void iu_t::set_mem(int addr, const data_t data) {
    for (int i = 0; i < CACHE_LINE_SIZE; ++i) mem[addr][i] = data[i];
}
