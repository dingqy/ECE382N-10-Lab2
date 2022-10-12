// test.cpp
//   Derek Chiou
//     May 19, 2007

// STUDENTS: YOU ARE EXPECTED TO PUT YOUR TESTS IN THIS FILE, ALONG WITH PROC.CPP.

#include <stdio.h>
#include "types.h"
#include "generic_error.h"
#include "helpers.h"
#include "cache.h"
#include "test.h"

extern args_t args;
extern int addr_range;
extern cache_t **caches;

test_args_t test_args;

void init_test() {
  switch(args.test) {
  case 0:
    test_args.addr_range = 1024;
    break;

  default:
    ERROR("don't recognize this test");
  }
}

void finish_test() {
  double hr;

  for (int i = 0; i < args.num_procs; ++i) {
    switch(args.test) {
    case 0:
      hr = caches[i]->hit_rate();
      if (!within_tolerance(hr, 0.5, 0.001)) {
	ERROR("out of tolerance");
      }
      break;
      
    default: 
      ERROR("don't recognize this test");
    }
  }
  printf("passed\n");
}
