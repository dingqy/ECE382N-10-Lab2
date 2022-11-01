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
        case 30:
            for (int i = 0; i < 32; i++) {
                test_args[i].random_generator.seed(i * 10);
                test_args[i].addr_range = 767;
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
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[2].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[3].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[4].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[5].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[6].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[7].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[8].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[9].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[10].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[11].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[12].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[13].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 0x0, 0x0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[17].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[18].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[19].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[20].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[21].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[22].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[23].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[24].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[25].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[26].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[27].test_cases.emplace_back(0, test_case_t{false, 0x1, 0x0});
            test_args[28].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[29].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[30].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 0x1, 0x0});
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0x0, 0x0});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 101, 0x0});
            test_args[0].test_cases.emplace_back(4, test_case_t{false, 580, 0x0});
            break;
        case 33:
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[2].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[3].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[4].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[5].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[6].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[7].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[8].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[9].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[10].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[11].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[12].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[13].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[17].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[18].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[19].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[20].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[21].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[22].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[23].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[24].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[25].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[26].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[27].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[28].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[29].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[30].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 101, 2});
            test_args[0].test_cases.emplace_back(4, test_case_t{false, 580, 4});
            test_args[1].test_cases.emplace_back(22, test_case_t{true, 242, 22});
            test_args[3].test_cases.emplace_back(24, test_case_t{true, 726, 24});
            test_args[4].test_cases.emplace_back(25, test_case_t{true, 200, 25});
            test_args[5].test_cases.emplace_back(26, test_case_t{false, 443, 26});
            test_args[0].test_cases.emplace_back(26, test_case_t{true, 352, 26});
            test_args[6].test_cases.emplace_back(27, test_case_t{false, 685, 27});
            test_args[9].test_cases.emplace_back(33, test_case_t{true, 643, 33});
            test_args[10].test_cases.emplace_back(34, test_case_t{true, 118, 34});
            test_args[12].test_cases.emplace_back(37, test_case_t{true, 602, 37});
            test_args[14].test_cases.emplace_back(39, test_case_t{true, 318, 39});
            test_args[15].test_cases.emplace_back(40, test_case_t{false, 561, 40});
            test_args[1].test_cases.emplace_back(44, test_case_t{true, 427, 44});
            test_args[1].test_cases.emplace_back(46, test_case_t{false, 450, 46});
            test_args[3].test_cases.emplace_back(46, test_case_t{false, 513, 46});
            test_args[1].test_cases.emplace_back(48, test_case_t{true, 251, 48});
            test_args[4].test_cases.emplace_back(48, test_case_t{false, 172, 48});
            test_args[5].test_cases.emplace_back(48, test_case_t{true, 599, 48});
            test_args[1].test_cases.emplace_back(49, test_case_t{false, 145, 49});
            test_args[6].test_cases.emplace_back(49, test_case_t{true, 258, 49});
            test_args[9].test_cases.emplace_back(56, test_case_t{false, 3, 56});
            test_args[10].test_cases.emplace_back(56, test_case_t{false, 430, 56});
            test_args[9].test_cases.emplace_back(57, test_case_t{true, 213, 57});
            test_args[12].test_cases.emplace_back(59, test_case_t{false, 516, 59});
            test_args[21].test_cases.emplace_back(60, test_case_t{false, 478, 60});
            test_args[14].test_cases.emplace_back(61, test_case_t{false, 602, 61});
            test_args[15].test_cases.emplace_back(62, test_case_t{true, 261, 62});
            test_args[23].test_cases.emplace_back(63, test_case_t{true, 194, 63});
            test_args[24].test_cases.emplace_back(66, test_case_t{true, 437, 66});
            test_args[3].test_cases.emplace_back(68, test_case_t{false, 583, 68});
            test_args[4].test_cases.emplace_back(70, test_case_t{true, 265, 70});
            test_args[6].test_cases.emplace_back(71, test_case_t{false, 398, 71});
            test_args[1].test_cases.emplace_back(72, test_case_t{true, 361, 72});
            test_args[1].test_cases.emplace_back(75, test_case_t{false, 605, 75});
            test_args[10].test_cases.emplace_back(78, test_case_t{true, 664, 78});
            test_args[9].test_cases.emplace_back(79, test_case_t{true, 728, 79});
            test_args[5].test_cases.emplace_back(80, test_case_t{true, 716, 80});
            test_args[21].test_cases.emplace_back(83, test_case_t{false, 520, 83});
            test_args[12].test_cases.emplace_back(91, test_case_t{true, 29, 91});
            test_args[14].test_cases.emplace_back(93, test_case_t{false, 162, 93});
            test_args[6].test_cases.emplace_back(94, test_case_t{true, 741, 94});
            test_args[15].test_cases.emplace_back(94, test_case_t{false, 612, 94});
            test_args[23].test_cases.emplace_back(95, test_case_t{true, 606, 95});
            test_args[24].test_cases.emplace_back(98, test_case_t{false, 265, 98});
            test_args[3].test_cases.emplace_back(100, test_case_t{false, 754, 100});
            test_args[10].test_cases.emplace_back(101, test_case_t{true, 212, 101});
            test_args[4].test_cases.emplace_back(102, test_case_t{false, 238, 102});
            test_args[28].test_cases.emplace_back(102, test_case_t{true, 637, 102});
            test_args[5].test_cases.emplace_back(103, test_case_t{false, 490, 103});
            test_args[1].test_cases.emplace_back(107, test_case_t{false, 608, 107});
            test_args[29].test_cases.emplace_back(108, test_case_t{false, 112, 108});
            test_args[9].test_cases.emplace_back(112, test_case_t{false, 542, 112});
            test_args[12].test_cases.emplace_back(114, test_case_t{false, 715, 114});
            test_args[21].test_cases.emplace_back(115, test_case_t{true, 243, 115});
            test_args[6].test_cases.emplace_back(116, test_case_t{true, 105, 116});
            test_args[15].test_cases.emplace_back(117, test_case_t{false, 702, 117});
            test_args[3].test_cases.emplace_back(124, test_case_t{true, 436, 124});
            test_args[4].test_cases.emplace_back(124, test_case_t{false, 582, 124});
            test_args[5].test_cases.emplace_back(125, test_case_t{false, 728, 125});
            test_args[28].test_cases.emplace_back(125, test_case_t{false, 437, 125});
            test_args[14].test_cases.emplace_back(126, test_case_t{false, 451, 126});
            test_args[24].test_cases.emplace_back(130, test_case_t{true, 58, 130});
            test_args[10].test_cases.emplace_back(133, test_case_t{false, 688, 133});
            test_args[9].test_cases.emplace_back(134, test_case_t{false, 179, 134});
            test_args[6].test_cases.emplace_back(138, test_case_t{false, 631, 138});
            test_args[1].test_cases.emplace_back(139, test_case_t{false, 266, 139});
            test_args[15].test_cases.emplace_back(139, test_case_t{true, 648, 139});
            test_args[12].test_cases.emplace_back(146, test_case_t{true, 211, 146});
            test_args[21].test_cases.emplace_back(147, test_case_t{false, 676, 147});
            test_args[14].test_cases.emplace_back(151, test_case_t{false, 502, 151});
            test_args[3].test_cases.emplace_back(156, test_case_t{false, 315, 156});
            test_args[4].test_cases.emplace_back(156, test_case_t{true, 677, 156});
            test_args[5].test_cases.emplace_back(157, test_case_t{true, 270, 157});
            test_args[9].test_cases.emplace_back(160, test_case_t{true, 75, 160});
            test_args[28].test_cases.emplace_back(160, test_case_t{false, 324, 160});
            test_args[1].test_cases.emplace_back(162, test_case_t{true, 641, 162});
            test_args[24].test_cases.emplace_back(162, test_case_t{false, 663, 162});
            test_args[10].test_cases.emplace_back(165, test_case_t{false, 541, 165});
            test_args[6].test_cases.emplace_back(171, test_case_t{false, 562, 171});
            test_args[15].test_cases.emplace_back(171, test_case_t{true, 43, 171});
            test_args[14].test_cases.emplace_back(173, test_case_t{false, 450, 173});
            test_args[14].test_cases.emplace_back(174, test_case_t{false, 31, 174});
            test_args[12].test_cases.emplace_back(178, test_case_t{true, 495, 178});
            test_args[5].test_cases.emplace_back(179, test_case_t{true, 724, 179});
            test_args[21].test_cases.emplace_back(179, test_case_t{true, 753, 179});
            test_args[3].test_cases.emplace_back(188, test_case_t{false, 281, 188});
            test_args[30].test_cases.emplace_back(190, test_case_t{true, 354, 190});
            test_args[15].test_cases.emplace_back(193, test_case_t{false, 637, 193});
            test_args[1].test_cases.emplace_back(194, test_case_t{true, 149, 194});
            test_args[24].test_cases.emplace_back(196, test_case_t{true, 422, 196});
            test_args[10].test_cases.emplace_back(197, test_case_t{true, 680, 197});
            test_args[29].test_cases.emplace_back(197, test_case_t{true, 96, 197});
            test_args[4].test_cases.emplace_back(200, test_case_t{true, 118, 200});
            test_args[6].test_cases.emplace_back(204, test_case_t{true, 581, 204});
            break;
        case 34:
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[2].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[3].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[4].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[5].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[6].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[7].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[8].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[9].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[10].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[11].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[12].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[13].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[17].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[18].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[19].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[20].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[21].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[22].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[23].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[24].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[25].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[26].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[27].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[28].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[29].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[30].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 101, 2});
            test_args[0].test_cases.emplace_back(4, test_case_t{false, 580, 4});
            test_args[1].test_cases.emplace_back(22, test_case_t{true, 242, 22});
            test_args[3].test_cases.emplace_back(24, test_case_t{true, 726, 24});
            test_args[4].test_cases.emplace_back(25, test_case_t{true, 200, 25});
            test_args[5].test_cases.emplace_back(26, test_case_t{false, 443, 26});
            test_args[0].test_cases.emplace_back(26, test_case_t{true, 352, 26});
            test_args[6].test_cases.emplace_back(27, test_case_t{false, 685, 27});
            test_args[9].test_cases.emplace_back(33, test_case_t{true, 643, 33});
            test_args[10].test_cases.emplace_back(34, test_case_t{true, 118, 34});
            test_args[12].test_cases.emplace_back(37, test_case_t{true, 602, 37});
            test_args[14].test_cases.emplace_back(39, test_case_t{true, 318, 39});
            test_args[15].test_cases.emplace_back(40, test_case_t{false, 561, 40});
            test_args[1].test_cases.emplace_back(44, test_case_t{true, 427, 44});
            test_args[1].test_cases.emplace_back(46, test_case_t{false, 450, 46});
            test_args[3].test_cases.emplace_back(46, test_case_t{false, 513, 46});
            test_args[1].test_cases.emplace_back(48, test_case_t{true, 251, 48});
            test_args[4].test_cases.emplace_back(48, test_case_t{false, 172, 48});
            test_args[5].test_cases.emplace_back(48, test_case_t{true, 599, 48});
            test_args[1].test_cases.emplace_back(49, test_case_t{false, 145, 49});
            test_args[6].test_cases.emplace_back(49, test_case_t{true, 258, 49});
            test_args[9].test_cases.emplace_back(56, test_case_t{false, 3, 56});
            test_args[10].test_cases.emplace_back(56, test_case_t{false, 430, 56});
            test_args[9].test_cases.emplace_back(57, test_case_t{true, 213, 57});
            test_args[12].test_cases.emplace_back(59, test_case_t{false, 516, 59});
            test_args[21].test_cases.emplace_back(60, test_case_t{false, 478, 60});
            test_args[14].test_cases.emplace_back(61, test_case_t{false, 602, 61});
            test_args[15].test_cases.emplace_back(62, test_case_t{true, 261, 62});
            test_args[23].test_cases.emplace_back(63, test_case_t{true, 194, 63});
            test_args[24].test_cases.emplace_back(66, test_case_t{true, 437, 66});
            test_args[3].test_cases.emplace_back(68, test_case_t{false, 583, 68});
            test_args[4].test_cases.emplace_back(70, test_case_t{true, 265, 70});
            test_args[6].test_cases.emplace_back(71, test_case_t{false, 398, 71});
            test_args[1].test_cases.emplace_back(72, test_case_t{true, 361, 72});
            test_args[1].test_cases.emplace_back(75, test_case_t{false, 605, 75});
            test_args[10].test_cases.emplace_back(78, test_case_t{true, 664, 78});
            test_args[9].test_cases.emplace_back(79, test_case_t{true, 728, 79});
            test_args[5].test_cases.emplace_back(80, test_case_t{true, 716, 80});
            test_args[21].test_cases.emplace_back(83, test_case_t{false, 520, 83});
            test_args[12].test_cases.emplace_back(91, test_case_t{true, 29, 91});
            test_args[14].test_cases.emplace_back(93, test_case_t{false, 162, 93});
            test_args[6].test_cases.emplace_back(94, test_case_t{true, 741, 94});
            test_args[15].test_cases.emplace_back(94, test_case_t{false, 612, 94});
            test_args[23].test_cases.emplace_back(95, test_case_t{true, 606, 95});
            test_args[24].test_cases.emplace_back(98, test_case_t{false, 265, 98});
            test_args[3].test_cases.emplace_back(100, test_case_t{false, 754, 100});
            test_args[10].test_cases.emplace_back(101, test_case_t{true, 212, 101});
            test_args[4].test_cases.emplace_back(102, test_case_t{false, 238, 102});
            test_args[28].test_cases.emplace_back(103, test_case_t{true, 637, 103});
            test_args[5].test_cases.emplace_back(104, test_case_t{false, 490, 104});
            test_args[21].test_cases.emplace_back(105, test_case_t{false, 243, 105});
            test_args[1].test_cases.emplace_back(107, test_case_t{false, 608, 107});
            test_args[29].test_cases.emplace_back(109, test_case_t{false, 112, 109});
            test_args[9].test_cases.emplace_back(113, test_case_t{false, 542, 113});
            test_args[12].test_cases.emplace_back(114, test_case_t{true, 715, 114});
            test_args[6].test_cases.emplace_back(116, test_case_t{true, 105, 116});
            test_args[15].test_cases.emplace_back(117, test_case_t{false, 702, 117});
            test_args[23].test_cases.emplace_back(119, test_case_t{true, 375, 119});
            test_args[3].test_cases.emplace_back(122, test_case_t{false, 436, 122});
            test_args[4].test_cases.emplace_back(124, test_case_t{false, 582, 124});
            test_args[28].test_cases.emplace_back(125, test_case_t{false, 437, 125});
            test_args[5].test_cases.emplace_back(126, test_case_t{false, 728, 126});
            test_args[14].test_cases.emplace_back(126, test_case_t{true, 451, 126});
            test_args[24].test_cases.emplace_back(130, test_case_t{false, 58, 130});
            test_args[9].test_cases.emplace_back(135, test_case_t{false, 179, 135});
            test_args[10].test_cases.emplace_back(135, test_case_t{false, 688, 135});
            test_args[1].test_cases.emplace_back(139, test_case_t{false, 266, 139});
            test_args[6].test_cases.emplace_back(139, test_case_t{true, 631, 139});
            test_args[1].test_cases.emplace_back(141, test_case_t{true, 641, 141});
            test_args[15].test_cases.emplace_back(142, test_case_t{false, 648, 142});
            test_args[21].test_cases.emplace_back(142, test_case_t{false, 676, 142});
            test_args[23].test_cases.emplace_back(144, test_case_t{false, 412, 144});
            test_args[4].test_cases.emplace_back(146, test_case_t{true, 677, 146});
            test_args[12].test_cases.emplace_back(146, test_case_t{true, 211, 146});
            test_args[14].test_cases.emplace_back(148, test_case_t{true, 502, 148});
            test_args[24].test_cases.emplace_back(152, test_case_t{false, 663, 152});
            test_args[3].test_cases.emplace_back(155, test_case_t{true, 315, 155});
            test_args[28].test_cases.emplace_back(157, test_case_t{false, 324, 157});
            test_args[5].test_cases.emplace_back(158, test_case_t{false, 270, 158});
            test_args[9].test_cases.emplace_back(160, test_case_t{false, 75, 160});
            test_args[23].test_cases.emplace_back(167, test_case_t{true, 276, 167});
            test_args[10].test_cases.emplace_back(168, test_case_t{false, 541, 168});
            test_args[14].test_cases.emplace_back(170, test_case_t{false, 450, 170});
            test_args[6].test_cases.emplace_back(171, test_case_t{true, 562, 171});
            test_args[14].test_cases.emplace_back(171, test_case_t{true, 31, 171});
            test_args[1].test_cases.emplace_back(173, test_case_t{true, 149, 173});
            test_args[1].test_cases.emplace_back(174, test_case_t{false, 237, 174});
            test_args[15].test_cases.emplace_back(175, test_case_t{true, 43, 175});
            test_args[21].test_cases.emplace_back(176, test_case_t{false, 753, 176});
            test_args[12].test_cases.emplace_back(179, test_case_t{true, 495, 179});
            test_args[28].test_cases.emplace_back(179, test_case_t{true, 134, 179});
            test_args[5].test_cases.emplace_back(180, test_case_t{true, 724, 180});
            test_args[9].test_cases.emplace_back(182, test_case_t{true, 104, 182});
            test_args[24].test_cases.emplace_back(184, test_case_t{true, 422, 184});
            test_args[3].test_cases.emplace_back(187, test_case_t{true, 281, 187});
            test_args[4].test_cases.emplace_back(189, test_case_t{true, 118, 189});
            test_args[23].test_cases.emplace_back(189, test_case_t{true, 629, 189});
            test_args[15].test_cases.emplace_back(198, test_case_t{true, 637, 198});
            test_args[5].test_cases.emplace_back(203, test_case_t{true, 740, 203});
            test_args[6].test_cases.emplace_back(203, test_case_t{false, 581, 203});
            test_args[14].test_cases.emplace_back(203, test_case_t{true, 77, 203});
            test_args[9].test_cases.emplace_back(205, test_case_t{true, 93, 205});
            test_args[1].test_cases.emplace_back(206, test_case_t{false, 265, 206});
            test_args[24].test_cases.emplace_back(206, test_case_t{true, 223, 206});
            test_args[1].test_cases.emplace_back(207, test_case_t{false, 410, 207});
            test_args[21].test_cases.emplace_back(208, test_case_t{true, 675, 208});
            test_args[12].test_cases.emplace_back(211, test_case_t{true, 356, 211});
            test_args[3].test_cases.emplace_back(219, test_case_t{false, 290, 219});
            test_args[23].test_cases.emplace_back(221, test_case_t{false, 106, 221});
            test_args[4].test_cases.emplace_back(223, test_case_t{true, 131, 223});
            test_args[6].test_cases.emplace_back(227, test_case_t{false, 62, 227});
            test_args[1].test_cases.emplace_back(229, test_case_t{true, 228, 229});
            test_args[9].test_cases.emplace_back(229, test_case_t{true, 395, 229});
            test_args[15].test_cases.emplace_back(230, test_case_t{true, 686, 230});
            test_args[12].test_cases.emplace_back(233, test_case_t{false, 395, 233});
            test_args[5].test_cases.emplace_back(235, test_case_t{false, 564, 235});
            test_args[21].test_cases.emplace_back(240, test_case_t{false, 431, 240});
            test_args[3].test_cases.emplace_back(241, test_case_t{true, 31, 241});
            test_args[14].test_cases.emplace_back(241, test_case_t{false, 658, 241});
            test_args[4].test_cases.emplace_back(248, test_case_t{true, 297, 248});
            test_args[24].test_cases.emplace_back(252, test_case_t{false, 712, 252});
            test_args[1].test_cases.emplace_back(253, test_case_t{true, 546, 253});
            test_args[6].test_cases.emplace_back(259, test_case_t{false, 7, 259});
            test_args[6].test_cases.emplace_back(260, test_case_t{true, 126, 260});
            test_args[15].test_cases.emplace_back(262, test_case_t{false, 156, 262});
            test_args[9].test_cases.emplace_back(263, test_case_t{true, 574, 263});
            test_args[14].test_cases.emplace_back(263, test_case_t{true, 530, 263});
            test_args[12].test_cases.emplace_back(265, test_case_t{true, 125, 265});
            test_args[5].test_cases.emplace_back(267, test_case_t{true, 134, 267});
            test_args[21].test_cases.emplace_back(272, test_case_t{false, 500, 272});
            test_args[3].test_cases.emplace_back(274, test_case_t{false, 387, 274});
            test_args[1].test_cases.emplace_back(275, test_case_t{false, 59, 275});
            test_args[4].test_cases.emplace_back(280, test_case_t{true, 261, 280});
            test_args[24].test_cases.emplace_back(284, test_case_t{false, 23, 284});
            test_args[9].test_cases.emplace_back(285, test_case_t{true, 604, 285});
            test_args[6].test_cases.emplace_back(292, test_case_t{false, 658, 292});
            test_args[15].test_cases.emplace_back(296, test_case_t{false, 403, 296});
            test_args[1].test_cases.emplace_back(297, test_case_t{false, 640, 297});
            test_args[1].test_cases.emplace_back(298, test_case_t{false, 513, 298});
            test_args[12].test_cases.emplace_back(298, test_case_t{false, 15, 298});
            test_args[12].test_cases.emplace_back(299, test_case_t{true, 253, 299});
            test_args[5].test_cases.emplace_back(300, test_case_t{false, 745, 300});
            test_args[5].test_cases.emplace_back(301, test_case_t{true, 421, 301});
            test_args[4].test_cases.emplace_back(304, test_case_t{true, 596, 304});
            test_args[21].test_cases.emplace_back(304, test_case_t{true, 219, 304});
            test_args[3].test_cases.emplace_back(308, test_case_t{true, 447, 308});
            test_args[6].test_cases.emplace_back(314, test_case_t{true, 57, 314});
            test_args[9].test_cases.emplace_back(317, test_case_t{false, 85, 317});
            test_args[9].test_cases.emplace_back(318, test_case_t{false, 623, 318});
            test_args[15].test_cases.emplace_back(318, test_case_t{true, 700, 318});
            test_args[1].test_cases.emplace_back(320, test_case_t{true, 134, 320});
            test_args[24].test_cases.emplace_back(320, test_case_t{false, 250, 320});
            test_args[5].test_cases.emplace_back(323, test_case_t{true, 559, 323});
            test_args[12].test_cases.emplace_back(324, test_case_t{true, 549, 324});
            test_args[3].test_cases.emplace_back(332, test_case_t{false, 713, 332});
            test_args[4].test_cases.emplace_back(336, test_case_t{true, 183, 336});
            test_args[6].test_cases.emplace_back(336, test_case_t{false, 159, 336});
            test_args[21].test_cases.emplace_back(338, test_case_t{true, 411, 338});
            test_args[9].test_cases.emplace_back(340, test_case_t{true, 516, 340});
            test_args[15].test_cases.emplace_back(341, test_case_t{true, 495, 341});
            test_args[1].test_cases.emplace_back(353, test_case_t{true, 666, 353});
            test_args[3].test_cases.emplace_back(354, test_case_t{true, 28, 354});
            test_args[5].test_cases.emplace_back(356, test_case_t{false, 516, 356});
            test_args[12].test_cases.emplace_back(358, test_case_t{false, 114, 358});
            test_args[12].test_cases.emplace_back(359, test_case_t{true, 319, 359});
            test_args[21].test_cases.emplace_back(360, test_case_t{true, 59, 360});
            test_args[6].test_cases.emplace_back(361, test_case_t{false, 600, 361});
            test_args[9].test_cases.emplace_back(362, test_case_t{true, 309, 362});
            test_args[24].test_cases.emplace_back(362, test_case_t{false, 31, 362});
            test_args[24].test_cases.emplace_back(363, test_case_t{false, 506, 363});
            test_args[4].test_cases.emplace_back(369, test_case_t{true, 294, 369});
            test_args[4].test_cases.emplace_back(370, test_case_t{true, 106, 370});
            test_args[15].test_cases.emplace_back(374, test_case_t{true, 142, 374});
            test_args[1].test_cases.emplace_back(375, test_case_t{false, 683, 375});
            test_args[3].test_cases.emplace_back(376, test_case_t{false, 463, 376});
            test_args[24].test_cases.emplace_back(387, test_case_t{false, 331, 387});
            test_args[4].test_cases.emplace_back(392, test_case_t{false, 144, 392});
            test_args[12].test_cases.emplace_back(392, test_case_t{false, 433, 392});
            test_args[9].test_cases.emplace_back(394, test_case_t{false, 532, 394});
            test_args[9].test_cases.emplace_back(395, test_case_t{false, 389, 395});
            test_args[6].test_cases.emplace_back(396, test_case_t{true, 206, 396});
            test_args[9].test_cases.emplace_back(396, test_case_t{true, 12, 396});
            test_args[21].test_cases.emplace_back(396, test_case_t{true, 386, 396});
            test_args[9].test_cases.emplace_back(397, test_case_t{false, 440, 397});
            test_args[15].test_cases.emplace_back(407, test_case_t{false, 14, 407});
            test_args[15].test_cases.emplace_back(408, test_case_t{true, 349, 408});
            test_args[1].test_cases.emplace_back(409, test_case_t{false, 233, 409});
            test_args[1].test_cases.emplace_back(410, test_case_t{true, 354, 410});
            test_args[5].test_cases.emplace_back(410, test_case_t{false, 372, 410});
            break;
        case 35:
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[2].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[3].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[4].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[5].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[6].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[7].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[8].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[9].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[10].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[11].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[12].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[13].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 0, 0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[17].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[18].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[19].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[20].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[21].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[22].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[23].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[24].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[25].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[26].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[27].test_cases.emplace_back(0, test_case_t{false, 1, 0});
            test_args[28].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[29].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[30].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 1, 0});
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 101, 2});
            test_args[0].test_cases.emplace_back(4, test_case_t{false, 580, 4});
            test_args[1].test_cases.emplace_back(22, test_case_t{true, 242, 22});
            test_args[0].test_cases.emplace_back(26, test_case_t{true, 352, 26});
            test_args[2].test_cases.emplace_back(33, test_case_t{true, 484, 33});
            test_args[7].test_cases.emplace_back(38, test_case_t{false, 159, 38});
            test_args[8].test_cases.emplace_back(39, test_case_t{true, 401, 39});
            test_args[11].test_cases.emplace_back(45, test_case_t{false, 360, 45});
            test_args[17].test_cases.emplace_back(45, test_case_t{true, 277, 45});
            test_args[3].test_cases.emplace_back(46, test_case_t{true, 726, 46});
            test_args[13].test_cases.emplace_back(48, test_case_t{true, 76, 48});
            test_args[16].test_cases.emplace_back(51, test_case_t{true, 35, 51});
            test_args[0].test_cases.emplace_back(52, test_case_t{false, 409, 52});
            test_args[2].test_cases.emplace_back(55, test_case_t{true, 86, 55});
            test_args[4].test_cases.emplace_back(57, test_case_t{false, 200, 57});
            test_args[5].test_cases.emplace_back(59, test_case_t{false, 443, 59});
            test_args[7].test_cases.emplace_back(60, test_case_t{true, 685, 60});
            test_args[6].test_cases.emplace_back(61, test_case_t{false, 685, 61});
            test_args[8].test_cases.emplace_back(61, test_case_t{true, 344, 61});
            test_args[9].test_cases.emplace_back(66, test_case_t{false, 643, 66});
            test_args[10].test_cases.emplace_back(68, test_case_t{true, 118, 68});
            test_args[17].test_cases.emplace_back(68, test_case_t{false, 347, 68});
            test_args[12].test_cases.emplace_back(70, test_case_t{false, 602, 70});
            test_args[21].test_cases.emplace_back(72, test_case_t{true, 478, 72});
            test_args[14].test_cases.emplace_back(74, test_case_t{false, 318, 74});
            test_args[13].test_cases.emplace_back(75, test_case_t{false, 175, 75});
            test_args[15].test_cases.emplace_back(76, test_case_t{false, 561, 76});
            test_args[11].test_cases.emplace_back(78, test_case_t{true, 89, 78});
            test_args[5].test_cases.emplace_back(81, test_case_t{true, 599, 81});
            test_args[23].test_cases.emplace_back(81, test_case_t{true, 194, 81});
            test_args[7].test_cases.emplace_back(82, test_case_t{false, 81, 82});
            test_args[8].test_cases.emplace_back(83, test_case_t{true, 531, 83});
            test_args[24].test_cases.emplace_back(83, test_case_t{false, 437, 83});
            test_args[16].test_cases.emplace_back(84, test_case_t{true, 688, 84});
            test_args[25].test_cases.emplace_back(85, test_case_t{false, 679, 85});
            test_args[0].test_cases.emplace_back(85, test_case_t{true, 168, 85});
            test_args[18].test_cases.emplace_back(86, test_case_t{true, 519, 86});
            test_args[2].test_cases.emplace_back(88, test_case_t{true, 132, 88});
            test_args[9].test_cases.emplace_back(88, test_case_t{false, 3, 88});
            test_args[4].test_cases.emplace_back(89, test_case_t{true, 172, 89});
            test_args[9].test_cases.emplace_back(89, test_case_t{false, 213, 89});
            test_args[12].test_cases.emplace_back(92, test_case_t{true, 516, 92});
            test_args[19].test_cases.emplace_back(92, test_case_t{false, 761, 92});
            test_args[6].test_cases.emplace_back(93, test_case_t{true, 258, 93});
            test_args[21].test_cases.emplace_back(94, test_case_t{false, 520, 94});
            test_args[10].test_cases.emplace_back(96, test_case_t{false, 430, 96});
            test_args[20].test_cases.emplace_back(96, test_case_t{true, 236, 96});
            test_args[14].test_cases.emplace_back(97, test_case_t{false, 602, 97});
            test_args[13].test_cases.emplace_back(98, test_case_t{true, 479, 98});
            test_args[15].test_cases.emplace_back(99, test_case_t{false, 261, 99});
            test_args[17].test_cases.emplace_back(100, test_case_t{false, 745, 100});
            test_args[22].test_cases.emplace_back(100, test_case_t{false, 720, 100});
            test_args[26].test_cases.emplace_back(102, test_case_t{false, 153, 102});
            test_args[27].test_cases.emplace_back(103, test_case_t{false, 395, 103});
            test_args[8].test_cases.emplace_back(105, test_case_t{true, 477, 105});
            test_args[16].test_cases.emplace_back(106, test_case_t{true, 294, 106});
            test_args[25].test_cases.emplace_back(107, test_case_t{false, 692, 107});
            test_args[28].test_cases.emplace_back(107, test_case_t{true, 637, 107});
            test_args[18].test_cases.emplace_back(108, test_case_t{false, 6, 108});
            test_args[18].test_cases.emplace_back(109, test_case_t{false, 427, 109});
            test_args[29].test_cases.emplace_back(109, test_case_t{false, 112, 109});
            test_args[2].test_cases.emplace_back(110, test_case_t{false, 503, 110});
            test_args[11].test_cases.emplace_back(110, test_case_t{true, 346, 110});
            test_args[30].test_cases.emplace_back(111, test_case_t{false, 354, 111});
            test_args[5].test_cases.emplace_back(113, test_case_t{false, 716, 113});
            test_args[9].test_cases.emplace_back(113, test_case_t{false, 728, 113});
            test_args[31].test_cases.emplace_back(113, test_case_t{false, 596, 113});
            test_args[23].test_cases.emplace_back(114, test_case_t{true, 606, 114});
            test_args[6].test_cases.emplace_back(115, test_case_t{true, 398, 115});
            test_args[19].test_cases.emplace_back(115, test_case_t{false, 433, 115});
            test_args[24].test_cases.emplace_back(115, test_case_t{false, 265, 115});
            test_args[0].test_cases.emplace_back(116, test_case_t{false, 36, 116});
            test_args[10].test_cases.emplace_back(118, test_case_t{true, 664, 118});
            test_args[20].test_cases.emplace_back(119, test_case_t{true, 92, 119});
            test_args[4].test_cases.emplace_back(122, test_case_t{true, 265, 122});
            test_args[17].test_cases.emplace_back(122, test_case_t{false, 438, 122});
            test_args[22].test_cases.emplace_back(123, test_case_t{true, 179, 123});
            test_args[12].test_cases.emplace_back(124, test_case_t{false, 29, 124});
            test_args[27].test_cases.emplace_back(125, test_case_t{false, 10, 125});
            test_args[21].test_cases.emplace_back(126, test_case_t{false, 243, 126});
            test_args[27].test_cases.emplace_back(126, test_case_t{true, 641, 126});
            test_args[16].test_cases.emplace_back(128, test_case_t{false, 186, 128});
            test_args[14].test_cases.emplace_back(129, test_case_t{false, 162, 129});
            test_args[13].test_cases.emplace_back(130, test_case_t{true, 199, 130});
            test_args[28].test_cases.emplace_back(130, test_case_t{true, 437, 130});
            test_args[15].test_cases.emplace_back(131, test_case_t{true, 612, 131});
            test_args[11].test_cases.emplace_back(132, test_case_t{false, 464, 132});
            test_args[30].test_cases.emplace_back(133, test_case_t{true, 523, 133});
            test_args[2].test_cases.emplace_back(135, test_case_t{false, 291, 135});
            test_args[5].test_cases.emplace_back(136, test_case_t{true, 490, 136});
            test_args[8].test_cases.emplace_back(137, test_case_t{true, 396, 137});
            test_args[26].test_cases.emplace_back(137, test_case_t{true, 351, 137});
            test_args[19].test_cases.emplace_back(138, test_case_t{true, 110, 138});
            test_args[0].test_cases.emplace_back(139, test_case_t{true, 521, 139});
            test_args[10].test_cases.emplace_back(140, test_case_t{true, 212, 140});
            test_args[25].test_cases.emplace_back(140, test_case_t{true, 508, 140});
            test_args[18].test_cases.emplace_back(141, test_case_t{true, 689, 141});
            test_args[29].test_cases.emplace_back(143, test_case_t{true, 96, 143});
            test_args[4].test_cases.emplace_back(144, test_case_t{true, 238, 144});
            test_args[17].test_cases.emplace_back(145, test_case_t{false, 171, 145});
            test_args[22].test_cases.emplace_back(145, test_case_t{true, 693, 145});
            test_args[12].test_cases.emplace_back(146, test_case_t{true, 715, 146});
            test_args[6].test_cases.emplace_back(147, test_case_t{false, 741, 147});
            test_args[9].test_cases.emplace_back(147, test_case_t{true, 542, 147});
            test_args[31].test_cases.emplace_back(148, test_case_t{false, 182, 148});
            test_args[24].test_cases.emplace_back(149, test_case_t{true, 58, 149});
            test_args[20].test_cases.emplace_back(151, test_case_t{true, 560, 151});
            test_args[15].test_cases.emplace_back(153, test_case_t{false, 702, 153});
            test_args[28].test_cases.emplace_back(155, test_case_t{false, 324, 155});
            test_args[27].test_cases.emplace_back(158, test_case_t{true, 650, 158});
            test_args[27].test_cases.emplace_back(159, test_case_t{false, 91, 159});
            test_args[19].test_cases.emplace_back(160, test_case_t{true, 173, 160});
            test_args[23].test_cases.emplace_back(160, test_case_t{true, 375, 160});
            test_args[14].test_cases.emplace_back(161, test_case_t{true, 451, 161});
            test_args[13].test_cases.emplace_back(162, test_case_t{false, 356, 162});
            test_args[18].test_cases.emplace_back(163, test_case_t{false, 316, 163});
            test_args[30].test_cases.emplace_back(165, test_case_t{false, 456, 165});
            test_args[11].test_cases.emplace_back(166, test_case_t{true, 65, 166});
            test_args[2].test_cases.emplace_back(168, test_case_t{false, 722, 168});
            test_args[8].test_cases.emplace_back(169, test_case_t{true, 586, 169});
            test_args[26].test_cases.emplace_back(170, test_case_t{false, 191, 170});
            test_args[5].test_cases.emplace_back(171, test_case_t{true, 728, 171});
            test_args[24].test_cases.emplace_back(171, test_case_t{false, 663, 171});
            test_args[2].test_cases.emplace_back(172, test_case_t{true, 443, 172});
            test_args[25].test_cases.emplace_back(172, test_case_t{false, 147, 172});
            test_args[10].test_cases.emplace_back(173, test_case_t{true, 688, 173});
            test_args[29].test_cases.emplace_back(175, test_case_t{true, 6, 175});
            test_args[0].test_cases.emplace_back(175, test_case_t{true, 521, 175});
            test_args[4].test_cases.emplace_back(176, test_case_t{true, 582, 176});
            test_args[29].test_cases.emplace_back(176, test_case_t{false, 385, 176});
            test_args[0].test_cases.emplace_back(176, test_case_t{false, 717, 176});
            test_args[17].test_cases.emplace_back(177, test_case_t{false, 766, 177});
            test_args[22].test_cases.emplace_back(177, test_case_t{true, 160, 177});
            test_args[12].test_cases.emplace_back(178, test_case_t{false, 211, 178});
            test_args[6].test_cases.emplace_back(180, test_case_t{true, 105, 180});
            test_args[31].test_cases.emplace_back(180, test_case_t{false, 139, 180});
            test_args[19].test_cases.emplace_back(182, test_case_t{false, 462, 182});
            test_args[20].test_cases.emplace_back(183, test_case_t{false, 425, 183});
            test_args[28].test_cases.emplace_back(183, test_case_t{false, 134, 183});
            test_args[23].test_cases.emplace_back(184, test_case_t{false, 412, 184});
            test_args[14].test_cases.emplace_back(187, test_case_t{true, 502, 187});
            test_args[13].test_cases.emplace_back(188, test_case_t{false, 88, 188});
            test_args[27].test_cases.emplace_back(191, test_case_t{true, 539, 191});
            test_args[26].test_cases.emplace_back(192, test_case_t{true, 398, 192});
            test_args[5].test_cases.emplace_back(193, test_case_t{true, 270, 193});
            test_args[25].test_cases.emplace_back(194, test_case_t{true, 568, 194});
            test_args[11].test_cases.emplace_back(199, test_case_t{true, 134, 199});
            test_args[18].test_cases.emplace_back(199, test_case_t{false, 359, 199});
            test_args[30].test_cases.emplace_back(201, test_case_t{false, 637, 201});
            test_args[8].test_cases.emplace_back(205, test_case_t{true, 237, 205});
            test_args[20].test_cases.emplace_back(205, test_case_t{true, 608, 205});
            test_args[24].test_cases.emplace_back(205, test_case_t{false, 422, 205});
            test_args[10].test_cases.emplace_back(206, test_case_t{true, 541, 206});
            test_args[23].test_cases.emplace_back(206, test_case_t{true, 276, 206});
            test_args[2].test_cases.emplace_back(207, test_case_t{false, 449, 207});
            test_args[4].test_cases.emplace_back(208, test_case_t{true, 677, 208});
            test_args[17].test_cases.emplace_back(209, test_case_t{false, 312, 209});
            test_args[29].test_cases.emplace_back(209, test_case_t{true, 382, 209});
            test_args[12].test_cases.emplace_back(210, test_case_t{true, 495, 210});
            test_args[0].test_cases.emplace_back(210, test_case_t{true, 294, 210});
            test_args[15].test_cases.emplace_back(211, test_case_t{true, 648, 211});
            test_args[22].test_cases.emplace_back(211, test_case_t{true, 131, 211});
            test_args[19].test_cases.emplace_back(214, test_case_t{false, 720, 214});
            test_args[6].test_cases.emplace_back(217, test_case_t{false, 631, 217});
            test_args[18].test_cases.emplace_back(221, test_case_t{true, 150, 221});
            test_args[31].test_cases.emplace_back(222, test_case_t{true, 121, 222});
            test_args[14].test_cases.emplace_back(223, test_case_t{false, 450, 223});
            test_args[14].test_cases.emplace_back(224, test_case_t{true, 31, 224});
            test_args[5].test_cases.emplace_back(225, test_case_t{false, 724, 225});
            test_args[27].test_cases.emplace_back(225, test_case_t{false, 225, 225});
            test_args[28].test_cases.emplace_back(225, test_case_t{true, 236, 225});
            test_args[5].test_cases.emplace_back(226, test_case_t{true, 740, 226});
            test_args[24].test_cases.emplace_back(227, test_case_t{true, 223, 227});
            test_args[4].test_cases.emplace_back(230, test_case_t{false, 118, 230});
            test_args[17].test_cases.emplace_back(231, test_case_t{false, 368, 231});
            test_args[22].test_cases.emplace_back(234, test_case_t{false, 268, 234});
            test_args[0].test_cases.emplace_back(235, test_case_t{false, 398, 235});
            test_args[25].test_cases.emplace_back(236, test_case_t{false, 584, 236});
            test_args[8].test_cases.emplace_back(237, test_case_t{false, 263, 237});
            test_args[26].test_cases.emplace_back(237, test_case_t{false, 713, 237});
            test_args[30].test_cases.emplace_back(237, test_case_t{true, 528, 237});
            test_args[20].test_cases.emplace_back(238, test_case_t{true, 314, 238});
            test_args[23].test_cases.emplace_back(238, test_case_t{true, 629, 238});
            test_args[10].test_cases.emplace_back(239, test_case_t{false, 680, 239});
            test_args[29].test_cases.emplace_back(242, test_case_t{false, 493, 242});
            test_args[12].test_cases.emplace_back(243, test_case_t{true, 356, 243});
            test_args[15].test_cases.emplace_back(243, test_case_t{false, 43, 243});
            test_args[18].test_cases.emplace_back(243, test_case_t{true, 209, 243});
            test_args[2].test_cases.emplace_back(244, test_case_t{false, 532, 244});
            test_args[31].test_cases.emplace_back(246, test_case_t{true, 673, 246});
            test_args[19].test_cases.emplace_back(247, test_case_t{false, 755, 247});
            test_args[19].test_cases.emplace_back(248, test_case_t{true, 50, 248});
            test_args[6].test_cases.emplace_back(249, test_case_t{false, 562, 249});
            test_args[24].test_cases.emplace_back(250, test_case_t{false, 712, 250});
            test_args[11].test_cases.emplace_back(254, test_case_t{true, 518, 254});
            test_args[5].test_cases.emplace_back(255, test_case_t{true, 564, 255});
            test_args[14].test_cases.emplace_back(257, test_case_t{false, 77, 257});
            test_args[27].test_cases.emplace_back(259, test_case_t{false, 314, 259});
            test_args[26].test_cases.emplace_back(260, test_case_t{true, 177, 260});
            test_args[20].test_cases.emplace_back(262, test_case_t{false, 593, 262});
            test_args[23].test_cases.emplace_back(262, test_case_t{false, 106, 262});
            test_args[12].test_cases.emplace_back(266, test_case_t{false, 395, 266});
            test_args[2].test_cases.emplace_back(267, test_case_t{true, 514, 267});
            test_args[17].test_cases.emplace_back(269, test_case_t{true, 689, 269});
            test_args[25].test_cases.emplace_back(269, test_case_t{true, 550, 269});
            test_args[22].test_cases.emplace_back(270, test_case_t{false, 268, 270});
            test_args[15].test_cases.emplace_back(271, test_case_t{false, 637, 271});
            test_args[22].test_cases.emplace_back(271, test_case_t{true, 341, 271});
            test_args[8].test_cases.emplace_back(272, test_case_t{false, 595, 272});
            test_args[24].test_cases.emplace_back(272, test_case_t{false, 23, 272});
            test_args[10].test_cases.emplace_back(273, test_case_t{true, 713, 273});
            test_args[29].test_cases.emplace_back(274, test_case_t{true, 668, 274});
            test_args[0].test_cases.emplace_back(274, test_case_t{false, 638, 274});
            test_args[28].test_cases.emplace_back(276, test_case_t{false, 132, 276});
            test_args[28].test_cases.emplace_back(277, test_case_t{false, 63, 277});
            test_args[6].test_cases.emplace_back(281, test_case_t{false, 581, 281});
            test_args[26].test_cases.emplace_back(282, test_case_t{true, 387, 282});
            test_args[18].test_cases.emplace_back(283, test_case_t{false, 187, 283});
            test_args[19].test_cases.emplace_back(285, test_case_t{true, 454, 285});
            test_args[30].test_cases.emplace_back(285, test_case_t{true, 87, 285});
            test_args[4].test_cases.emplace_back(287, test_case_t{true, 131, 287});
            test_args[11].test_cases.emplace_back(288, test_case_t{false, 554, 288});
            test_args[12].test_cases.emplace_back(289, test_case_t{false, 125, 289});
            test_args[14].test_cases.emplace_back(289, test_case_t{true, 658, 289});
            test_args[31].test_cases.emplace_back(289, test_case_t{false, 448, 289});
            test_args[2].test_cases.emplace_back(291, test_case_t{false, 298, 291});
            test_args[25].test_cases.emplace_back(294, test_case_t{false, 632, 294});
            test_args[23].test_cases.emplace_back(295, test_case_t{false, 182, 295});
            test_args[10].test_cases.emplace_back(296, test_case_t{false, 360, 296});
            test_args[20].test_cases.emplace_back(296, test_case_t{true, 659, 296});
            test_args[29].test_cases.emplace_back(297, test_case_t{false, 764, 297});
            test_args[27].test_cases.emplace_back(298, test_case_t{false, 281, 298});
            test_args[5].test_cases.emplace_back(300, test_case_t{false, 134, 300});
            test_args[17].test_cases.emplace_back(301, test_case_t{false, 150, 301});
            test_args[6].test_cases.emplace_back(303, test_case_t{false, 62, 303});
            test_args[15].test_cases.emplace_back(303, test_case_t{true, 686, 303});
            test_args[22].test_cases.emplace_back(304, test_case_t{false, 485, 304});
            test_args[26].test_cases.emplace_back(304, test_case_t{false, 473, 304});
            test_args[8].test_cases.emplace_back(306, test_case_t{false, 522, 306});
            test_args[19].test_cases.emplace_back(307, test_case_t{false, 664, 307});
            test_args[30].test_cases.emplace_back(308, test_case_t{false, 506, 308});
            test_args[0].test_cases.emplace_back(308, test_case_t{true, 26, 308});
            test_args[12].test_cases.emplace_back(311, test_case_t{true, 15, 311});
            test_args[28].test_cases.emplace_back(311, test_case_t{false, 155, 311});
            test_args[18].test_cases.emplace_back(315, test_case_t{false, 23, 315});
            test_args[4].test_cases.emplace_back(320, test_case_t{true, 297, 320});
            test_args[11].test_cases.emplace_back(321, test_case_t{true, 626, 321});
            test_args[14].test_cases.emplace_back(323, test_case_t{true, 530, 323});
            test_args[25].test_cases.emplace_back(323, test_case_t{true, 517, 323});
            test_args[2].test_cases.emplace_back(325, test_case_t{false, 475, 325});
            test_args[22].test_cases.emplace_back(326, test_case_t{true, 284, 326});
            test_args[10].test_cases.emplace_back(328, test_case_t{false, 268, 328});
            test_args[29].test_cases.emplace_back(328, test_case_t{false, 46, 328});
            test_args[8].test_cases.emplace_back(329, test_case_t{true, 424, 329});
            test_args[6].test_cases.emplace_back(330, test_case_t{true, 7, 330});
            test_args[27].test_cases.emplace_back(330, test_case_t{true, 418, 330});
            test_args[0].test_cases.emplace_back(330, test_case_t{true, 41, 330});
            test_args[0].test_cases.emplace_back(332, test_case_t{false, 406, 332});
            test_args[5].test_cases.emplace_back(333, test_case_t{true, 745, 333});
            test_args[0].test_cases.emplace_back(333, test_case_t{true, 515, 333});
            test_args[5].test_cases.emplace_back(334, test_case_t{true, 421, 334});
            test_args[20].test_cases.emplace_back(336, test_case_t{false, 720, 336});
            test_args[17].test_cases.emplace_back(337, test_case_t{false, 231, 337});
            test_args[15].test_cases.emplace_back(338, test_case_t{true, 156, 338});
            test_args[19].test_cases.emplace_back(340, test_case_t{false, 529, 340});
            test_args[30].test_cases.emplace_back(340, test_case_t{false, 605, 340});
            test_args[4].test_cases.emplace_back(342, test_case_t{false, 261, 342});
            test_args[12].test_cases.emplace_back(343, test_case_t{false, 253, 343});
            test_args[11].test_cases.emplace_back(344, test_case_t{false, 142, 344});
            test_args[28].test_cases.emplace_back(344, test_case_t{false, 548, 344});
            test_args[11].test_cases.emplace_back(345, test_case_t{false, 104, 345});
            test_args[25].test_cases.emplace_back(346, test_case_t{false, 672, 346});
            test_args[2].test_cases.emplace_back(347, test_case_t{false, 531, 347});
            test_args[18].test_cases.emplace_back(347, test_case_t{true, 380, 347});
            test_args[22].test_cases.emplace_back(348, test_case_t{true, 208, 348});
            test_args[10].test_cases.emplace_back(350, test_case_t{false, 723, 350});
            test_args[8].test_cases.emplace_back(352, test_case_t{true, 366, 352});
            test_args[14].test_cases.emplace_back(355, test_case_t{false, 551, 355});
            test_args[20].test_cases.emplace_back(358, test_case_t{true, 537, 358});
            test_args[15].test_cases.emplace_back(360, test_case_t{false, 403, 360});
            test_args[6].test_cases.emplace_back(363, test_case_t{false, 126, 363});
            test_args[27].test_cases.emplace_back(363, test_case_t{false, 186, 363});
            test_args[30].test_cases.emplace_back(363, test_case_t{true, 313, 363});
            test_args[4].test_cases.emplace_back(364, test_case_t{true, 596, 364});
            test_args[12].test_cases.emplace_back(365, test_case_t{false, 549, 365});
            test_args[31].test_cases.emplace_back(365, test_case_t{false, 344, 365});
            test_args[0].test_cases.emplace_back(365, test_case_t{false, 5, 365});
            test_args[5].test_cases.emplace_back(366, test_case_t{true, 559, 366});
            test_args[11].test_cases.emplace_back(367, test_case_t{false, 311, 367});
            test_args[2].test_cases.emplace_back(369, test_case_t{true, 53, 369});
            test_args[17].test_cases.emplace_back(369, test_case_t{true, 202, 369});
            test_args[28].test_cases.emplace_back(369, test_case_t{false, 292, 369});
            test_args[18].test_cases.emplace_back(370, test_case_t{true, 440, 370});
            test_args[19].test_cases.emplace_back(372, test_case_t{true, 678, 372});
            test_args[29].test_cases.emplace_back(372, test_case_t{true, 165, 372});
            test_args[10].test_cases.emplace_back(373, test_case_t{true, 74, 373});
            test_args[14].test_cases.emplace_back(377, test_case_t{true, 257, 377});
            test_args[20].test_cases.emplace_back(380, test_case_t{false, 678, 380});
            test_args[25].test_cases.emplace_back(380, test_case_t{true, 655, 380});
            test_args[22].test_cases.emplace_back(381, test_case_t{true, 623, 381});
            test_args[15].test_cases.emplace_back(382, test_case_t{false, 700, 382});
            test_args[15].test_cases.emplace_back(383, test_case_t{true, 495, 383});
            test_args[6].test_cases.emplace_back(385, test_case_t{true, 658, 385});
            test_args[30].test_cases.emplace_back(385, test_case_t{false, 38, 385});
            test_args[4].test_cases.emplace_back(386, test_case_t{true, 183, 386});
            test_args[27].test_cases.emplace_back(386, test_case_t{false, 276, 386});
            test_args[12].test_cases.emplace_back(387, test_case_t{false, 114, 387});
            test_args[0].test_cases.emplace_back(387, test_case_t{false, 294, 387});
            test_args[5].test_cases.emplace_back(388, test_case_t{false, 516, 388});
            test_args[12].test_cases.emplace_back(388, test_case_t{false, 319, 388});
            test_args[2].test_cases.emplace_back(391, test_case_t{false, 456, 391});
            test_args[19].test_cases.emplace_back(394, test_case_t{true, 436, 394});
            test_args[10].test_cases.emplace_back(395, test_case_t{false, 351, 395});
            test_args[31].test_cases.emplace_back(397, test_case_t{true, 446, 397});
            test_args[14].test_cases.emplace_back(399, test_case_t{false, 645, 399});
            test_args[28].test_cases.emplace_back(402, test_case_t{false, 335, 402});
            test_args[17].test_cases.emplace_back(403, test_case_t{false, 673, 403});
            test_args[28].test_cases.emplace_back(403, test_case_t{false, 514, 403});
            test_args[29].test_cases.emplace_back(404, test_case_t{false, 484, 404});
            test_args[29].test_cases.emplace_back(405, test_case_t{false, 752, 405});
            test_args[29].test_cases.emplace_back(406, test_case_t{true, 19, 406});
            test_args[15].test_cases.emplace_back(407, test_case_t{true, 142, 407});
            test_args[30].test_cases.emplace_back(407, test_case_t{false, 633, 407});
            test_args[4].test_cases.emplace_back(408, test_case_t{true, 294, 408});
            test_args[25].test_cases.emplace_back(413, test_case_t{false, 569, 413});
            test_args[22].test_cases.emplace_back(414, test_case_t{false, 465, 414});
            test_args[2].test_cases.emplace_back(415, test_case_t{false, 324, 415});
            test_args[10].test_cases.emplace_back(417, test_case_t{true, 265, 417});
            test_args[27].test_cases.emplace_back(419, test_case_t{false, 256, 419});
            test_args[11].test_cases.emplace_back(421, test_case_t{false, 616, 421});
            test_args[0].test_cases.emplace_back(421, test_case_t{false, 51, 421});
            test_args[12].test_cases.emplace_back(423, test_case_t{false, 433, 423});
            test_args[6].test_cases.emplace_back(424, test_case_t{true, 57, 424});
            test_args[5].test_cases.emplace_back(425, test_case_t{true, 372, 425});
            test_args[19].test_cases.emplace_back(427, test_case_t{true, 121, 427});
            test_args[4].test_cases.emplace_back(431, test_case_t{false, 106, 431});
            test_args[14].test_cases.emplace_back(431, test_case_t{false, 372, 431});
            test_args[29].test_cases.emplace_back(432, test_case_t{true, 386, 432});
            test_args[20].test_cases.emplace_back(433, test_case_t{false, 148, 433});
            test_args[31].test_cases.emplace_back(433, test_case_t{false, 579, 433});
            test_args[22].test_cases.emplace_back(436, test_case_t{true, 584, 436});
            test_args[17].test_cases.emplace_back(439, test_case_t{true, 67, 439});
            test_args[28].test_cases.emplace_back(440, test_case_t{true, 522, 440});
            test_args[30].test_cases.emplace_back(441, test_case_t{false, 222, 441});
            test_args[15].test_cases.emplace_back(443, test_case_t{false, 14, 443});
            test_args[15].test_cases.emplace_back(444, test_case_t{true, 349, 444});
            test_args[25].test_cases.emplace_back(447, test_case_t{false, 493, 447});
            test_args[10].test_cases.emplace_back(449, test_case_t{false, 744, 449});
            test_args[19].test_cases.emplace_back(450, test_case_t{true, 493, 450});
            test_args[27].test_cases.emplace_back(451, test_case_t{false, 333, 451});
            test_args[2].test_cases.emplace_back(452, test_case_t{true, 118, 452});
            test_args[11].test_cases.emplace_back(453, test_case_t{true, 676, 453});
            test_args[4].test_cases.emplace_back(455, test_case_t{true, 144, 455});
            test_args[12].test_cases.emplace_back(455, test_case_t{true, 413, 455});
            test_args[31].test_cases.emplace_back(455, test_case_t{false, 680, 455});
            test_args[6].test_cases.emplace_back(456, test_case_t{true, 159, 456});
            test_args[5].test_cases.emplace_back(457, test_case_t{true, 428, 457});
            test_args[5].test_cases.emplace_back(458, test_case_t{false, 295, 458});
            test_args[22].test_cases.emplace_back(459, test_case_t{false, 410, 459});
            test_args[14].test_cases.emplace_back(463, test_case_t{true, 121, 463});
            test_args[29].test_cases.emplace_back(464, test_case_t{false, 470, 464});
            test_args[28].test_cases.emplace_back(465, test_case_t{false, 744, 465});
            test_args[20].test_cases.emplace_back(466, test_case_t{false, 702, 466});
            test_args[15].test_cases.emplace_back(467, test_case_t{false, 516, 467});
            test_args[17].test_cases.emplace_back(471, test_case_t{false, 37, 471});
            test_args[27].test_cases.emplace_back(473, test_case_t{true, 14, 473});
            test_args[30].test_cases.emplace_back(473, test_case_t{false, 285, 473});
            test_args[11].test_cases.emplace_back(475, test_case_t{false, 205, 475});
            test_args[12].test_cases.emplace_back(477, test_case_t{false, 709, 477});
            test_args[4].test_cases.emplace_back(478, test_case_t{true, 649, 478});
            test_args[25].test_cases.emplace_back(479, test_case_t{false, 280, 479});
            test_args[10].test_cases.emplace_back(481, test_case_t{false, 88, 481});
            test_args[29].test_cases.emplace_back(486, test_case_t{false, 486, 486});
            test_args[2].test_cases.emplace_back(487, test_case_t{false, 513, 487});
            test_args[6].test_cases.emplace_back(489, test_case_t{false, 600, 489});
            test_args[5].test_cases.emplace_back(491, test_case_t{false, 131, 491});
            test_args[5].test_cases.emplace_back(492, test_case_t{true, 262, 492});
            test_args[17].test_cases.emplace_back(493, test_case_t{false, 73, 493});
            test_args[19].test_cases.emplace_back(493, test_case_t{true, 398, 493});
            test_args[17].test_cases.emplace_back(494, test_case_t{true, 237, 494});
            test_args[14].test_cases.emplace_back(495, test_case_t{true, 737, 495});
            test_args[27].test_cases.emplace_back(495, test_case_t{false, 161, 495});
            test_args[30].test_cases.emplace_back(495, test_case_t{false, 29, 495});
            test_args[28].test_cases.emplace_back(497, test_case_t{false, 242, 497});
            test_args[20].test_cases.emplace_back(498, test_case_t{true, 531, 498});
            test_args[20].test_cases.emplace_back(499, test_case_t{false, 721, 499});
            test_args[20].test_cases.emplace_back(500, test_case_t{false, 176, 500});
            test_args[15].test_cases.emplace_back(501, test_case_t{true, 118, 501});
            test_args[25].test_cases.emplace_back(501, test_case_t{false, 326, 501});
            test_args[31].test_cases.emplace_back(508, test_case_t{false, 14, 508});
            test_args[12].test_cases.emplace_back(509, test_case_t{false, 7, 509});
            test_args[12].test_cases.emplace_back(510, test_case_t{true, 16, 510});
            test_args[2].test_cases.emplace_back(511, test_case_t{true, 258, 511});
            test_args[11].test_cases.emplace_back(511, test_case_t{false, 634, 511});
            test_args[11].test_cases.emplace_back(512, test_case_t{true, 650, 512});
            test_args[10].test_cases.emplace_back(513, test_case_t{true, 591, 513});
            test_args[22].test_cases.emplace_back(513, test_case_t{true, 501, 513});
            test_args[17].test_cases.emplace_back(516, test_case_t{true, 138, 516});
            test_args[14].test_cases.emplace_back(517, test_case_t{true, 59, 517});
            test_args[6].test_cases.emplace_back(521, test_case_t{false, 206, 521});
            test_args[25].test_cases.emplace_back(523, test_case_t{false, 604, 523});
            test_args[5].test_cases.emplace_back(525, test_case_t{true, 671, 525});
            test_args[19].test_cases.emplace_back(526, test_case_t{false, 355, 526});
            test_args[27].test_cases.emplace_back(528, test_case_t{false, 60, 528});
            test_args[28].test_cases.emplace_back(529, test_case_t{true, 707, 529});
            test_args[30].test_cases.emplace_back(530, test_case_t{false, 698, 530});
            test_args[20].test_cases.emplace_back(533, test_case_t{true, 414, 533});
            test_args[15].test_cases.emplace_back(535, test_case_t{true, 393, 535});
            test_args[22].test_cases.emplace_back(535, test_case_t{false, 532, 535});
            test_args[29].test_cases.emplace_back(539, test_case_t{false, 178, 539});
            test_args[31].test_cases.emplace_back(540, test_case_t{false, 460, 540});
            test_args[31].test_cases.emplace_back(541, test_case_t{true, 550, 541});
            test_args[2].test_cases.emplace_back(543, test_case_t{false, 268, 543});
            test_args[2].test_cases.emplace_back(544, test_case_t{false, 564, 544});
            test_args[6].test_cases.emplace_back(544, test_case_t{false, 354, 544});
            test_args[11].test_cases.emplace_back(544, test_case_t{true, 134, 544});
            test_args[25].test_cases.emplace_back(545, test_case_t{false, 710, 545});
            test_args[2].test_cases.emplace_back(546, test_case_t{false, 598, 546});
            test_args[2].test_cases.emplace_back(548, test_case_t{false, 467, 548});
            test_args[17].test_cases.emplace_back(548, test_case_t{false, 278, 548});
            test_args[19].test_cases.emplace_back(548, test_case_t{false, 652, 548});
            test_args[2].test_cases.emplace_back(549, test_case_t{true, 709, 549});
            test_args[10].test_cases.emplace_back(549, test_case_t{true, 262, 549});
            test_args[28].test_cases.emplace_back(551, test_case_t{true, 119, 551});
            test_args[14].test_cases.emplace_back(552, test_case_t{true, 520, 552});
            test_args[30].test_cases.emplace_back(552, test_case_t{false, 264, 552});
            test_args[12].test_cases.emplace_back(553, test_case_t{false, 75, 553});
            test_args[5].test_cases.emplace_back(557, test_case_t{true, 260, 557});
            test_args[20].test_cases.emplace_back(557, test_case_t{false, 524, 557});
            test_args[5].test_cases.emplace_back(558, test_case_t{true, 344, 558});
            test_args[29].test_cases.emplace_back(561, test_case_t{true, 146, 561});
            test_args[27].test_cases.emplace_back(562, test_case_t{false, 401, 562});
            test_args[6].test_cases.emplace_back(566, test_case_t{true, 3, 566});
            test_args[15].test_cases.emplace_back(568, test_case_t{true, 20, 568});
            test_args[22].test_cases.emplace_back(568, test_case_t{true, 269, 568});
            test_args[17].test_cases.emplace_back(570, test_case_t{false, 746, 570});
            test_args[2].test_cases.emplace_back(571, test_case_t{true, 413, 571});
            test_args[31].test_cases.emplace_back(573, test_case_t{false, 440, 573});
            test_args[14].test_cases.emplace_back(574, test_case_t{true, 274, 574});
            test_args[31].test_cases.emplace_back(574, test_case_t{true, 159, 574});
            test_args[11].test_cases.emplace_back(576, test_case_t{false, 270, 576});
            test_args[19].test_cases.emplace_back(580, test_case_t{true, 537, 580});
            test_args[10].test_cases.emplace_back(582, test_case_t{true, 525, 582});
            test_args[28].test_cases.emplace_back(585, test_case_t{false, 273, 585});
            test_args[30].test_cases.emplace_back(585, test_case_t{true, 237, 585});
            test_args[12].test_cases.emplace_back(586, test_case_t{true, 316, 586});
            test_args[6].test_cases.emplace_back(588, test_case_t{true, 8, 588});
            test_args[25].test_cases.emplace_back(588, test_case_t{true, 655, 588});
            test_args[6].test_cases.emplace_back(589, test_case_t{true, 37, 589});
            test_args[5].test_cases.emplace_back(590, test_case_t{false, 400, 590});
            test_args[29].test_cases.emplace_back(593, test_case_t{false, 295, 593});
            test_args[27].test_cases.emplace_back(594, test_case_t{true, 36, 594});
            test_args[14].test_cases.emplace_back(596, test_case_t{true, 344, 596});
            test_args[15].test_cases.emplace_back(600, test_case_t{true, 478, 600});
            test_args[17].test_cases.emplace_back(602, test_case_t{true, 577, 602});
            test_args[19].test_cases.emplace_back(602, test_case_t{false, 247, 602});
            test_args[11].test_cases.emplace_back(608, test_case_t{false, 709, 608});
            test_args[12].test_cases.emplace_back(608, test_case_t{true, 520, 608});
            test_args[31].test_cases.emplace_back(608, test_case_t{true, 43, 608});
            test_args[25].test_cases.emplace_back(610, test_case_t{false, 545, 610});
            test_args[5].test_cases.emplace_back(612, test_case_t{true, 236, 612});
            test_args[6].test_cases.emplace_back(612, test_case_t{false, 158, 612});
            test_args[10].test_cases.emplace_back(614, test_case_t{false, 574, 614});
            test_args[29].test_cases.emplace_back(615, test_case_t{false, 54, 615});
            test_args[30].test_cases.emplace_back(617, test_case_t{true, 18, 617});
            test_args[15].test_cases.emplace_back(623, test_case_t{true, 12, 623});
            test_args[19].test_cases.emplace_back(624, test_case_t{false, 373, 624});
            test_args[27].test_cases.emplace_back(627, test_case_t{false, 553, 627});
            test_args[14].test_cases.emplace_back(632, test_case_t{true, 113, 632});
            test_args[22].test_cases.emplace_back(632, test_case_t{false, 541, 632});
            test_args[17].test_cases.emplace_back(634, test_case_t{false, 96, 634});
            test_args[10].test_cases.emplace_back(636, test_case_t{true, 520, 636});
            test_args[28].test_cases.emplace_back(640, test_case_t{true, 549, 640});
            test_args[31].test_cases.emplace_back(640, test_case_t{true, 296, 640});
            test_args[12].test_cases.emplace_back(642, test_case_t{true, 501, 642});
            test_args[25].test_cases.emplace_back(643, test_case_t{true, 285, 643});
            test_args[5].test_cases.emplace_back(645, test_case_t{false, 266, 645});
            test_args[5].test_cases.emplace_back(646, test_case_t{true, 459, 646});
            test_args[6].test_cases.emplace_back(647, test_case_t{false, 260, 647});
            test_args[29].test_cases.emplace_back(647, test_case_t{true, 126, 647});
            test_args[30].test_cases.emplace_back(649, test_case_t{true, 40, 649});
            test_args[15].test_cases.emplace_back(655, test_case_t{false, 266, 655});
            test_args[17].test_cases.emplace_back(659, test_case_t{false, 133, 659});
            test_args[19].test_cases.emplace_back(659, test_case_t{false, 695, 659});
            test_args[27].test_cases.emplace_back(659, test_case_t{false, 329, 659});
            test_args[27].test_cases.emplace_back(660, test_case_t{true, 18, 660});
            test_args[28].test_cases.emplace_back(662, test_case_t{false, 688, 662});
            test_args[31].test_cases.emplace_back(662, test_case_t{false, 659, 662});
            test_args[14].test_cases.emplace_back(664, test_case_t{true, 350, 664});
            test_args[14].test_cases.emplace_back(665, test_case_t{false, 200, 665});
            test_args[25].test_cases.emplace_back(665, test_case_t{false, 532, 665});
            test_args[22].test_cases.emplace_back(666, test_case_t{false, 650, 666});
            test_args[5].test_cases.emplace_back(668, test_case_t{false, 534, 668});
            test_args[10].test_cases.emplace_back(668, test_case_t{false, 689, 668});
            test_args[12].test_cases.emplace_back(674, test_case_t{false, 414, 674});
            test_args[6].test_cases.emplace_back(679, test_case_t{false, 634, 679});
            test_args[29].test_cases.emplace_back(679, test_case_t{false, 616, 679});
            test_args[6].test_cases.emplace_back(680, test_case_t{false, 591, 680});
            test_args[19].test_cases.emplace_back(681, test_case_t{false, 601, 681});
            test_args[30].test_cases.emplace_back(681, test_case_t{true, 188, 681});
            test_args[28].test_cases.emplace_back(684, test_case_t{false, 227, 684});
            test_args[14].test_cases.emplace_back(687, test_case_t{false, 355, 687});
            test_args[15].test_cases.emplace_back(687, test_case_t{true, 434, 687});
            test_args[25].test_cases.emplace_back(687, test_case_t{false, 187, 687});
            test_args[5].test_cases.emplace_back(690, test_case_t{true, 614, 690});
            test_args[10].test_cases.emplace_back(691, test_case_t{false, 33, 691});
            test_args[17].test_cases.emplace_back(691, test_case_t{true, 651, 691});
            test_args[27].test_cases.emplace_back(692, test_case_t{true, 167, 692});
            test_args[31].test_cases.emplace_back(695, test_case_t{true, 553, 695});
            test_args[12].test_cases.emplace_back(696, test_case_t{true, 177, 696});
            test_args[22].test_cases.emplace_back(698, test_case_t{false, 69, 698});
            test_args[29].test_cases.emplace_back(701, test_case_t{false, 634, 701});
            test_args[19].test_cases.emplace_back(703, test_case_t{false, 592, 703});
            test_args[19].test_cases.emplace_back(704, test_case_t{true, 89, 704});
            test_args[14].test_cases.emplace_back(709, test_case_t{false, 591, 709});
            test_args[15].test_cases.emplace_back(710, test_case_t{false, 710, 710});
            test_args[5].test_cases.emplace_back(712, test_case_t{false, 45, 712});
            test_args[6].test_cases.emplace_back(712, test_case_t{true, 472, 712});
            test_args[17].test_cases.emplace_back(713, test_case_t{false, 443, 713});
            test_args[27].test_cases.emplace_back(714, test_case_t{true, 357, 714});
            test_args[28].test_cases.emplace_back(716, test_case_t{true, 701, 716});
            test_args[12].test_cases.emplace_back(718, test_case_t{false, 27, 718});
            test_args[22].test_cases.emplace_back(720, test_case_t{true, 441, 720});
            test_args[10].test_cases.emplace_back(723, test_case_t{true, 473, 723});
            test_args[29].test_cases.emplace_back(724, test_case_t{false, 298, 724});
            test_args[19].test_cases.emplace_back(726, test_case_t{true, 363, 726});
            test_args[31].test_cases.emplace_back(727, test_case_t{true, 323, 727});
            test_args[14].test_cases.emplace_back(731, test_case_t{false, 672, 731});
            test_args[5].test_cases.emplace_back(736, test_case_t{false, 396, 736});
            test_args[27].test_cases.emplace_back(736, test_case_t{false, 207, 736});
            test_args[15].test_cases.emplace_back(738, test_case_t{false, 30, 738});
            test_args[6].test_cases.emplace_back(744, test_case_t{false, 397, 744});
            test_args[17].test_cases.emplace_back(746, test_case_t{false, 486, 746});
            test_args[31].test_cases.emplace_back(749, test_case_t{true, 690, 749});
            test_args[12].test_cases.emplace_back(751, test_case_t{false, 361, 751});
            test_args[14].test_cases.emplace_back(753, test_case_t{false, 421, 753});
            test_args[10].test_cases.emplace_back(755, test_case_t{true, 532, 755});
            test_args[29].test_cases.emplace_back(756, test_case_t{true, 621, 756});
            test_args[27].test_cases.emplace_back(758, test_case_t{true, 637, 758});
            test_args[22].test_cases.emplace_back(763, test_case_t{true, 534, 763});
            test_args[15].test_cases.emplace_back(770, test_case_t{true, 610, 770});
            test_args[31].test_cases.emplace_back(771, test_case_t{false, 447, 771});
            test_args[5].test_cases.emplace_back(772, test_case_t{true, 84, 772});
            test_args[17].test_cases.emplace_back(773, test_case_t{true, 127, 773});
            test_args[10].test_cases.emplace_back(777, test_case_t{true, 150, 777});
            test_args[6].test_cases.emplace_back(778, test_case_t{false, 180, 778});
            test_args[27].test_cases.emplace_back(781, test_case_t{true, 428, 781});
            test_args[27].test_cases.emplace_back(782, test_case_t{true, 245, 782});
            test_args[19].test_cases.emplace_back(784, test_case_t{true, 187, 784});
            test_args[12].test_cases.emplace_back(786, test_case_t{true, 706, 786});
            test_args[14].test_cases.emplace_back(786, test_case_t{true, 184, 786});
            test_args[29].test_cases.emplace_back(788, test_case_t{false, 514, 788});
            test_args[10].test_cases.emplace_back(799, test_case_t{true, 300, 799});
            test_args[31].test_cases.emplace_back(803, test_case_t{false, 334, 803});
            test_args[5].test_cases.emplace_back(804, test_case_t{true, 94, 804});
            test_args[27].test_cases.emplace_back(804, test_case_t{true, 246, 804});
            test_args[31].test_cases.emplace_back(804, test_case_t{false, 239, 804});
            test_args[5].test_cases.emplace_back(805, test_case_t{true, 286, 805});
            test_args[17].test_cases.emplace_back(805, test_case_t{false, 552, 805});
            test_args[27].test_cases.emplace_back(805, test_case_t{false, 604, 805});
            test_args[12].test_cases.emplace_back(808, test_case_t{true, 109, 808});
            test_args[15].test_cases.emplace_back(809, test_case_t{false, 67, 809});
            test_args[6].test_cases.emplace_back(810, test_case_t{false, 737, 810});
            test_args[22].test_cases.emplace_back(817, test_case_t{true, 120, 817});
            test_args[29].test_cases.emplace_back(820, test_case_t{true, 488, 820});
            test_args[10].test_cases.emplace_back(821, test_case_t{true, 460, 821});
            test_args[31].test_cases.emplace_back(827, test_case_t{true, 267, 827});
            test_args[19].test_cases.emplace_back(828, test_case_t{false, 30, 828});
            test_args[12].test_cases.emplace_back(830, test_case_t{false, 183, 830});
            test_args[15].test_cases.emplace_back(831, test_case_t{true, 307, 831});
            test_args[27].test_cases.emplace_back(832, test_case_t{true, 609, 832});
            test_args[6].test_cases.emplace_back(833, test_case_t{true, 54, 833});
            test_args[5].test_cases.emplace_back(837, test_case_t{true, 617, 837});
            test_args[17].test_cases.emplace_back(838, test_case_t{true, 155, 838});
            test_args[14].test_cases.emplace_back(839, test_case_t{false, 128, 839});
            test_args[29].test_cases.emplace_back(843, test_case_t{false, 491, 843});
            test_args[29].test_cases.emplace_back(844, test_case_t{true, 265, 844});
            test_args[22].test_cases.emplace_back(849, test_case_t{true, 709, 849});
            test_args[10].test_cases.emplace_back(854, test_case_t{true, 91, 854});
            test_args[6].test_cases.emplace_back(857, test_case_t{false, 475, 857});
            test_args[6].test_cases.emplace_back(858, test_case_t{false, 562, 858});
            test_args[14].test_cases.emplace_back(861, test_case_t{false, 341, 861});
            test_args[14].test_cases.emplace_back(862, test_case_t{false, 543, 862});
            test_args[15].test_cases.emplace_back(863, test_case_t{true, 137, 863});
            test_args[27].test_cases.emplace_back(864, test_case_t{true, 662, 864});
            test_args[12].test_cases.emplace_back(866, test_case_t{true, 356, 866});
            test_args[29].test_cases.emplace_back(866, test_case_t{true, 762, 866});
            test_args[5].test_cases.emplace_back(869, test_case_t{true, 316, 869});
            test_args[6].test_cases.emplace_back(881, test_case_t{false, 573, 881});
            test_args[22].test_cases.emplace_back(881, test_case_t{true, 178, 881});
            test_args[6].test_cases.emplace_back(882, test_case_t{true, 651, 882});
            test_args[15].test_cases.emplace_back(885, test_case_t{true, 420, 885});
            test_args[10].test_cases.emplace_back(886, test_case_t{true, 24, 886});
            test_args[27].test_cases.emplace_back(886, test_case_t{true, 626, 886});
            test_args[27].test_cases.emplace_back(887, test_case_t{true, 569, 887});
            test_args[29].test_cases.emplace_back(888, test_case_t{false, 28, 888});
            test_args[14].test_cases.emplace_back(894, test_case_t{false, 570, 894});
            test_args[12].test_cases.emplace_back(898, test_case_t{false, 379, 898});
            test_args[5].test_cases.emplace_back(901, test_case_t{false, 485, 901});
            test_args[22].test_cases.emplace_back(903, test_case_t{true, 662, 903});
            test_args[15].test_cases.emplace_back(907, test_case_t{true, 253, 907});
            test_args[10].test_cases.emplace_back(908, test_case_t{false, 168, 908});
            test_args[27].test_cases.emplace_back(909, test_case_t{false, 478, 909});
            test_args[6].test_cases.emplace_back(914, test_case_t{false, 126, 914});
            test_args[12].test_cases.emplace_back(920, test_case_t{true, 534, 920});
            test_args[5].test_cases.emplace_back(933, test_case_t{true, 630, 933});
            test_args[22].test_cases.emplace_back(936, test_case_t{false, 399, 936});
            test_args[15].test_cases.emplace_back(940, test_case_t{false, 282, 940});
            test_args[27].test_cases.emplace_back(941, test_case_t{false, 623, 941});
            test_args[10].test_cases.emplace_back(942, test_case_t{false, 188, 942});
            test_args[12].test_cases.emplace_back(942, test_case_t{false, 253, 942});
            test_args[27].test_cases.emplace_back(942, test_case_t{true, 177, 942});
            test_args[29].test_cases.emplace_back(943, test_case_t{false, 85, 943});
            test_args[6].test_cases.emplace_back(947, test_case_t{false, 533, 947});
            test_args[14].test_cases.emplace_back(947, test_case_t{false, 495, 947});
            test_args[5].test_cases.emplace_back(965, test_case_t{true, 423, 965});
            test_args[14].test_cases.emplace_back(969, test_case_t{true, 39, 969});
            test_args[15].test_cases.emplace_back(972, test_case_t{true, 91, 972});
            test_args[10].test_cases.emplace_back(974, test_case_t{false, 573, 974});
            test_args[12].test_cases.emplace_back(975, test_case_t{false, 298, 975});
            test_args[29].test_cases.emplace_back(977, test_case_t{false, 587, 977});
            test_args[6].test_cases.emplace_back(979, test_case_t{true, 735, 979});
            test_args[27].test_cases.emplace_back(987, test_case_t{true, 445, 987});
            test_args[14].test_cases.emplace_back(991, test_case_t{true, 731, 991});
            test_args[15].test_cases.emplace_back(994, test_case_t{true, 316, 994});
            test_args[10].test_cases.emplace_back(996, test_case_t{false, 467, 996});
            test_args[5].test_cases.emplace_back(997, test_case_t{true, 205, 997});
            test_args[10].test_cases.emplace_back(997, test_case_t{true, 632, 997});
            test_args[29].test_cases.emplace_back(999, test_case_t{true, 356, 999});
            test_args[6].test_cases.emplace_back(1001, test_case_t{false, 295, 1001});
            test_args[12].test_cases.emplace_back(1007, test_case_t{false, 703, 1007});
            test_args[27].test_cases.emplace_back(1009, test_case_t{false, 492, 1009});
            test_args[5].test_cases.emplace_back(1019, test_case_t{false, 270, 1019});
            test_args[5].test_cases.emplace_back(1020, test_case_t{true, 97, 1020});
            test_args[6].test_cases.emplace_back(1023, test_case_t{true, 355, 1023});
            test_args[14].test_cases.emplace_back(1023, test_case_t{true, 437, 1023});
            test_args[15].test_cases.emplace_back(1026, test_case_t{false, 180, 1026});
            test_args[10].test_cases.emplace_back(1030, test_case_t{true, 202, 1030});
            test_args[27].test_cases.emplace_back(1031, test_case_t{true, 537, 1031});
            test_args[29].test_cases.emplace_back(1031, test_case_t{false, 144, 1031});
            test_args[27].test_cases.emplace_back(1032, test_case_t{true, 221, 1032});
            test_args[29].test_cases.emplace_back(1032, test_case_t{true, 357, 1032});
            test_args[29].test_cases.emplace_back(1033, test_case_t{true, 275, 1033});
            test_args[12].test_cases.emplace_back(1039, test_case_t{false, 590, 1039});
            test_args[5].test_cases.emplace_back(1054, test_case_t{true, 102, 1054});
            test_args[27].test_cases.emplace_back(1054, test_case_t{false, 90, 1054});
            test_args[5].test_cases.emplace_back(1055, test_case_t{true, 512, 1055});
            test_args[6].test_cases.emplace_back(1055, test_case_t{false, 706, 1055});
            test_args[29].test_cases.emplace_back(1055, test_case_t{true, 307, 1055});
            test_args[14].test_cases.emplace_back(1056, test_case_t{false, 689, 1056});
            test_args[15].test_cases.emplace_back(1058, test_case_t{false, 687, 1058});
            test_args[12].test_cases.emplace_back(1061, test_case_t{false, 710, 1061});
            test_args[10].test_cases.emplace_back(1062, test_case_t{true, 492, 1062});
            test_args[5].test_cases.emplace_back(1077, test_case_t{false, 442, 1077});
            test_args[14].test_cases.emplace_back(1079, test_case_t{true, 572, 1079});
            test_args[15].test_cases.emplace_back(1080, test_case_t{false, 354, 1080});
            test_args[10].test_cases.emplace_back(1084, test_case_t{false, 79, 1084});
            test_args[27].test_cases.emplace_back(1086, test_case_t{true, 311, 1086});
            test_args[6].test_cases.emplace_back(1088, test_case_t{false, 631, 1088});
            test_args[29].test_cases.emplace_back(1088, test_case_t{true, 728, 1088});
            test_args[6].test_cases.emplace_back(1089, test_case_t{true, 731, 1089});
            test_args[12].test_cases.emplace_back(1093, test_case_t{false, 645, 1093});
            test_args[14].test_cases.emplace_back(1102, test_case_t{false, 113, 1102});
            test_args[14].test_cases.emplace_back(1103, test_case_t{true, 449, 1103});
            test_args[10].test_cases.emplace_back(1106, test_case_t{true, 410, 1106});
            test_args[5].test_cases.emplace_back(1110, test_case_t{true, 487, 1110});
            test_args[15].test_cases.emplace_back(1112, test_case_t{false, 503, 1112});
            test_args[27].test_cases.emplace_back(1118, test_case_t{true, 698, 1118});
            test_args[29].test_cases.emplace_back(1120, test_case_t{false, 492, 1120});
            test_args[6].test_cases.emplace_back(1122, test_case_t{true, 276, 1122});
            test_args[12].test_cases.emplace_back(1125, test_case_t{false, 495, 1125});
            test_args[10].test_cases.emplace_back(1128, test_case_t{false, 540, 1128});
            test_args[14].test_cases.emplace_back(1135, test_case_t{false, 427, 1135});
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
            case 28:
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
