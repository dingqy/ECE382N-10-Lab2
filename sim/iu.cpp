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

    // init inv queue
    to_net_inv_q.init(SIZE_INV_QUEUE);

    // init to_net buffer
    net_cmd_t empty;
    empty.valid_p = false;
    for (int ind = 0; ind < SIZE_IU_TO_NET_BUFFER; ind++) {
        net_buffer[ind].net_cmd = empty;
        net_buffer[ind].valid = false;
    }

    // init dir
    for (int i = 0; i < MEM_SIZE; ++i) {
        dir[i].state = DIR_INVALID;
        dir[i].shared_nodes = 0;
    }
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
    // clear pending buffers to queues
    bool skip_cycle = false;
    for (int ind = 0; ind < SIZE_IU_TO_NET_BUFFER; ind++) {
        if (net_buffer[ind].valid) {
            // invalidate the buffered reqest
            bool enqueue_status = false;

            switch (net_buffer[ind].pri) {
                case (REPLY):
                    enqueue_status = net->to_net(node, REPLY, net_buffer[ind].net_cmd);
                    if (enqueue_status) net_buffer[ind].valid = 0;
                    break;
                case (WRBACK): {
                    enqueue_status = net->to_net(node, WRBACK, net_buffer[ind].net_cmd);
                    if (enqueue_status) net_buffer[ind].valid = 0;
                    break;
                }
                case (FORWARD): {
                    enqueue_status = net->to_net(node, FORWARD, net_buffer[ind].net_cmd);
                    if (enqueue_status) net_buffer[ind].valid = 0;
                    break;
                }
                case (REQUEST): {
                    enqueue_status = net->to_net(node, REQUEST, net_buffer[ind].net_cmd);
                    if (enqueue_status) net_buffer[ind].valid = 0;
                    break;
                }
            }
            if (enqueue_status) {
                // one request each cycle
                skip_cycle = true;
                break;
            }
        }
    }

    if (!skip_cycle) {
        // fixed priority: reply from network
        if (net->from_net_p(node, REPLY)) {
            process_net_reply(net->from_net(node, REPLY));
            NOTE_ARGS(("node #%d processes a %s\n", node, "REPLY"));

        } else if (net->from_net_p(node, WRBACK)) {
            process_net_writeback(net->from_net(node, WRBACK));
            NOTE_ARGS(("node #%d proceses a %s\n", node, "WRBACK"));

        } else if (net->from_net_p(node, FORWARD)) {
            process_net_forward(net->from_net(node, FORWARD));
            NOTE_ARGS(("node #%d processes a %s\n", node, "FORWARD"));

        } else if (net->from_net_p(node, REQUEST)) {
            process_net_request(net->from_net(node, REQUEST));
            NOTE_ARGS(("node #%d processes a %s\n", node, "REQUEST"));

        } else if (!to_net_inv_q.empty()) {
            net_cmd_t inv_net_cmd = to_net_inv_q.dequeue();
            bool enqueue_status = net->to_net(node, REQUEST, inv_net_cmd);
            if (!enqueue_status) {
                to_net_inv_q.push_front(inv_net_cmd);
            } else {
                NOTE_ARGS(("node #%d processes a %s from the inv queue\n", node, "REQUEST"));
            }

        } else if (proc_cmd_p && !proc_cmd_processed_p) {
            proc_cmd_processed_p = true;    // do not process the same proc cmd repeatedly
            // will be reset to false if retry needed
            process_proc_request(proc_cmd);
        }
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
    if (!forward_cmd_p) {
        if (!proc_cmd_p) {
            proc_cmd_p = true;
            proc_cmd = pc;

            proc_cmd_processed_p = false;
            return (false); // cannot accept a new proc cmd
        } else {
            return (true); // can accept a new proc cmd
        }
    } else {
        forward_cmd_p = false;
        forward_net_cmd = pc;
        return false;
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
 *          x If it is owned by other nodes, then it needs to downgrade the owner node, get the newest copy, and update owner
 *          x If it is shared with other nodes, update sharer list
 *          x If it is the only copy, then change request state to exclusive state and setup sharer list (not initial shared state)
 *      * Global memory access
 *          x Send request through network (read request)
 *  2. Cache write miss
 *      * Local memory access
 *          x If it is owned by other nodes, then it needs to downgrade owner node to invalidate, get the newest copy, and update owner
 *          -x If it is shared by other nodes, then it needs to invalidate all the sharers, wait for all acknowledgement, and update sharer list
 *          x If it is the only copy, setup owner
 *      * Global memory access
 *          x send request through network (write request)
 *  3. Replacement write back (modified/exclusive state)
 *      * Local memory access
 *          -x Copy the data into memory and change directory state to be Invalid
 *      * Global memory access
 *          -x send request through network (invalidate request, need to downgrade the directory state)
 *          - Buffer the data into victim buffer
 *  4. Replacement write back (shared state)
 *      * Local memory access
 *          x Update sharer list
 *      * Global memory access
 *          -x send request through network (invalidate request, need to update the sharer list)
 *
 * @param pc Processor command
 * @return Success or not (???)
 */
bool iu_t::process_proc_request(proc_cmd_t pc) {
    int dest = gen_node(pc.addr);
    int lcl = gen_local_cache_line(pc.addr);

    NOTE_ARGS(("%d: addr = %d, dest = %d", node, pc.addr, dest));

    proc_cmd_processed_p = true; // it has been processed, but the cmd is not cleared yet

    if (dest == node) { // local

        ++local_accesses;

        switch (pc.busop) {
            case READ:
                if (pc.permit_tag == SHARED) {
                    // BUS READ
                    if (dir[lcl].state == DIR_INVALID) {
                        // first time request, change cache state to exclusive and setup sharer list
                        dir[lcl].shared_nodes = (1 << node);
                        dir[lcl].owner = node;
                        dir[lcl].state = DIR_OWNED;

                        copy_cache_line(pc.data, mem[lcl]);
                        pc.permit_tag = EXCLUSIVE;

                        proc_cmd_p = false; // clear proc_cmd
                        cache->reply(pc);

                    } else if (dir[lcl].state == DIR_SHARED) {
                        // If it is shared with other nodes, update sharer list
                        dir[lcl].shared_nodes |= (1 << node);

                        copy_cache_line(pc.data, mem[lcl]);
                        pc.permit_tag = SHARED;

                        proc_cmd_p = false; // clear proc_cmd
                        cache->reply(pc);

                    } else if (dir[lcl].state == DIR_OWNED) {
                        // If it is owned by other nodes, it needs to generate a net_cmd and forward the proc_cmd
                        if (dir[lcl].owner == node) {
                            ERROR("should not see this proc request, the node is already the owner");
                        } else if (dir[lcl].shared_nodes != (1 << dir[lcl].owner)) {
                            NOTE_ARGS(("Waiting for Inv-ack to come back, dir %d, requestor %d", node, node));
                            // let the processor retry
                            proc_cmd_processed_p = false;
                        } else {

                            net_cmd_t net_cmd;
                            net_cmd.src = node;
                            net_cmd.dest = dir[lcl].owner;
                            net_cmd.proc_cmd = pc;
                            net_cmd.valid_p = 1;

                            bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                            if (!enqueue_status) {
                                // FORWARD queue is full
                                to_buffer(FORWARD, net_cmd);
                            }

                            // temporarily set dir state to DIR_SHARED_NO_DATA
                            // in case write requests come and we need to send invalidates
                            dir[lcl].state = DIR_SHARED_NO_DATA;

                            // no cache reply for now
                            // don't clear proc_cmd for now
                            // dir state won't be SHARED for now
                        }

                    } else if (dir[lcl].state == DIR_SHARED_NO_DATA) {
                        // Forward request to the owner
                        // the src remains the same, the dest changes to the actural owner
                        net_cmd_t net_cmd;
                        net_cmd.src = node;
                        net_cmd.dest = dir[lcl].owner;
                        net_cmd.proc_cmd = pc;
                        net_cmd.proc_cmd.busop = READ;
                        net_cmd.valid_p = 1;

                        bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                        if (!enqueue_status) {
                            // FORWARD queue is full
                            to_buffer(FORWARD, net_cmd);
                        }
                    } else {
                        ERROR_ARGS(("invalid directory state seen at node %d\n", node));
                    }
                } else if (pc.permit_tag == MODIFIED) {
                    // BUS RWITM
                    if (dir[lcl].state == DIR_INVALID) {

                        // first time request, change cache state to modified and setup owner
                        dir[lcl].shared_nodes = (1 << node);
                        dir[lcl].owner = node;
                        dir[lcl].state = DIR_OWNED;
                        copy_cache_line(pc.data, mem[lcl]);

                        proc_cmd_p = false; // clear proc_cmd
                        cache->reply(pc);

                    } else if (dir[lcl].state == DIR_SHARED) {

                        // If it is shared with other nodes, send invalidates to all sharers
                        if (dir[lcl].shared_nodes == 0) {
                            ERROR("sharer list should not be zero");
                        } else if (check_onehot(dir[lcl].shared_nodes)) {
                            ERROR("should have at least two sharers");
                        }

                        if (to_net_inv_q.space() < count_bits(dir[lcl].shared_nodes)) {
                            // let the processor retry
                            proc_cmd_processed_p = false;

                        } else {
                            // send out invalidates
                            dir[lcl].state = DIR_OWNED;
                            dir[lcl].owner = node;
                            dir[lcl].shared_nodes |= (1 << node);

                            for (int i_node = 0; i_node < 32; i_node++) {
                                if ((dir[lcl].shared_nodes >> i_node) & 0x1) {
                                    if (i_node != node) {
                                        // don't send invalidates to the requestor if it is in the sharer list
                                        net_cmd_t net_cmd;
                                        net_cmd.src = node;
                                        net_cmd.dest = i_node;
                                        net_cmd.proc_cmd = pc;
                                        net_cmd.proc_cmd.busop = INVALIDATE;
                                        net_cmd.valid_p = 1;

                                        // enqueue to the local queue if net queue is full, for invalidations
                                        bool enqueue_status = net->to_net(node, REQUEST, net_cmd);
                                        if (!enqueue_status) {
                                            to_net_inv_q.push_back(net_cmd);
                                        }
                                    }
                                }
                            }
                            // sharer list won't be updated for now
                            // reply to the cache
                            copy_cache_line(pc.data, mem[lcl]);
                            proc_cmd_p = false; // clear proc_cmd
                            cache->reply(pc);
                        
                        }

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
                        net_cmd.valid_p = 1;

                        bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                        if (!enqueue_status) {
                            // REQUEST queue is full
                            to_buffer(FORWARD, net_cmd);
                        }

                        // the requestor won't be the owner for now 
                        // no cache reply for now
                        // don't clear proc_cmd for now    

                    } else if (dir[lcl].state == DIR_SHARED_NO_DATA) {
                        // let the processor retry
                        proc_cmd_processed_p = false;
                    } else {
                        ERROR_ARGS(("invalid directory state seen at node %d\n", node));
                    }
                } else {
                    ERROR_ARGS(
                            ("Invalid bus op %d with permit tag %d seen at node %d\n", pc.busop, pc.permit_tag, node));
                }
                break;

            case WRITE:
                // writeback/evict
                // no cache reply generated
                if (dir[lcl].state == DIR_SHARED) {
                    // shared: update sharer list
                    uint temp = ~(1 << node);
                    dir[lcl].shared_nodes &= temp;

                } else if (dir[lcl].state == DIR_OWNED) {
                    // owned: copy the data into memory and change directory state to be Invalid
                    if (dir[lcl].owner != node) {
                        ERROR_ARGS(("Non-owner write-back: owner %d, node %d\n", dir[lcl].owner, node));
                    }
                    copy_cache_line(mem[lcl], pc.data);
                    dir[lcl].state = DIR_INVALID;
                    dir[lcl].shared_nodes = 0;

                } else {
                    ERROR_ARGS(("Invalid write-back request from node %d\n", node));
                }
                proc_cmd_p = false;
                break;

            case INVALIDATE: ERROR_ARGS(("Self INVALIDATE from node %d\n", node));
                break;
        }

    } else { // global
        ++global_accesses;

        net_cmd_t net_cmd;
        net_cmd.src = node;
        net_cmd.dest = dest;
        net_cmd.proc_cmd = pc;
        net_cmd.valid_p = 1;

        if (pc.busop == WRITE) {
            bool enqueue_status = net->to_net(node, WRBACK, net_cmd);
            if (!enqueue_status) {
                // WRBACK queue is full
                to_buffer(WRBACK, net_cmd);
            }
        } else {
            bool enqueue_status = net->to_net(node, REQUEST, net_cmd);
            if (!enqueue_status) {
                // REQUEST queue is full
                to_buffer(REQUEST, net_cmd);
            }
        }

        // no cache reply
    }
}


// receive a net request
/**
 * Process requests from network (Other nodes)
 *
 * Network request
 *  1. Read request (Not forwarded request)
 *      x This cache block is Shared
 *          x Return the data in the memory and update sharer list
 *      x This cache block is Shared-no-data
 *          - Forward request to the owner
 *      x This cache block is Owned
 *          - If the owner is current node, access the cache to get the newest copy, downgrade the cache state,
 *            change the directory state to be Shared, and update sharer list.
 *          - If the owner is other nodes, change state to be Shared-no-data, update the sharer list, and forward the request to the owner
 *      x This cache block is Invalid
 *          - Change state to owned state, setup owner, and return data with exclusive
 *
 *  2. Read request (forwarded request)
 *      x Access the cache
 *          - If cache miss,
 *              + If it is in victim buffer, return data to the source
 *              + else, return non-ack response to the source
 *          - If cache hit
 *              + If cache block is modified/exclusive, return data directly to directory (Update sharer list) and source
 *              + If cache block is shared, return data to the source and the dir (shared-no-data to shared)
 *
 *  3. Write request (Not forwarded request)
 *      x This cache block is Shared
 *          - If the permitted tag is Modified:
 *              + Change the block to be Modified state
 *              + Send invalidation requests until all the sharers acknowledge (Push requests into the queue)
 *                  TODO: If request queue is not enough, What should do to avoid deadlock?
 *                        One possible solution is add one internal request queue and buffer the request temporarily
 *                        If the buffer is full, and invalidation queue is still not enough, non-ack response is sent
 *              + Send acknowledge back to source node
 *          o If the permitted tag is Shared:
 *              + Update sharer list (Change 1 to 0)
 *      x This cache block is Modified
 *          o If the owner is request node, write data (Exclusive do not need this), and change state to be Invalid
 *              + Return ack to the requestor 
 *          - If the owner is other nodes
 *              + If the requestor is one of sharers, return non-ack response
 *              + If the requestor is not one of sharers or there aren't sharers, forward the request to the owner
 *      x This cache block is Shared-no-data
 *          - Return non-ack response
 *      x This cache block is Invalid
 *          - Change state to modified state, setup owner, and return data with exclusive
 *
 *  4. Write request (forwarded request)
 *      x Access the cache
 *          - If cache miss,
 *              + If it is in victim buffer, return data to the source
 *              + else, return non-ack response to the source
 *          - If cache hit, return data directly to the source (Downgrade to Invalid) and send ack to directory
 *
 *  5. Invalidation request
 *      x No directory access
 *      x Modify cache state and return ack response (No matter whether it hit or not)
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

    NOTE_ARGS(("Node #%d: pc.busop %d, dir state %d", node, pc.busop, dir[lcl].state));

    if (gen_node(pc.addr) == node) {
        /* not forwarded requests
            - depending on dir[lcl] states        
        */
        switch (pc.busop) {
            case READ:
                if (pc.permit_tag == SHARED) {
                    // BUS READ
                    if (dir[lcl].state == DIR_SHARED) {
                        // Return the data in the memory and update sharer list
                        dir[lcl].shared_nodes |= (1 << src);

                        net_cmd.dest = src;
                        copy_cache_line(pc.data, mem[lcl]);
                        net_cmd.proc_cmd = pc;
                        net_cmd.valid_p = 1;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }

                    } else if (dir[lcl].state == DIR_SHARED_NO_DATA) {
                        // Forward request to the owner
                        // the src remains the same, the dest changes to the actural owner
                        net_cmd.dest = dir[lcl].owner;

                        bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                        if (!enqueue_status) {
                            // FORWARD queue is full
                            to_buffer(FORWARD, net_cmd);
                        }

                    } else if (dir[lcl].state == DIR_OWNED) {
                        if (dir[lcl].shared_nodes != (1 << dir[lcl].owner)) {
                            NOTE_ARGS(("Waiting for Inv-ack to come back, dir %d, requestor %d", node, src));
                            // send back no-ack to src
                            net_cmd.valid_p = 0;
                            net_cmd.dest = src;

                            bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                            if (!enqueue_status) {
                                // REPLY queue is full
                                to_buffer(REPLY, net_cmd);
                            }
                        } else if (node == dir[lcl].owner) {
                            // If the owner is current node, 
                            // access the cache to get the newest copy, downgrade the cache state,
                            // change the directory state to be Shared, and update sharer list.

                            forward_cmd_p = true;
                            response_t r = cache->snoop(net_cmd);
                            // can't return the data back for now
                            // have to access cache for data
                            forward_cmd_p = false;

                            if (!r.hit_p) {
                                ERROR_ARGS(("The owner %d lost the cache line for addr %d\n", node, pc.addr));
                            }

                            dir[lcl].state = DIR_SHARED;
                            dir[lcl].shared_nodes |= (1 << src);

                            copy_cache_line(pc.data, forward_net_cmd.data);
                            pc.permit_tag = SHARED;
                            pc.busop = WRITE;
                            net_cmd.proc_cmd = pc;

                            net_cmd.dest = src; // reply to the requestor with data

                            bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                            if (!enqueue_status) {
                                // REPLY queue is full
                                to_buffer(REPLY, net_cmd);
                            }

                            // reply to the dir with data
                            // if dir is not the requestor
                            if (gen_node(pc.addr) != src) {
                                net_cmd.dest = gen_node(pc.addr);
                                to_buffer(REPLY, net_cmd);
                            }

                        } else {
                            // If the owner is other nodes, 
                            // change state to be Shared-no-data, 
                            // update the sharer list, and forward the request to the owner

                            dir[lcl].state = DIR_SHARED_NO_DATA;

                            // the src remains the same, the dest changes to the actural owner
                            net_cmd.dest = dir[lcl].owner;

                            bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                            if (!enqueue_status) {
                                // FORWARD queue is full
                                to_buffer(FORWARD, net_cmd);
                            }

                        }
                    } else { // dir[lcl].state == INVALID

                        // first time request, change dir state to OWNED, reply with EXCLUSIVE
                        dir[lcl].shared_nodes = (1 << src);
                        dir[lcl].owner = src;
                        dir[lcl].state = DIR_OWNED;

                        pc.permit_tag = EXCLUSIVE;
                        net_cmd.dest = src;
                        copy_cache_line(pc.data, mem[lcl]);
                        net_cmd.proc_cmd = pc;
                        net_cmd.valid_p = 1;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }
                    }
                } else if (pc.permit_tag == MODIFIED) {
                    // BUS RWITM
                    if (dir[lcl].state == DIR_SHARED) {
                        // first check the capacity of the local inv queue
                        if (to_net_inv_q.space() < count_bits(dir[lcl].shared_nodes)) {

                            // no-ack the src node (net_cmd.valid_p = 0)
                            net_cmd.valid_p = 0;

                        } else {
                            // Change the block to be Modified state
                            dir[lcl].state = DIR_OWNED;
                            dir[lcl].owner = src;
                            dir[lcl].shared_nodes |= 1 << src;

                            // Send invalidation requests until all the sharers acknowledge
                            for (int i_node = 0; i_node < 32; i_node++) {
                                if ((dir[lcl].shared_nodes >> i_node) & 0x1) {
                                    if (i_node != src) {
                                        // don't send invalidates to the src if it is in the sharer list
                                        net_cmd_t net_cmd_inv;
                                        net_cmd_inv.src = src; // later used to invalidate shared list
                                        net_cmd_inv.dest = i_node;
                                        net_cmd_inv.proc_cmd = pc;
                                        net_cmd_inv.proc_cmd.busop = INVALIDATE;
                                        net_cmd_inv.valid_p = 1;

                                        if (i_node == node) {
                                            // no need to generate net req if the dir has the copy
                                            net_cmd.proc_cmd.busop = INVALIDATE;
                                            response_t r = cache->snoop(net_cmd);
                                            // Update sharer list
                                            uint temp = ~(1 << node);
                                            dir[lcl].shared_nodes &= temp;
                                        } else {
                                            // enqueue to the local queue if REQUEST queue is full, for invalidations
                                            bool enqueue_status = net->to_net(node, REQUEST, net_cmd_inv);
                                            if (!enqueue_status) {
                                                to_net_inv_q.push_back(net_cmd_inv);
                                            }
                                        }
                                    }
                                }
                            }
                            // ack the src node (net_cmd.valid_p = 1)
                            net_cmd.valid_p = 1;
                            copy_cache_line(pc.data, mem[lcl]);
                        }

                        // reply to the src node
                        net_cmd.dest = src;
                        net_cmd.proc_cmd = pc;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }

                    } else if (dir[lcl].state == DIR_SHARED_NO_DATA) {

                        // reply to the src node (requestor) with no-ack (net_cmd.valid_p = 0)
                        net_cmd.valid_p = 0;

                        net_cmd.dest = src;
                        net_cmd.proc_cmd = pc;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }

                    } else if (dir[lcl].state == DIR_OWNED) {
                        if (src == dir[lcl].owner) {
                            ERROR("should not see this proc request, the node is already the owner");

                        } else if ((dir[lcl].shared_nodes >> src) & 0x1) {
                            // the requestor is one of sharers
                            // reply to the src node (requestor) with no-ack (net_cmd.valid_p = 0)
                            net_cmd.valid_p = 0;

                            net_cmd.dest = src;
                            net_cmd.proc_cmd = pc;

                            bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                            if (!enqueue_status) {
                                // REPLY queue is full
                                to_buffer(REPLY, net_cmd);
                            }
                        } else {
                            // the requestor is not one of sharers, forward the request to the owner
                            // the src remains the same, the dest changes to the actural owner
                            net_cmd.dest = dir[lcl].owner;

                            bool enqueue_status = net->to_net(node, FORWARD, net_cmd);
                            if (!enqueue_status) {
                                // FORWARD queue is full
                                to_buffer(FORWARD, net_cmd);
                            }
                        }
                    } else { // dir[lcl].state == INVALID

                        // first time request, change dir state to OWNED, reply with EXCLUSIVE
                        dir[lcl].shared_nodes = (1 << src);
                        dir[lcl].owner = src;
                        dir[lcl].state = DIR_OWNED;

                        net_cmd.dest = src;
                        copy_cache_line(pc.data, mem[lcl]);
                        net_cmd.proc_cmd = pc;
                        net_cmd.valid_p = 1;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }
                    }
                } else {
                    ERROR_ARGS(
                            ("Invalid bus op %d with permit tag %d seen at node %d\n", pc.busop, pc.permit_tag, node));
                }
                break;

            case WRITE: ERROR_ARGS(("Node %d: Writebacks shouldn't be in the request queue", node));
                break;

            case INVALIDATE: ERROR_ARGS(("Dir %d received invalidates from node %d", node, src));
                break;
        }
    } else {
        // gen_node(pc.addr) != node
        // invalidates
        if (pc.busop == INVALIDATE) {
            response_t r = cache->snoop(net_cmd);

            // reply to the dir
            net_cmd.src = node;
            net_cmd.dest = gen_node(pc.addr);
            net_cmd.proc_cmd = pc;
            net_cmd.valid_p = 1;

            bool enqueue_status = net->to_net(node, REPLY, net_cmd);
            if (!enqueue_status) {
                // REPLY queue is full
                to_buffer(REPLY, net_cmd);
            }
        } else {
            ERROR("REQUEST queue (if not INVALIDATES) should always satisfy gen_node(pc.addr) == node");
        }
    }
    NOTE_ARGS(("After Net request, dir state %d, sharer list %x", dir[lcl].state, dir[lcl].shared_nodes));

}

