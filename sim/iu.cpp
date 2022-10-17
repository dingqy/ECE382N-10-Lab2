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
            net_cmd.dest = src;
            net_cmd.src = dest;
            copy_cache_line(pc.data, mem[lcl]);
            net_cmd.proc_cmd = pc;


            return (net->to_net(node, REPLY, net_cmd));

        case WRITE:
            copy_cache_line(mem[lcl], pc.data);
            return (false);

        case INVALIDATE:
            // ***** FYTD *****
            // TODO: Invalidation from other nodes
            return (false);  // need to return something for now
    }
}

/**
 * Process reply from network (Other nodes)
 *
 * @param net_cmd Network command
 * @return Success or not
 */
bool iu_t::process_net_reply(net_cmd_t net_cmd) {
    proc_cmd_t pc = net_cmd.proc_cmd;

    // ***** FYTD *****

    proc_cmd_p = false; // clear out request that this reply is a reply to

    // TODO: Maybe more reply operation?
    switch (pc.busop) {
        case READ: // assume local
            // Deal with read request
            cache->reply(pc);
            return (false);

        case WRITE:
        case INVALIDATE: ERROR(
                "should not have gotten a reply back from a write or an invalidate, since we are incoherent");
            return (false);  // need to return something for now
    }
}

void iu_t::print_stats() {
    printf("------------------------------\n");
    printf("%d: iu\n", node);

    printf("num local  accesses = %d\n", local_accesses);
    printf("num global accesses = %d\n", global_accesses);
}
