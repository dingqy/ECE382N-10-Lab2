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
            test_args[0].test_goldens.emplace_back(1, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x1, 0x1, 0x0});
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
            test_args[1].test_goldens.emplace_back(1, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x1, 0x1, 0x0});
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
            test_args[0].test_goldens.emplace_back(1, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x1, 0x1, 0x0});
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
            test_args[1].test_goldens.emplace_back(21, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x1, 0x1, 0x0});
            break;
        case 5:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(32, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(32, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x0, 0x1,
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
            test_args[0].test_cases.emplace_back(30, test_case_t{false, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(32, test_case_t{false, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(34, test_case_t{false, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(36, test_case_t{false, 0x00008001, 0x0});
            test_args[1].test_records.emplace_back(50, test_record_t{false, 0x00000001});
            test_args[1].test_goldens.emplace_back(50,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 8:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(32, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(32, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x1, 0x0});

            test_args[0].test_records.emplace_back(42, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(42,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(53, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x4, 0x2});
            test_args[2].test_records.emplace_back(52, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(52,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 9:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(22, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(22, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x0, 0x1,
                                                                     0x0});

            test_args[0].test_records.emplace_back(32, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(32, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(42, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(42, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0x3, 0x0});
            test_args[1].test_records.emplace_back(42, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(42, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 10:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(22, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(22, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x1, 0x0});

            test_args[0].test_records.emplace_back(32, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(32,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(42, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(42, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x0, 0x2, 0x1});
            test_args[1].test_records.emplace_back(42, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(42,
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
            test_args[1].test_goldens.emplace_back(111, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x5, 0x2});

            test_args[2].test_records.emplace_back(121, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(121,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(111, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(111,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(132, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(132,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[0].test_records.emplace_back(132, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(132,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(143, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(143, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x4, 0x2});
            break;
        case 13:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(42, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(42, test_result_t{INVALID, DIR_SHARED, 0x00000001, 0x100, 0x3, 0x0});

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

            test_args[2].test_records.emplace_back(56, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(56, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
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
            test_args[1].test_goldens.emplace_back(50, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x2, 0x1});
            test_args[1].test_records.emplace_back(50, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(50,
                                                   test_result_t{EXCLUSIVE, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 16:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(25, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(36, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(36, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x0, 0x1,
                                                                     0x0});

            test_args[1].test_records.emplace_back(57, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(57, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x5, 0x2});

            test_args[0].test_records.emplace_back(68, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(68,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[1].test_records.emplace_back(68, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(68,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(78, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(78, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x4, 0x2});

            test_args[2].test_records.emplace_back(67, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(67,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 17:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[1].test_cases.emplace_back(50, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(71, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(71, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            test_args[1].test_records.emplace_back(71, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(71, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0x7, 0x0});
            break;
        case 18:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[1].test_cases.emplace_back(100, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(101, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(101, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x7, 0x1});

            test_args[1].test_records.emplace_back(101, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(101,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(123, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(123, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x2, 0x1});

            test_args[2].test_records.emplace_back(113, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(113,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[0].test_records.emplace_back(113, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(113,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 19:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(42, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(42, test_result_t{INVALID, DIR_SHARED, 0x00000001, 0x100, 0x3, 0x0});

            test_args[1].test_cases.emplace_back(72, test_case_t{false, 0x00002101, 0x0});
            test_args[1].test_cases.emplace_back(74, test_case_t{false, 0x00004101, 0x0});
            test_args[1].test_cases.emplace_back(76, test_case_t{false, 0x00006101, 0x0});
            test_args[1].test_cases.emplace_back(78, test_case_t{false, 0x00008101, 0x0});

            test_args[1].test_records.emplace_back(80, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(80, test_result_t{INVALID, DIR_SHARED, 0x00000001, 0x100, 0x1, 0x0});
            break;
        case 20:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(42, test_case_t{true, 0x00000101, 0x200});
            test_args[0].test_cases.emplace_back(50, test_case_t{true, 0x00000101, 0x300});

            test_args[1].test_records.emplace_back(53, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x5, 0x2});

            test_args[0].test_records.emplace_back(63, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(63,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});

            test_args[2].test_records.emplace_back(63, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(63,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});

            test_args[0].test_records.emplace_back(71, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(71,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(73, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(73, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x4, 0x2});

            test_args[1].test_records.emplace_back(82, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(82, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x4, 0x2});

            test_args[2].test_records.emplace_back(91, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(91,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});
            test_args[2].test_records.emplace_back(92, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(92,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});

            test_args[0].test_records.emplace_back(102, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(102,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x300, 0x0, 0x0});

            test_args[1].test_records.emplace_back(103, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(103, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x1, 0x0});

            break;
        case 21:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(42, test_case_t{true, 0x00000101, 0x200});
            test_args[3].test_cases.emplace_back(50, test_case_t{true, 0x00000101, 0x300});

            test_args[1].test_records.emplace_back(53, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x5, 0x2});

            test_args[0].test_records.emplace_back(63, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(63,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});

            test_args[2].test_records.emplace_back(63, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(63,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});

            test_args[2].test_records.emplace_back(70, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(70,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});
            test_args[2].test_records.emplace_back(71, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(71,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(73, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(73, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x4, 0x2});

            test_args[1].test_records.emplace_back(81, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(81, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x4, 0x2});

            test_args[3].test_records.emplace_back(81, test_record_t{true, 0x00000101});
            test_args[3].test_goldens.emplace_back(81,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x300, 0x0, 0x0});

            test_args[1].test_records.emplace_back(82, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(82, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x8, 0x3});
            break;
        case 22:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(42, test_case_t{true, 0x00000101, 0x200});
            test_args[1].test_cases.emplace_back(54, test_case_t{true, 0x00000101, 0x300});

            test_args[1].test_records.emplace_back(53, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x5, 0x2});
            test_args[1].test_records.emplace_back(55, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(55, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x5, 0x2});

            test_args[0].test_records.emplace_back(63, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(63,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x100, 0x0, 0x0});

            test_args[2].test_records.emplace_back(63, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(63,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});

            test_args[2].test_records.emplace_back(65, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(65,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000001, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(75, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(75, test_result_t{INVALID, DIR_OWNED, 0x00000001, 0x100, 0x2, 0x1});

            test_args[1].test_records.emplace_back(75, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(75,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000001, 0x300, 0x0, 0x0});
            break;
        case 23:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[1].test_cases.emplace_back(35, test_case_t{false, 0x00000101, 0x0});

            test_args[2].test_records.emplace_back(56, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(56, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            break;
        case 24:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[1].test_cases.emplace_back(35, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(36, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(36, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x0, 0x1,
                                                                     0x0});

            // 52 - Node 2
            // 53 - Node 1
            test_args[2].test_records.emplace_back(52, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(52,
                                                   test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(53, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(53, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0x5, 0x0});

            test_args[1].test_records.emplace_back(54, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(54, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x7, 0x1});

            test_args[1].test_records.emplace_back(54, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(54,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[0].test_records.emplace_back(64, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(64,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[2].test_records.emplace_back(64, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(64,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_records.emplace_back(75, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(75, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x2, 0x1});

            break;
        case 25:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            for (int i = 2; i < 32; i++) {
                test_args[i].test_cases.emplace_back(50, test_case_t{false, 0x00000101, 0x0});
            }
            test_args[1].test_records.emplace_back(1000, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(1000,
                                                   test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0xFFFFFFFF,
                                                                 0x0});

            test_args[0].test_cases.emplace_back(1000, test_case_t{true, 0x00000101, 0x200});
            for (int i = 1; i < 32; i++) {
                test_args[i].test_records.emplace_back(2000, test_record_t{true, 0x00000101});
                test_args[i].test_goldens.emplace_back(2000, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0,
                                                                           0x0});
            }
            test_args[0].test_records.emplace_back(2000, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(2000,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 26:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            for (int i = 2; i < 32; i++) {
                test_args[i].test_cases.emplace_back(50, test_case_t{false, 0x00000101, 0x0});
            }
            test_args[1].test_records.emplace_back(1000, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(1000,
                                                   test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x100, 0xFFFFFFFF,
                                                                 0x0});

            test_args[1].test_records.emplace_back(1000, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(1000,
                                                   test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});

            test_args[1].test_cases.emplace_back(1000, test_case_t{true, 0x00000101, 0x200});
            test_args[0].test_records.emplace_back(2000, test_record_t{true, 0x00000101});
            test_args[0].test_goldens.emplace_back(2000,
                                                   test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0, 0x0});
            for (int i = 2; i < 32; i++) {
                test_args[i].test_records.emplace_back(2000, test_record_t{true, 0x00000101});
                test_args[i].test_goldens.emplace_back(2000, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x100, 0x0,
                                                                           0x0});
            }
            for (int i = 0; i < 100; i++) {
                test_args[1].test_records.emplace_back(1001 + i, test_record_t{true, 0x00000101});
                test_args[1].test_goldens.emplace_back(1001 + i,
                                                       test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0,
                                                                     0x0});
            }
            test_args[1].test_records.emplace_back(2000, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(2000,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
            break;
        case 27:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[3].test_cases.emplace_back(60, test_case_t{true, 0x00000101, 0x200});
            test_args[4].test_cases.emplace_back(65, test_case_t{false, 0x00000101, 0x0});
            test_args[1].test_records.emplace_back(71, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(71, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0xD, 0x3});

            test_args[1].test_records.emplace_back(76, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(76, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0xD, 0x3});

            test_args[4].test_records.emplace_back(86, test_record_t{true, 0x00000101});
            test_args[4].test_goldens.emplace_back(86, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x0, 0x0, 0x0});

            test_args[1].test_records.emplace_back(92, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(92, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x8, 0x3});

            test_args[1].test_records.emplace_back(97, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(97, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x100, 0x8, 0x3});

            test_args[3].test_records.emplace_back(107, test_record_t{true, 0x00000101});
            test_args[3].test_goldens.emplace_back(107, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[4].test_records.emplace_back(117, test_record_t{true, 0x00000101});
            test_args[4].test_goldens.emplace_back(117, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(118, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(118, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x200, 0x18, 0x0});
            break;
        case 28:
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000201, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000301, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000401, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000501, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000611, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000711, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000811, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000911, 0x100});
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x00000A21, 0x100});

            test_args[2].test_cases.emplace_back(500, test_case_t{false, 0x00000201, 0x0});
            test_args[3].test_cases.emplace_back(500, test_case_t{false, 0x00000301, 0x0});
            test_args[4].test_cases.emplace_back(500, test_case_t{false, 0x00000401, 0x0});
            test_args[5].test_cases.emplace_back(500, test_case_t{false, 0x00000501, 0x0});
            test_args[6].test_cases.emplace_back(500, test_case_t{false, 0x00000611, 0x0});
            test_args[7].test_cases.emplace_back(500, test_case_t{false, 0x00000711, 0x0});
            test_args[8].test_cases.emplace_back(500, test_case_t{false, 0x00000811, 0x0});
            test_args[9].test_cases.emplace_back(500, test_case_t{false, 0x00000911, 0x0});
            test_args[10].test_cases.emplace_back(500, test_case_t{false, 0x00000A21, 0x0});

            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00000C01, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00000D01, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00000E01, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00000F01, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00001011, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00001111, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00001211, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00001311, 0x100});
            test_args[11].test_cases.emplace_back(0, test_case_t{true, 0x00001421, 0x100});

            test_args[12].test_cases.emplace_back(500, test_case_t{false, 0x00000C01, 0x0});
            test_args[13].test_cases.emplace_back(500, test_case_t{false, 0x00000B01, 0x0});
            test_args[14].test_cases.emplace_back(500, test_case_t{false, 0x00000E01, 0x0});
            test_args[15].test_cases.emplace_back(500, test_case_t{false, 0x00000F01, 0x0});
            test_args[16].test_cases.emplace_back(500, test_case_t{false, 0x00001011, 0x0});
            test_args[17].test_cases.emplace_back(500, test_case_t{false, 0x00001111, 0x0});
            test_args[18].test_cases.emplace_back(500, test_case_t{false, 0x00001211, 0x0});
            test_args[19].test_cases.emplace_back(500, test_case_t{false, 0x00001311, 0x0});
            test_args[20].test_cases.emplace_back(500, test_case_t{false, 0x00001421, 0x0});

            test_args[31].test_cases.emplace_back(1000, test_case_t{true, 0x00005F21, 0x100});
            for (int i = 0; i < 31; i++) {
                test_args[i].test_cases.emplace_back(1000, test_case_t{false, 0x00005F21, 0x0});
            }

            test_args[31].test_records.emplace_back(1500, test_record_t{false, 0x00005F21});
            test_args[31].test_goldens.emplace_back(1500,
                                                    test_result_t{INVALID, DIR_SHARED, 0x00005F21, 0x100, 0xFFFFFFFF,
                                                                  0x0});

            test_args[31].test_cases.emplace_back(1500, test_case_t{true, 0x00003F21, 0x200});
            for (int i = 0; i < 31; i++) {
                test_args[i].test_cases.emplace_back(1500, test_case_t{false, 0x00003F21, 0x0});
            }

            test_args[31].test_records.emplace_back(2000, test_record_t{false, 0x00003F21});
            test_args[31].test_goldens.emplace_back(2000,
                                                    test_result_t{INVALID, DIR_SHARED, 0x00003F21, 0x200, 0xFFFFFFFF,
                                                                  0x0});

            test_args[2].test_cases.emplace_back(2000, test_case_t{true, 0x00000201, 0x0});
            test_args[3].test_cases.emplace_back(2000, test_case_t{true, 0x00000301, 0x0});
            test_args[4].test_cases.emplace_back(2000, test_case_t{true, 0x00000401, 0x0});
            test_args[5].test_cases.emplace_back(2000, test_case_t{true, 0x00000501, 0x0});
            test_args[6].test_cases.emplace_back(2000, test_case_t{true, 0x00000611, 0x0});
            test_args[7].test_cases.emplace_back(2000, test_case_t{true, 0x00000711, 0x0});
            test_args[8].test_cases.emplace_back(2000, test_case_t{true, 0x00000811, 0x0});
            test_args[9].test_cases.emplace_back(2000, test_case_t{true, 0x00000911, 0x0});
            test_args[10].test_cases.emplace_back(2000, test_case_t{true, 0x00000A21, 0x0});

            test_args[12].test_cases.emplace_back(2000, test_case_t{true, 0x00000C01, 0x0});
            test_args[13].test_cases.emplace_back(2000, test_case_t{true, 0x00000D01, 0x0});
            test_args[14].test_cases.emplace_back(2000, test_case_t{true, 0x00000E01, 0x0});
            test_args[15].test_cases.emplace_back(2000, test_case_t{true, 0x00000F01, 0x0});
            test_args[16].test_cases.emplace_back(2000, test_case_t{true, 0x00001011, 0x0});
            test_args[17].test_cases.emplace_back(2000, test_case_t{true, 0x00001111, 0x0});
            test_args[18].test_cases.emplace_back(2000, test_case_t{true, 0x00001211, 0x0});
            test_args[19].test_cases.emplace_back(2000, test_case_t{true, 0x00001311, 0x0});
            test_args[20].test_cases.emplace_back(2000, test_case_t{true, 0x00001421, 0x0});

            test_args[31].test_cases.emplace_back(2000, test_case_t{true, 0x00005F21, 0x300});
            test_args[31].test_cases.emplace_back(2000, test_case_t{true, 0x00003F21, 0x400});

            test_args[31].test_records.emplace_back(3000, test_record_t{true, 0x00005F21});
            test_args[31].test_goldens.emplace_back(3000,
                                                    test_result_t{MODIFIED, DIR_INVALID, 0x00005F21, 0x300, 0x0, 0x0});

            test_args[31].test_records.emplace_back(3000, test_record_t{true, 0x00003F21});
            test_args[31].test_goldens.emplace_back(3000,
                                                    test_result_t{MODIFIED, DIR_INVALID, 0x00003F21, 0x400, 0x0, 0x0});
            break;
        case 29:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[1].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[2].test_cases.emplace_back(50, test_case_t{true, 0x00000101, 0x200});

            test_args[1].test_records.emplace_back(61, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(61,
                                                    test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x5, 0x2});

            test_args[0].test_cases.emplace_back(52, test_case_t{false, 0x00002001, 0x0});
            test_args[0].test_cases.emplace_back(54, test_case_t{false, 0x00004001, 0x0});
            test_args[0].test_cases.emplace_back(56, test_case_t{false, 0x00006001, 0x0});
            test_args[0].test_cases.emplace_back(58, test_case_t{false, 0x00008001, 0x0});

            test_args[1].test_records.emplace_back(70, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(70,
                                                   test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x4, 0x2});

            test_args[1].test_records.emplace_back(81, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(81,
                                                   test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x4, 0x2});

            test_args[2].test_records.emplace_back(71, test_record_t{true, 0x00000101});
            test_args[2].test_goldens.emplace_back(71,
                                                   test_result_t{MODIFIED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});
        case 30:
            for (int i = 0; i < 32; i++) {
                test_args[i].random_generator.seed(i * 10);
                test_args[i].addr_range = 32767;
            }
            break;
        case 31:
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 0x00003F21, 0x200});
            for (int i = 0; i < 31; i++) {
                test_args[i].test_cases.emplace_back(0, test_case_t{false, 0x00003F21, 0x0});
            }

            test_args[31].test_records.emplace_back(500, test_record_t{false, 0x00003F21});
            test_args[31].test_goldens.emplace_back(500,
                                                    test_result_t{INVALID, DIR_SHARED, 0x00003F21, 0x200, 0xFFFFFFFF,
                                                                  0x0});
            break;
        case 32:
            test_args[0].test_cases.emplace_back(0, test_case_t{true, 0x00000101, 0x100});
            test_args[2].test_cases.emplace_back(21, test_case_t{false, 0x00000101, 0x0});
            test_args[3].test_cases.emplace_back(60, test_case_t{true, 0x00000101, 0x200});
            test_args[1].test_cases.emplace_back(75, test_case_t{false, 0x00000101, 0x0});

            test_args[1].test_records.emplace_back(71, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(71, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0xD, 0x3});

            test_args[1].test_records.emplace_back(76, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(76, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0xD, 0x3});

            test_args[1].test_records.emplace_back(76, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(76, test_result_t{INVALID, DIR_INVALID, 0x00000101, 0x0, 0x0, 0x0});

            test_args[1].test_records.emplace_back(92, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(92, test_result_t{INVALID, DIR_OWNED, 0x00000101, 0x100, 0x8, 0x3});

            test_args[1].test_records.emplace_back(93, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(93, test_result_t{INVALID, DIR_SHARED_NO_DATA, 0x00000101, 0x100, 0x8, 0x3});

            test_args[3].test_records.emplace_back(103, test_record_t{true, 0x00000101});
            test_args[3].test_goldens.emplace_back(103, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(113, test_record_t{true, 0x00000101});
            test_args[1].test_goldens.emplace_back(113, test_result_t{SHARED, DIR_INVALID, 0x00000101, 0x200, 0x0, 0x0});

            test_args[1].test_records.emplace_back(113, test_record_t{false, 0x00000101});
            test_args[1].test_goldens.emplace_back(113, test_result_t{INVALID, DIR_SHARED, 0x00000101, 0x200, 0xA, 0x0});
            break;
        case 33:
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 35, 0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 38, 0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 41, 0});

            test_args[16].test_cases.emplace_back(100, test_case_t{true, 12584, 97});
            test_args[16].test_cases.emplace_back(102, test_case_t{true, 20263, 185});
            test_args[16].test_cases.emplace_back(104, test_case_t{false, 11807, 251});
            test_args[16].test_cases.emplace_back(106, test_case_t{true, 3493, 273});
            test_args[16].test_cases.emplace_back(108, test_case_t{true, 31277, 296});
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
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
                std::cout << "Processor: " << i << " Checking..." << std::endl;
                for (int j = 0; j < test_args[i].test_goldens.size(); j++) {
                    std::cout << "Processor: " << i << " Checking record " << j << std::endl;
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
                        if (test_result.sharer_list != test_golden.sharer_list) {
                            ERROR("Directory sharer list error (Shared-no-data/Owned)")
                        }
                    }
                    if (test_golden.mem_state == DIR_SHARED) {
                        if (test_result.sharer_list != test_golden.sharer_list) {
                            ERROR("Directory sharer list error (Shared)")
                        }
                    }
                    if (test_golden.mem_state == DIR_INVALID && test_golden.cache_state == INVALID) {
                        if (test_result.data != test_golden.data) {
                            ERROR("Write back data error")
                        }
                        if (test_result.sharer_list != test_golden.sharer_list) {
                            ERROR("Directory sharer list error (Invalid)")
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