bool iu_t::process_net_forward(net_cmd_t net_cmd) {
    proc_cmd_t pc = net_cmd.proc_cmd;

    int src = net_cmd.src;

    if (gen_node(pc.addr) != node) {
        switch (pc.busop) {
            case (READ):
                if (pc.permit_tag == SHARED) {
                    // Forwarded BUS READ
                    forward_cmd_p = true;
                    response_t r = cache->snoop(net_cmd);
                    // can't return the data back for now
                    // have to access cache for data
                    forward_cmd_p = false;
                    if (!r.hit_p) {
                        // if cache miss, return non-ack response to the source
                        NOTE_ARGS(("The owner %d has lost the cache line for addr %d\n", node, pc.addr));

                        net_cmd.valid_p = 0;
                        net_cmd.dest = src;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }
                    } else {
                        // if hit
                        // - If cache block is modified/exclusive, return data directly to directory (Update sharer list) 
                        //   and source
                        // - If cache block is shared, return data to the source

                        net_cmd.valid_p = 1;

                        copy_cache_line(pc.data, forward_net_cmd.data);
                        pc.permit_tag = SHARED;
                        pc.busop = READ;
                        net_cmd.proc_cmd = pc;

                        // reply to the requestor with data
                        net_cmd.dest = src;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }

                        if (forward_net_cmd.permit_tag == MODIFIED || forward_net_cmd.permit_tag == EXCLUSIVE) {
                            // reply to the dir with data
                            // if dir is not the requestor
                            if (gen_node(pc.addr) != src) {
                                net_cmd.dest = gen_node(pc.addr);
                                to_buffer(REPLY, net_cmd);
                            }
                        }
                    }
                } else if (pc.permit_tag == MODIFIED) {
                    forward_cmd_p = true;
                    response_t r = cache->snoop(net_cmd);
                    // can't return the data back for now
                    // have to access cache for data
                    forward_cmd_p = false;

                    if (!r.hit_p) {
                        // if cache miss, return non-ack response to the source
                        NOTE_ARGS(("The owner %d has lost the cache line for addr %d\n", node, pc.addr));

                        net_cmd.valid_p = 0;
                        net_cmd.dest = src;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }
                    } else {
                        // if hit
                        // - return data to directory (Update sharer list) and source

                        net_cmd.valid_p = 1;

                        copy_cache_line(pc.data, forward_net_cmd.data);
                        pc.permit_tag = MODIFIED;
                        pc.busop = WRITE;
                        net_cmd.proc_cmd = pc;

                        // reply to the requestor with data
                        net_cmd.dest = src;

                        bool enqueue_status = net->to_net(node, REPLY, net_cmd);
                        if (!enqueue_status) {
                            // REPLY queue is full
                            to_buffer(REPLY, net_cmd);
                        }

                        // reply to the dir with data
                        // if dir is not the requestor
                        net_cmd.dest = gen_node(pc.addr);
                        if (gen_node(pc.addr) != src) {
                            net_cmd.dest = gen_node(pc.addr);
                            to_buffer(REPLY, net_cmd);
                        }
                    }
                } else {
                    ERROR_ARGS(
                            ("Invalid bus op %d with permit tag %d seen at node %d\n", pc.busop, pc.permit_tag, node));
                }
                break;

            case (WRITE): ERROR_ARGS(("Node %d: Writebacks shouldn't be in the forward queue", node));
                break;

            case (INVALIDATE): ERROR_ARGS(("Node %d: Invalidation shouldn't be in the forward queue", node));
                break;
        }

    } else {
        ERROR("FORWARD queue should satisfy gen_node(pc.addr) != node")
    }
}

