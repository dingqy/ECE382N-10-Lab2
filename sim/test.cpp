// test.cpp
//   Derek Chiou
//     May 19, 2007

// STUDENTS: YOU ARE EXPECTED TO PUT YOUR TESTS IN THIS FILE, ALONG WITH PROC.CPP.

#include <stdio.h>
#include <iostream>
#include "types.h"
#include "generic_error.h"
#include "helpers.h"
#include "cache.h"
#include "test.h"

extern args_t args;
extern int addr_range;
extern cache_t **caches;

test_args_t test_args[32];

/**
 * Initialize the test address range
 *
 * TODO: ADD test here
 */
void init_test() {
    data_t init_temp;
    switch (args.test) {
        case 0:
            test_args[0].addr_range = 1024;
            break;
        case 1:
            for (int &i: init_temp) {
                i = 0;
            }
            init_temp[1] = 1;

            test_args[0].test_inits.emplace_back(0x00000001, init_temp);
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0x00000001, 0});
            test_args[0].test_records.emplace_back(1, test_record_t{true, 0x00000001});
            test_args[0].test_records.emplace_back(1, test_record_t{false, 0x00000001});
            test_args[0].test_goldens.emplace_back(1, test_result_t{EXCLUSIVE, DIR_INVALID, 0x00000001, 0x1, 0x0, 0x0});
            test_args[0].test_goldens.emplace_back(1, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x1, 0x0, 0x0});
            break;
        case 2:
            for (int &i: init_temp) {
                i = 0;
            }
            init_temp[1] = 1;

            test_args[1].test_inits.emplace_back(0x00000101, init_temp);
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0x00000101, 0});
            test_args[0].test_records.emplace_back(21, test_record_t{true, 0x00000101});
            test_args[1].test_records.emplace_back(21, test_record_t{false, 0x00000101});
            test_args[0].test_goldens.emplace_back(1, test_result_t{EXCLUSIVE, DIR_INVALID, 0x00000101, 0x1, 0x0, 0x0});
            test_args[1].test_goldens.emplace_back(1, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x1, 0x0, 0x0});
            break;
        case 3:
            for (int &i: init_temp) {
                i = 0;
            }
            init_temp[1] = 1;

            test_args[0].test_inits.emplace_back(0x00000001, init_temp);
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000001, 0x100});
            test_args[0].test_records.emplace_back(1, test_record_t{true, 0x00000001});
            test_args[0].test_records.emplace_back(1, test_record_t{false, 0x00000001});
            test_args[0].test_goldens.emplace_back(1,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});
            test_args[0].test_goldens.emplace_back(1, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x1, 0x0, 0x0});
            break;
        case 4:
            for (int &i: init_temp) {
                i = 0;
            }
            init_temp[1] = 1;

            test_args[1].test_inits.emplace_back(0x00000101, init_temp);
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[0].test_records.emplace_back(21, test_record_t{true, 0x00000101});
            test_args[1].test_records.emplace_back(21, test_record_t{false, 0x00000101});
            test_args[0].test_goldens.emplace_back(21,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[1].test_goldens.emplace_back(21, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x1, 0x0, 0x0});
            break;
        case 5:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(32, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(32, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x0, 0x0,
                                                                     0x0});

            test_args[0].test_records.emplace_back(42, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(42, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(54, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(54, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0x5, 0x0});
            test_args[2].test_records.emplace_back(53, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(53, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 6:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000001, 0x100});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(4, test_case_t{false, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(6, test_case_t{false, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(8, test_case_t{false, 0x00008001, 0x0});
            test_args[0].test_records.emplace_back(10, test_record_t{false, 0x00000001});
            test_args[0].test_goldens.emplace_back(10,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});
            break;
        case 7:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(4, test_case_t{false, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(6, test_case_t{false, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(8, test_case_t{false, 0x00008001, 0x0});
            test_args[1].test_records.emplace_back(19, test_record_t{false, 0x00000001});
            test_args[1].test_goldens.emplace_back(19,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 8:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(31, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(31, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x0, 0x0});

            test_args[0].test_records.emplace_back(41, test_record_t{true, 0x00010001});
            test_args[0].test_goldens.emplace_back(41,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(52, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(52, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x0, 0x2});
            test_args[2].test_records.emplace_back(53, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(53,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 9:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(22, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(22, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x0, 0x0,
                                                                     0x0});

            test_args[0].test_records.emplace_back(32, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(32, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(43, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(43, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0x3, 0x0});
            test_args[1].test_records.emplace_back(44, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(44, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 10:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(22, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(22, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x0, 0x0});

            test_args[0].test_records.emplace_back(32, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(32,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(43, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(43, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x0, 0x1});
            test_args[1].test_records.emplace_back(44, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(44,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 11:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(50, test_case_t{false, 0x00000101, 0x0});

            test_args[2].test_records.emplace_back(71, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(71, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[1].test_records.emplace_back(71, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(71, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0x7, 0x0});
            break;
        case 12:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(100, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(111, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(111, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x3, 0x2});

            test_args[1].test_records.emplace_back(140, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(140, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x0, 0x2});

            test_args[1].test_records.emplace_back(140, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(140,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[0].test_records.emplace_back(140, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(140,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 13:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[0].test_cases.emplace_back(72, test_case_t{false, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(74, test_case_t{false, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(76, test_case_t{false, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(78, test_case_t{false, 0x00008001, 0x0});

            test_args[1].test_records.emplace_back(90, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(90, test_result_t{INVALID, DIR_SHARED, 0x00000001, 0x100, 0x2, 0x0});
            break;
        case 14:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(25, test_case_t{false, 0x00000101, 0x0});

            test_args[2].test_records.emplace_back(46, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(46, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 15:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[0].test_cases.emplace_back(22, test_case_t{false, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(24, test_case_t{false, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(26, test_case_t{false, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(28, test_case_t{false, 0x00008001, 0x0});

            test_args[1].test_records.emplace_back(40, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(40,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[1].test_records.emplace_back(50, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(50, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x0, 0x2});
            test_args[1].test_records.emplace_back(50, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(50,
                                                   test_result_t{EXCLUSIVE, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;




        default: ERROR("don't recognize this test");
    }
}

/**
 * Deal with the performance of the test
 *
 * TODO: ADD test here
 */
void finish_test() {
    double hr;

    std::cout << "-------------------------------------------------------" << std::endl;
    for (int i = 0; i < args.num_procs; ++i) {
        switch (args.test) {
            case 0:
                hr = caches[i]->hit_rate();
                if (!within_tolerance(hr, 0.5, 0.001)) {
                    ERROR("out of tolerance");
                }
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
                std::cout << "Processor: " << i << " Checking..." << std::endl;
                for (int j = 0; j < test_args[i].test_goldens.size(); j++) {
                    test_result_t test_result = test_args[i].test_results[j].second;
                    test_result_t test_golden = test_args[i].test_goldens[j].second;
                    if (test_result.cache_state != test_golden.cache_state) {
                        ERROR("Cache state error")
                    }
                    if (test_result.mem_state != test_golden.mem_state) {
                        ERROR("Directory state error")
                    }
                    if (test_golden.cache_state >= 1) {
                        if (test_result.data != test_golden.data) {
                            ERROR("Cache data error")
                        }
                    }
                    if (test_golden.mem_state >= 2) {
                        if (test_result.owner != test_golden.owner) {
                            ERROR("Directory owner error")
                        }
                    }
                    if (test_golden.mem_state == DIR_SHARED) {
                        if (test_result.sharer_list != test_golden.sharer_list) {
                            ERROR("Directory sharer list error")
                        }
                    }
                    if (test_golden.mem_state == DIR_INVALID && test_golden.cache_state == INVALID) {
                        if (test_result.data != test_golden.data) {
                            ERROR("Write back Error")
                        }
                    }
                }
                std::cout << "Passed" << std::endl;
                break;
            default: ERROR("don't recognize this test");
        }
        std::cout << "-------------------------------------------------------" << std::endl;
    }
    printf("passed\n");
}
