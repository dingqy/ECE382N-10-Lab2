// main.cpp
//   by Derek Chiou
//      March 4, 2007
// 
//   modified October 22, 2009

// for 382N-10

// high-level structure, initialization, and argument processing

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.  

#include<stdio.h>
#include<stdlib.h>

#include "helpers.h"
#include "cache.h"
#include "iu.h"
#include "proc.h"
#include "network.h"
#include "test.h"

// pointers to all components of the simulator
proc_t    **procs;
cache_t   **caches;
iu_t      **ius;
network_t *network;

int cur_cycle = 0;

uint gen_node_mask = 0x0; // to be defined in parse_args
uint gen_local_addr_shift;

args_t args;

void advance_time() {
  static int p = 0;

  for (int i = 0; i < args.num_procs; ++i) {
    p = (p + 1) % args.num_procs;

    network->advance_one_cycle();
    ius[p]->advance_one_cycle();
    procs[p]->advance_one_cycle();

  }
  ++cur_cycle;
}

void parse_args(int argc, char *argv[]) {
  if (argc != 5) {
    ERROR("usage: <number of processors> <num cycles> <test> <verbose>");
  }
  
  args.num_procs = atoi(argv[1]);
  args.num_cycles = atoi(argv[2]);
  args.test = atoi(argv[3]);
  args.verbose = atoi(argv[4]);

  gen_node_mask = (1 << (lg(args.num_procs))) - 1;
  gen_local_addr_shift = lg(args.num_procs) + LG_INTERLEAVE_SIZE;
}

void init_system() {
  network = new network_t(args.num_procs);
  procs = new proc_t *[args.num_procs];
  caches = new cache_t *[args.num_procs];
  ius = new iu_t*[args.num_procs];

  for (int p = 0; p < args.num_procs; ++p) {
    procs[p] = new proc_t(p);
    caches[p] = new cache_t(p, 2, 3, LG_CACHE_LINE_SIZE);
    ius[p] = new iu_t(p);;
    
    procs[p]->bind(caches[p]);
    caches[p]->bind(ius[p]);
    ius[p]->bind(caches[p], network);
  }

  init_test();
}

main(int argc, char *argv[]) {
  int cycle;

  parse_args(argc, argv);
  init_system();
  
  for (cycle = 0; cycle < args.num_cycles; ++cycle) {
    advance_time();
  }

  for (int i = 0; i < args.num_procs; ++i) {
    caches[i]->print_stats();
    ius[i]->print_stats();
  }

  finish_test();
  
}
