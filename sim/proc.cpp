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
#include "helpers.h"

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
 * Case 6:
 *  - Directory Owned (Local) -> Invalidate request (Write back) -> Copy data and Invalid state in directory
 *
 * Case 7:
 *  - Directory Owned (Global) -> Write request (Write back) -> Copy data and Invalid state in directory
 *
 * Case 8:
 *  - Directory Owned (Global) -> Write request -> Forward request -> Network -> Node reply (To directory and source) -> Modified in one cache, Invalid in other cache, and owner change in directory
 *
 * Case 9:
 *  - Directory Owned (Local) -> Read request -> Forward request -> Network -> Node reply (To directory and source) -> Shared in both caches and directory
 *
 * Case 10:
 *  - Directory Owned (Local) -> Write request -> Forward request -> Network -> Node reply (To directory and source) -> Modified in one cache, Invalid in other cache, and owner change in directory
 * --------------------------------------------------------------------------------------------------------------
 * Case 11:
 *  - Directory Shared (Global) -> Read request -> Node reply (To source) -> Shared in cache and sharer list update in directory
 *
 * Case 12:
 *  - Directory Shared (Global) -> Write request -> Invalidation broadcast -> Node reply (To source) -> Invalidation ack -> Modified in cache, invalidation, and owned in directory
 *
 * Case 13:
 *  - Directory Shared (Global) -> Write request (write back) -> Update sharer list
 * --------------------------------------------------------------------------------------------------------------
 * Case 14:
 *  - Directory Shared-no-data -> Read request -> Forward request -> Node reply (To directory and source) -> Shared in cache and sharer list update
 *
 * Case 15:
 *  - Directory Shared-no-data -> Write request (write back) -> Invalid in directory
 *  -                                           Read request -> Forward request -> Retry/Resubmit -> Exclusive in cache and owned in directory
 *
 * Case 16:
 *  - Directory shared-no-data -> Write request -> Resubmit -> Directory shared -> invalidation -> Modified in cache and owned in directory
 * --------------------------------------------------------------------------------------------------------------
 * Case 17:
 *  - Directory Shared (Local) -> Read request -> Node reply (To source) -> Shared in cache and sharer list update in directory
 *
 * Case 18:
 *  - Directory Shared (Local) -> Write request -> Invalidation broadcast -> Node reply (To source) -> Invalidation ack -> Modified in cache, invalidation, and owned in directory
 *
 * Case 19:
 *  - Directory Shared (Local) -> Write request (write back) -> Update sharer list
 * --------------------------------------------------------------------------------------------------------------
 * Case 20:
 *  - Directory Shared (Global) -> Write request -> Invalidation -> ...
 *  -                                               Write request -> Resubmit/Retry
 *
 * Case 21:
 *  - Directory Shared (Global) -> Write request -> Invalidation -> ...
 *  -                                               Write request -> Forward request
 *
 * Case 22:
 *  - Directory Shared (Local) -> Write request -> Invalidation -> ...
 *  -                                               Write request -> Forward request
 * --------------------------------------------------------------------------------------------------------------
 * Case 23:
 *  - Directory Shared-no-data (Local) -> Read request -> Forward request -> Node reply (To directory and source) -> Shared in cache and sharer list update
 *
 * Case 24:
 *  - Directory Shared-no-data (Local) -> Write request (write back) -> Invalid in directory
 *  -                                           Read request -> Forward request -> Retry/Resubmit -> Exclusive in cache and owned in directory
 *
 * Case 25:
 *  - Directory shared-no-data (Local) -> Write request -> Resubmit -> Directory shared -> invalidation -> Modified in cache and owned in directory
 * --------------------------------------------------------------------------------------------------------------
 */
void proc_t::advance_one_cycle() {
    int data;

    if (init_valid) {
        for (auto &i: test_args[proc].test_inits) {
            cache->set_mem(i.address, i.data);
        }
        init_valid = false;
    }

    test_args_t test_set = test_args[proc];

    // TODO: ADD test behavior here
    switch (args.test) {
        case 0:
            if (!response.retry_p) {
                addr = random() % test_args[proc].addr_range;
                ld_p = ((random() % 2) == 0);
            }
            if (ld_p) response = cache->load(addr, 0, &data, response.retry_p);
            else response = cache->store(addr, 0, cur_cycle, response.retry_p);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            if (case_index < test_set.test_cases.size()) {
                if (cur_cycle >= test_set.test_cases[case_index].first) {
                    if (test_set.test_cases[case_index].second.write) {
                        response = cache->store(test_set.test_cases[case_index].second.address, 0,
                                                test_set.test_cases[case_index].second.data,
                                                response.retry_p);
                    } else {
                        response = cache->load(test_set.test_cases[case_index].second.address, 0, &data,
                                               response.retry_p);
                    }
                    if (!response.retry_p) {
                        case_index += 1;
                    }
                }
            }
            break;
        default: ERROR("don't know this test case");
    }

    while (record_index < test_set.test_records.size()) {
        int address = test_set.test_records[record_index].second.address;
        if (cur_cycle == test_set.test_records[record_index].first) {
            if (test_set.test_records[record_index].second.mem_cache) {
                cache_access_response_t cache_rep;
                cache->cache_access(address, INVALID, &cache_rep);
                test_args[proc].test_results.emplace_back(cur_cycle,
                                                          test_result_t{cache_rep.permit_tag, DIR_INVALID, address,
                                                                        cache->read_data(address, cache_rep), 0x0,
                                                                        0x0});
            } else {
                int lcl = gen_local_cache_line(address);
                dir_t temp = cache->get_dir_entry(lcl);
                test_args[proc].test_results.emplace_back(cur_cycle,
                                                          test_result_t{INVALID, temp.state, address,
                                                                        cache->get_mem(address), temp.shared_nodes,
                                                                        temp.owner});
            }
            record_index += 1;
        } else {
            break;
        }
    }
}
