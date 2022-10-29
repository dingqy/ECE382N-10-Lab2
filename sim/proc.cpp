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
 *
 * Test cases description
 *
 * --------------------------------------------------------------------------------------------------------------
 * Case 1:
 *  - Directory Invalid -> Read request -> Exclusive in cache and Owned in directory (Local)
 *
 * Case 2:
 *  - Directory Invalid -> Read request -> Network -> Node reply -> Exclusive in cache and Owned in directory (global)
 *
 * Case 3:
 *  - Directory Invalid -> Write request -> Modified in cache and Owned in directory (Local)
 *
 * Case 4:
 *  - Directory Invalid -> Write request -> Network -> Node reply -> Exclusive in cache and Owned in directory (global)
 * --------------------------------------------------------------------------------------------------------------
 * Case 5:
 *  - Directory Owned (Global) -> Read request -> Forward request -> Network -> Node reply (To directory and source) -> Shared in both caches and directory
 *
 * Case 6.1:
 *  - Directory Owned (Local) -> Invalidate request (Write back) -> Copy data and Invalid state in directory
 *
 * Case 6.2 (19):
 *  - Directory Owned (Global) -> Write request (Write back) -> Copy data and Invalid state in directory
 *
 * Case 11:
 *  - Directory Owned (Global) -> Write request -> Forward request -> Network -> Node reply (To directory and source) -> Modified in one cache, Invalid in other cache, and owner change in directory
 *
 * Case 12:
 *  - Directory Owned (Local) -> Read request -> Forward request -> Network -> Node reply (To directory and source) -> Shared in both caches and directory
 *
 * Case 18:
 *  - Directory Owned (Local) -> Write request -> Forward request -> Network -> Node reply (To directory and source) -> Modified in one cache, Invalid in other cache, and owner change in directory
 * --------------------------------------------------------------------------------------------------------------
 * Case 7:
 *  - Directory Owned (Global) -> Read request 1 -> Forward request -> Network -> Node reply (To directory and source) -> Shared in both caches and directory
 *  - Directory Shared-no-data -> Read request 2 -> Forward request -> Network -> Node reply (To source) -> Shared in sources and sharer update in directory
 *
 * Case 8:
 *  - Directory Owned (Global) -> Read request 1 -> Forward request -> Network -> Node reply (To directory and source) -> Shared in both caches and directory
 *  - Directory Shared-no-data -> Read request 2 -> Forward request -> Network -> Resubmit / Retry -> Shared in sources and sharer update in directory
 *
 * Case 9:
 *  - Directory Owned (Global) -> Read request 1 -> Forward request -> Network -> Node reply non-ack (To directory and source) -> Resubmit / Retry -> Shared in both caches and directory
 *  - Directory Shared-no-data -> Read request 2 -> Forward request -> Network -> Resubmit / Retry -> Shared in sources and sharer update in directory
 *
 * Case 9:
 *  - Directory Owned (Global) -> Read request 1 -> Forward request -> Network -> Node reply non-ack (To directory and source) -> Resubmit / Retry -> Shared in both caches and directory
 *  - Directory Shared-no-data -> Write request 2 -> Non-ack -> Retry -> Directory Shared -> Forward -> Network -> Node reply non-ack (To source) -> Resubmit / Retry -> Shared in sources and sharer update in directory
 * --------------------------------------------------------------------------------------------------------------
 * Case 13:
 *  - Directory Shared -> Read request -> Node reply (To source) -> Shared in cache and sharer list update in directory
 *
 * Case 14:
 *  - Directory Shared -> Write request -> Invalidation broadcast -> Node reply (To source) -> Invalidation ack -> Modified in cache, invalidation, and owned in directory
 *
 * Case 15:
 *  - Directory Shared -> Write request (write back) -> Update sharer list
 * --------------------------------------------------------------------------------------------------------------
 * Case 16:
 *  - Directory Shared-no-data -> Read request -> Forward request -> Node reply (To directory and source) -> Shared in cache and sharer list update
 *
 * Case 17:
 *  - Directory Shared-no-data -> Write request (write back) -> Invalid in directory
 * --------------------------------------------------------------------------------------------------------------
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

            // TODO: Test cases
            //


        default: ERROR("don't know this test case");


    }
}