bool iu_t::process_net_writeback(net_cmd_t net_cmd) {
    proc_cmd_t pc = net_cmd.proc_cmd;

    int lcl = gen_local_cache_line(pc.addr);
    int src = net_cmd.src;
    int dest = net_cmd.dest;

    if (pc.busop == WRITE) {
        if (gen_node(pc.addr) == node) {
            // write back
            // no reply generated

            if (dir[lcl].state == DIR_SHARED) {
                // shared: update sharer list
                uint temp = ~(1 << src);
                dir[lcl].shared_nodes &= temp;

            } else if (dir[lcl].state == DIR_OWNED) {
                // owned: copy the data into memory and change directory state to be Invalid
                if (dir[lcl].owner != src) {
                    ERROR_ARGS(("Non-owner write-back: owner %d, node %d\n", dir[lcl].owner, node));
                }
                copy_cache_line(mem[lcl], pc.data);
                dir[lcl].state = DIR_INVALID;
                dir[lcl].shared_nodes = 0;
            } else if (dir[lcl].state == DIR_SHARED_NO_DATA) {
                if (dir[lcl].owner != src) {
                    ERROR_ARGS(("Non-owner write-back: owner %d, node %d\n", dir[lcl].owner, node));
                }
                copy_cache_line(mem[lcl], pc.data);
                dir[lcl].state = DIR_INVALID;
                dir[lcl].shared_nodes = 0;              
            } else {
                ERROR_ARGS(("invalid directory state seen at node %d\n", node));
            }
        } else {
            ERROR("WRITEBACK queue should satisfy gen_node(pc.addr) == node");
        }
    } else {
        ERROR("WRITEBACK queue should only contain WRITE BACK bus ops");
    }
}

