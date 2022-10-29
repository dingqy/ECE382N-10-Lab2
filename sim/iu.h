// iu.h
//   by Derek Chiou
//      March 4, 2007
// 

// STUDENTS: YOU ARE ALLOWED TO MODIFY THIS FILE, BUT YOU SHOULDN'T NEED TO MODIFY MUCH, IF ANYTHING.
// for 382N-10

#ifndef IU_H
#define IU_H

#include "types.h"
#include "my_fifo.h"
#include "cache.h"
#include "network.h"
#include <queue>

class iu_t {
    int node;

    int local_accesses;
    int global_accesses;

    data_t mem[MEM_SIZE];   // 64B x 1024

    cache_t *cache;
    network_t *net;

    bool proc_cmd_p;
    proc_cmd_t proc_cmd;

    bool proc_cmd_processed_p;

    // processor side
    bool process_proc_request(proc_cmd_t proc_cmd);

    // network side
    bool process_net_request(net_cmd_t net_cmd);

    bool process_net_reply(net_cmd_t net_cmd);

    // directory
    dir_t dir[MEM_SIZE];

    // queue: node -> network
    my_fifo_t<net_cmd_t> to_net_req_q;


public:
    iu_t(int __node);

    void bind(cache_t *c, network_t *n);

    void advance_one_cycle();

    void print_stats();

    // processor side
    bool from_proc(proc_cmd_t pc);

    // network side
    bool from_net(net_cmd_t nc);

    // debug directory
    // TODO: Function for tests
    dir_t get_dir_entry(int index);

};

#endif
