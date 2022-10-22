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
 */
void iu_t::advance_one_cycle() {
    // fixed priority: reply from network
    if (net->from_net_p(node, REPLY)) {
        process_net_reply(net->from_net(node, REPLY));

    } else if (net->from_net_p(node, REQUEST)) {
        process_net_request(net->from_net(node, REQUEST));

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
 *          - If it is owned by other nodes, then it needs to downgrade the owner node, get the newest copy, and update owner
 *          - If it is shared with other nodes, update sharer list
 *          - If it is the only copy, then change request state to exclusive state and setup sharer list (not initial shared state)
 *      * Global memory access
 *          - Send request through network (read request)
 *  2. Cache write miss
 *      * Local memory access
 *          - If it is owned by other nodes, then it needs to downgrade owner node to invalidate, get the newest copy, and update owner
 *          - If it is shared by other nodes, then it needs to invalidate all the sharers, wait for all acknowledgement, and update sharer list
 *          - If it is the only copy, setup owner
 *      * Global memory access
 *          - send request through network (write request)
 *  3. Replacement write back (modified state)
 *      * Local memory access
 *          - Copy the data into memory and update owner
 *      * Global memory access
 *          - send request through network (write request but need to downgrade the directory state)
 *          - For any incoming request to this cache line, response should be non-acknowledgement (It will not hit in the cache)
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
        proc_cmd_p = false; // clear proc_cmd

        switch (pc.busop) {
            case READ:
                // Read from memory
                copy_cache_line(pc.data, mem[lcl]);
                cache->reply(pc);
                return (false);

            case WRITE:
                // Write to memory
                copy_cache_line(mem[lcl], pc.data);
                return (false);

            case INVALIDATE:
                // ***** FYTD *****
                // TODO: Self-invalidation (Is it necessary to implement?)
                return (false);  // need to return something for now
                break;
        }

    } else { // global
        ++global_accesses;
        net_cmd_t net_cmd;

        net_cmd.src = node;
        net_cmd.dest = dest;
        net_cmd.proc_cmd = pc;

        return (net->to_net(node, REQUEST, net_cmd));
    }
}


// receive a net request
/**
 * Process requests from network (Other nodes)
 *
 * Network request
 *  1. Read request (Not forwarded request)
 *      * This cache block is shared
 *          - Return the data in the memory and update sharer list
 *      * This cache block has owner (modified)
 *          - If the owner is current node, access the cache to get the newest copy, downgrade the cache state, and update the owner in directory
 *          - If the owner is other nodes, forward the request to the owner
 *      * This cache block is Processing-modified
 *          - Return non-ack response
 *          - TODO: Is it possible to have some MSHR to queue the request?
 *      * This cache block has owner (exclusive)
 *          - If the owner is current node, respond with data, downgrade the cache state, and update the owner in directory
 *          - If the owner is other nodes, respond with data and forward the request to the owner (no ack read request)
 *      * This cache block is Processing-invalid
 *          - return non-ack response
 *
 *  2. Read request (forwarded request)
 *      * Access the cache
 *          - If cache miss, return non-ack response
 *          - If cache hit and need ack, return data directly to directory and destination (Downgrade to shared or invalid)
 *
 *  3. Write request (Ownership)
 *      * This cache block is shared
 *          - Change the block to be Processing-modified state
 *          - Send invalidation requests until all the sharers acknowledge
 *          - Send acknowledge back to source node
 *      * This cache block has owner
 *          - If the owner is current node, invalidate the owner and return ack response
 *          - If the owner is other nodes, send invalidate request, change to Processing-modified state, and wait for ack response
 *      * This cache block is Processing-modified
 *          - Return non-ack response
 *          - TODO: Is it possible to have some MSHR to queue the request?
 *      * This cache block is Processing-invalid
 *          - Changing to processing-modified state and return data directly
 *
 *  4. Invalidation request
 *      * No directory access
 *      * Modify cache state and return ack response
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
 *      * Update sharer list and reduce the counter by 1
 *  2. Read request ack
 *      * Fill cache (may trigger replacement write back)
 *      * End the processor command processing signal
 *  3. Invalidation request non-ack
 *      * Retry
 *  4. Write request ack
 *      * End the processor command processing signal
 *  5. Read request non-ack
 *      * Retry
 *  6. Write request non-ack
 *      * Retry
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