/**
 * Process reply from network (Other nodes)
 *
 * Network request (Based on different bus tag)
 *  1. Invalidation request ack
 *      x Update sharer list (1 -> 0)
 *      x End the processor command when all invalidations acked
 *  2. Read request ack (Not forwarded request)
 *      x Fill cache (may trigger replacement write back)
 *      x End the processor command processing signal
 *  3. Invalidation request non-ack (Impossible)
 *      x Retry
 *  4. Write request ack (Not forwarded request)
 *      x Write back
 *          - Evict the victim (Not implemented, no ack expected)
 *      x Not Write back
 *          - Fill cache (may trigger replacement write back)
 *          - End the processor command processing signal
 *  5. Read request non-ack
 *      x Retry (Need proc do again)
 *  6. Write request non-ack
 *      x Retry (Need proc do again)
 *  7. Write request ack (forwarded request)
 *      x Update owner id
 *  8. Read request ack (forwarded request)
 *      x Fill memory
 *      x Change state from Shared-no-data/Invalid to Shared and update sharer list
 *
 * @param net_cmd Network command
 * @return Success or not
 */
bool iu_t::process_net_reply(net_cmd_t net_cmd) {
    proc_cmd_t pc = net_cmd.proc_cmd;
    int lcl = gen_local_cache_line(pc.addr);

    bool forwarded = (node == gen_node(pc.addr)); // 1: forwarded, 0: not forwarded

    switch (pc.busop) {
        case (READ): {
            if (!net_cmd.valid_p) {
                // retry
                proc_cmd_processed_p = false;
                NOTE_ARGS(("Node %d, retry bus op %d based on the reply from node %d", node, pc.busop, net_cmd.src));

            } else if (forwarded) {
                // Read request ack (forwarded request)
                // Fill memory
                // Change state from Shared-no-data/Invalid to Shared and update sharer list
                copy_cache_line(mem[lcl], pc.data);
                dir[lcl].state = DIR_SHARED;
                dir[lcl].shared_nodes |= (1 << net_cmd.src);
                NOTE_ARGS(("Node %d, dir update to SHARED based on the reply from node %d", node, net_cmd.src));
                if (net_cmd.src == gen_node(pc.addr)) {
                    // requestor is the dir
                    proc_cmd_p = false; // clear proc_cmd
                    cache->reply(pc);                    
                }
            } else {
                // Read request ack (Not forwarded request)
                // Fill cache (may trigger replacement write back)
                // End the processor command processing signal
                proc_cmd_p = false; // clear proc_cmd
                cache->reply(pc);

            }
            break;
        }

        case (WRITE): {
            if (!net_cmd.valid_p) {
                // retry, write back rejected?
                proc_cmd_processed_p = false;

            } else if (forwarded) {
                // Write request ack (forwarded request)
                // Update owner id
                dir[lcl].state = DIR_OWNED;
                dir[lcl].owner = net_cmd.src;
                dir[lcl].shared_nodes = (1 << net_cmd.src);

                if (net_cmd.src == gen_node(pc.addr)) {
                    // requestor is the dir
                    proc_cmd_p = false; // clear proc_cmd
                    cache->reply(pc);                    
                }
            } else {
                // Write request ack (Not forwarded request)
                //   - Fill memory
                proc_cmd_p = false; // clear proc_cmd
                cache->reply(pc);
            }
            break;
        }

        case (INVALIDATE): {
            if (!net_cmd.valid_p) {
                ERROR_ARGS(("Node: %d No INVALIDATION NO-ACK expected for current implementation!", node));

            } else {
                // Update sharer list
                uint temp = ~(1 << net_cmd.src);
                dir[lcl].shared_nodes &= temp;
                NOTE_ARGS(("INVALIDATE ACK: Shared nodes %d", dir[lcl].shared_nodes));
            }
            break;
        }
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
    int lcl = gen_local_cache_line(addr);

    for (int i = 0; i < CACHE_LINE_SIZE; ++i) mem[lcl][i] = data[i];
}

int iu_t::get_mem(int addr) {
    int lcl = gen_local_cache_line(addr);
    int offset = addr & ((1 << LG_CACHE_LINE_SIZE) - 1);

    return mem[lcl][offset];
}

void iu_t::to_buffer(pri_t pri, net_cmd_t net_cmd) {
    if (net_buffer[0].valid || net_buffer[1].valid) {
        ERROR("net_buffer: pending request got overwritten");
        return;
    }
    NOTE_ARGS(("Node %d, buffered a network request of priority %d", node, pri));

    if (net_buffer[0].valid) {
        net_buffer[1].net_cmd = net_cmd;
        net_buffer[1].valid = 1;
        net_buffer[1].pri = pri;
    } else {
        net_buffer[0].net_cmd = net_cmd;
        net_buffer[0].valid = 1;
        net_buffer[0].pri = pri;
    }
}
