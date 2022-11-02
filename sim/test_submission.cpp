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

#define TEST_WRITE true
#define TEST_READ false

/**
 * Initialize the test address range
 *
 * TODO: ADD test here
 */
void init_test() {
    switch (args.test) {
        case 0:
            test_args[0].addr_range = 1024;
            break;
        case 1:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000001, 0x100});
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_READ, 0x00000001, 0x0});
            test_args[0].test_goldens.emplace_back(0, test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});
            break;
        case 2:
            test_args[1].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(0, test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});
            break;
        case 3:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(0, test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});
            break;
        case 4:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_cases.emplace_back(42, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(42, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[2].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 5:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});

            test_args[0].test_cases.emplace_back(42, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(42, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[2].test_cases.emplace_back(53, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 6:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000001, 0x100});
            test_args[0].test_cases.emplace_back(2, test_case_t{TEST_READ, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(4, test_case_t{TEST_READ, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(6, test_case_t{TEST_READ, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(8, test_case_t{TEST_READ, 0x00008001, 0x0});
            test_args[0].test_cases.emplace_back(10, test_case_t{TEST_READ, 0x00000001, 0x0});
            test_args[0].test_goldens.emplace_back(10,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});
            break;
        case 7:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[0].test_cases.emplace_back(30, test_case_t{TEST_READ, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(32, test_case_t{TEST_READ, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(34, test_case_t{TEST_READ, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(36, test_case_t{TEST_READ, 0x00008001, 0x0});
            test_args[1].test_cases.emplace_back(50, test_case_t{TEST_READ, 0x00000001, 0x0});
            test_args[1].test_goldens.emplace_back(50,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 8:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{TEST_WRITE, 0x00000101, 0x200});

            test_args[0].test_cases.emplace_back(42, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(42,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[2].test_cases.emplace_back(52, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(52,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 9:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});

            test_args[0].test_cases.emplace_back(32, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(32, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_cases.emplace_back(42, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(42, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 10:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_WRITE, 0x00000101, 0x200});

            test_args[0].test_cases.emplace_back(32, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(32,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_cases.emplace_back(42, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(42,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 11:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(50, test_case_t{TEST_READ, 0x00000101, 0x0});

            test_args[2].test_cases.emplace_back(71, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(71, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 12:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(100, test_case_t{TEST_WRITE, 0x00000101, 0x200});

            test_args[2].test_cases.emplace_back(121, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(121,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[1].test_cases.emplace_back(111, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(111,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_cases.emplace_back(132, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(132,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[0].test_cases.emplace_back(132, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(132,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            break;
        case 14:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(25, test_case_t{TEST_READ, 0x00000101, 0x0});

            test_args[2].test_cases.emplace_back(56, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(56, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 15:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});

            test_args[0].test_cases.emplace_back(22, test_case_t{TEST_READ, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(24, test_case_t{TEST_READ, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(26, test_case_t{TEST_READ, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(28, test_case_t{TEST_READ, 0x00008001, 0x0});

            test_args[1].test_cases.emplace_back(50, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(50,
                                                   test_result_t{EXCLUSIVE, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 16:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(25, test_case_t{TEST_WRITE, 0x00000101, 0x200});

            test_args[0].test_cases.emplace_back(68, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(68,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[1].test_cases.emplace_back(68, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(68,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[2].test_cases.emplace_back(67, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(67,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 17:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_cases.emplace_back(50, test_case_t{TEST_READ, 0x00000101, 0x0});

            test_args[1].test_cases.emplace_back(71, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(71, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 18:
            test_args[0].test_cases.emplace_back(0, test_case_t{TEST_WRITE, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_cases.emplace_back(100, test_case_t{TEST_WRITE, 0x00000101, 0x200});

            test_args[1].test_cases.emplace_back(101, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[1].test_goldens.emplace_back(101,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[2].test_cases.emplace_back(113, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[2].test_goldens.emplace_back(113,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[0].test_cases.emplace_back(113, test_case_t{TEST_READ, 0x00000101, 0x0});
            test_args[0].test_goldens.emplace_back(113,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 30:
            for (int i = 0; i < 32; i++) {
                test_args[i].random_generator.seed(i * 10);
                test_args[i].addr_range = 32767;
            }
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
                std::cout << "Processor: " << i << " Checking..." << std::endl;
                if (test_args[i].test_goldens.size() != test_args[i].test_results.size()) {
                    ERROR("Test numbers are different.")
                }
                for (int j = 0; j < test_args[i].test_goldens.size(); j++) {
                    std::cout << "Processor: " << i << " Checking record " << j << std::endl;
                    test_result_t test_result = test_args[i].test_results[j].second;
                    test_result_t test_golden = test_args[i].test_goldens[j].second;
                    if (test_result.data != test_golden.data) {
                        std::cout << "Cycle: " << test_args[i].test_results[j].first << ", Data result: "
                                  << test_result.data << ", Data expected: " << test_golden.data << std::endl;
                        ERROR("Test data error")
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
