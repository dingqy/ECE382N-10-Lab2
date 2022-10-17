// proc.cpp
//   by Derek Chiou
//      March 4, 2007
// 

// STUDENTS: YOU ARE EXPECTED TO MODIFY THIS FILE TO INSERT YOUR
// TESTS.  HOWEVER, YOU MUST BE ABLE TO ACCEPT OTHER PROC.CPP FILES,
// AS I WILL BE REPLACING YOUR PROC.CPP WITH MINE (AND YOUR FELLOW
// STUDENTS') FOR TESTING PURPOSES.

// for 382N-10



#include <stdio.h>
#include <stdlib.h>
#include "generic_error.h"
#include "cache.h"
#include "proc.h"
#include "test.h"

/**
 * Constructor of processor
 *
 * @param __p Processor ID
 */
proc_t::proc_t(int __p) {
    proc = __p;
    init();
}

/**
 * Initialize the args in processor class
 */
void proc_t::init() {
    response.retry_p = false;
    ld_p = false;
}

/**
 * Bind related cache
 *
 * @param c cache object
 */
void proc_t::bind(cache_t *c) {
    cache = c;
}


// ***** FYTD ***** 

// this is just a simple random test.  I'm not giving
// you any more test cases than this.  You will be tested on the
// correctness and performance of your solution.

/**
 * Simulate processor memory access behavior
 */
void proc_t::advance_one_cycle() {
    int data;

    // TODO: ADD test behavior here
    switch (args.test) {
        case 0:
            if (!response.retry_p) {
                addr = random() % test_args.addr_range;
                ld_p = ((random() % 2) == 0);
            }
            if (ld_p) response = cache->load(addr, 0, &data, response.retry_p);
            else response = cache->store(addr, 0, cur_cycle, response.retry_p);
            break;

        default: ERROR("don't know this test case");
    }
}




