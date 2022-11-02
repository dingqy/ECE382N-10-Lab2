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
        case 34:
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 2, 0});
            test_args[2].test_cases.emplace_back(0, test_case_t{false, 5, 0});
            test_args[3].test_cases.emplace_back(0, test_case_t{true, 7, 0});
            test_args[4].test_cases.emplace_back(0, test_case_t{true, 10, 0});
            test_args[5].test_cases.emplace_back(0, test_case_t{true, 12, 0});
            test_args[6].test_cases.emplace_back(0, test_case_t{true, 15, 0});
            test_args[7].test_cases.emplace_back(0, test_case_t{false, 17, 0});
            test_args[8].test_cases.emplace_back(0, test_case_t{false, 20, 0});
            test_args[9].test_cases.emplace_back(0, test_case_t{true, 23, 0});
            test_args[10].test_cases.emplace_back(0, test_case_t{true, 25, 0});
            test_args[11].test_cases.emplace_back(0, test_case_t{false, 28, 0});
            test_args[12].test_cases.emplace_back(0, test_case_t{true, 30, 0});
            test_args[13].test_cases.emplace_back(0, test_case_t{false, 33, 0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 35, 0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 38, 0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 41, 0});
            test_args[17].test_cases.emplace_back(0, test_case_t{false, 43, 0});
            test_args[18].test_cases.emplace_back(0, test_case_t{false, 46, 0});
            test_args[19].test_cases.emplace_back(0, test_case_t{false, 48, 0});
            test_args[20].test_cases.emplace_back(0, test_case_t{false, 51, 0});
            test_args[21].test_cases.emplace_back(0, test_case_t{true, 53, 0});
            test_args[22].test_cases.emplace_back(0, test_case_t{false, 56, 0});
            test_args[23].test_cases.emplace_back(0, test_case_t{true, 58, 0});
            test_args[24].test_cases.emplace_back(0, test_case_t{true, 61, 0});
            test_args[25].test_cases.emplace_back(0, test_case_t{false, 64, 0});
            test_args[26].test_cases.emplace_back(0, test_case_t{false, 66, 0});
            test_args[27].test_cases.emplace_back(0, test_case_t{false, 69, 0});
            test_args[28].test_cases.emplace_back(0, test_case_t{true, 71, 0});
            test_args[29].test_cases.emplace_back(0, test_case_t{true, 74, 0});
            test_args[30].test_cases.emplace_back(0, test_case_t{true, 76, 0});
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 79, 0});
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 4310, 2});
            test_args[1].test_cases.emplace_back(22, test_case_t{false, 10334, 22});
            test_args[0].test_cases.emplace_back(24, test_case_t{true, 24760, 24});
            test_args[7].test_cases.emplace_back(28, test_case_t{true, 6804, 28});
            test_args[0].test_cases.emplace_back(32, test_case_t{true, 15029, 32});
            test_args[2].test_cases.emplace_back(33, test_case_t{false, 20669, 33});
            test_args[13].test_cases.emplace_back(38, test_case_t{true, 3274, 38});
            test_args[8].test_cases.emplace_back(39, test_case_t{false, 17139, 39});
            test_args[3].test_cases.emplace_back(46, test_case_t{true, 31004, 46});
            test_args[11].test_cases.emplace_back(46, test_case_t{true, 15374, 46});
            test_args[14].test_cases.emplace_back(49, test_case_t{true, 13608, 49});
            test_args[15].test_cases.emplace_back(51, test_case_t{true, 23943, 51});
            test_args[19].test_cases.emplace_back(52, test_case_t{false, 32513, 52});
            test_args[16].test_cases.emplace_back(53, test_case_t{true, 1508, 53});
            test_args[2].test_cases.emplace_back(55, test_case_t{false, 3673, 55});
            test_args[17].test_cases.emplace_back(55, test_case_t{false, 11843, 55});
            test_args[9].test_cases.emplace_back(56, test_case_t{true, 27473, 56});
            test_args[4].test_cases.emplace_back(57, test_case_t{false, 8569, 57});
            test_args[5].test_cases.emplace_back(59, test_case_t{true, 18904, 59});
            test_args[6].test_cases.emplace_back(61, test_case_t{false, 29239, 61});
            test_args[8].test_cases.emplace_back(61, test_case_t{true, 14694, 61});
            test_args[18].test_cases.emplace_back(61, test_case_t{false, 22178, 61});
            test_args[20].test_cases.emplace_back(63, test_case_t{false, 10078, 63});
            test_args[25].test_cases.emplace_back(65, test_case_t{true, 28982, 65});
            test_args[0].test_cases.emplace_back(65, test_case_t{false, 17458, 65});
            test_args[10].test_cases.emplace_back(67, test_case_t{false, 5039, 67});
            test_args[11].test_cases.emplace_back(68, test_case_t{false, 3820, 68});
            test_args[12].test_cases.emplace_back(69, test_case_t{true, 25708, 69});
            test_args[14].test_cases.emplace_back(71, test_case_t{true, 25715, 71});
            test_args[22].test_cases.emplace_back(71, test_case_t{true, 30748, 71});
            test_args[15].test_cases.emplace_back(73, test_case_t{false, 11167, 73});
            test_args[16].test_cases.emplace_back(75, test_case_t{true, 29389, 75});
            test_args[2].test_cases.emplace_back(77, test_case_t{false, 5669, 77});
            test_args[17].test_cases.emplace_back(78, test_case_t{true, 14841, 78});
            test_args[4].test_cases.emplace_back(79, test_case_t{false, 7347, 79});
            test_args[26].test_cases.emplace_back(79, test_case_t{true, 6548, 79});
            test_args[5].test_cases.emplace_back(81, test_case_t{true, 25568, 81});
            test_args[27].test_cases.emplace_back(81, test_case_t{true, 16882, 81});
            test_args[6].test_cases.emplace_back(83, test_case_t{false, 11021, 83});
            test_args[8].test_cases.emplace_back(83, test_case_t{true, 22676, 83});
            test_args[18].test_cases.emplace_back(83, test_case_t{false, 293, 83});
            test_args[21].test_cases.emplace_back(83, test_case_t{true, 20413, 83});
            test_args[20].test_cases.emplace_back(85, test_case_t{false, 3967, 85});
            test_args[25].test_cases.emplace_back(87, test_case_t{true, 29536, 87});
            test_args[10].test_cases.emplace_back(89, test_case_t{false, 18368, 89});
            test_args[11].test_cases.emplace_back(90, test_case_t{false, 14795, 90});
            test_args[12].test_cases.emplace_back(91, test_case_t{true, 22042, 91});
            test_args[14].test_cases.emplace_back(93, test_case_t{false, 6914, 93});
            test_args[22].test_cases.emplace_back(94, test_case_t{true, 7640, 94});
            test_args[23].test_cases.emplace_back(94, test_case_t{false, 8313, 94});
            test_args[28].test_cases.emplace_back(94, test_case_t{false, 27217, 94});
            test_args[15].test_cases.emplace_back(95, test_case_t{false, 26134, 95});
            test_args[24].test_cases.emplace_back(96, test_case_t{false, 18648, 96});
            test_args[0].test_cases.emplace_back(96, test_case_t{false, 7175, 96});
            test_args[16].test_cases.emplace_back(97, test_case_t{true, 12584, 97});
            test_args[2].test_cases.emplace_back(99, test_case_t{true, 21475, 99});
            test_args[17].test_cases.emplace_back(100, test_case_t{false, 31803, 100});
            test_args[26].test_cases.emplace_back(101, test_case_t{true, 14988, 101});
            test_args[4].test_cases.emplace_back(102, test_case_t{false, 11338, 102});
            test_args[5].test_cases.emplace_back(103, test_case_t{false, 30557, 103});
            test_args[26].test_cases.emplace_back(103, test_case_t{false, 8160, 103});
            test_args[27].test_cases.emplace_back(103, test_case_t{false, 440, 103});
            test_args[6].test_cases.emplace_back(105, test_case_t{true, 17007, 105});
            test_args[8].test_cases.emplace_back(105, test_case_t{false, 20362, 105});
            test_args[18].test_cases.emplace_back(105, test_case_t{false, 18253, 105});
            test_args[20].test_cases.emplace_back(107, test_case_t{false, 23922, 107});
            test_args[25].test_cases.emplace_back(109, test_case_t{false, 21710, 109});
            test_args[29].test_cases.emplace_back(110, test_case_t{true, 4782, 110});
            test_args[10].test_cases.emplace_back(111, test_case_t{true, 28346, 111});
            test_args[11].test_cases.emplace_back(112, test_case_t{false, 19805, 112});
            test_args[30].test_cases.emplace_back(112, test_case_t{false, 15117, 112});
            test_args[12].test_cases.emplace_back(113, test_case_t{false, 1245, 113});
            test_args[14].test_cases.emplace_back(115, test_case_t{true, 19249, 115});
            test_args[22].test_cases.emplace_back(116, test_case_t{true, 29591, 116});
            test_args[23].test_cases.emplace_back(116, test_case_t{true, 25862, 116});
            test_args[28].test_cases.emplace_back(116, test_case_t{false, 18661, 116});
            test_args[15].test_cases.emplace_back(118, test_case_t{true, 29986, 118});
            test_args[24].test_cases.emplace_back(118, test_case_t{false, 11314, 118});
            test_args[31].test_cases.emplace_back(118, test_case_t{false, 25452, 118});
            test_args[16].test_cases.emplace_back(119, test_case_t{false, 7955, 119});
            test_args[0].test_cases.emplace_back(120, test_case_t{true, 1541, 120});
            test_args[2].test_cases.emplace_back(121, test_case_t{false, 12425, 121});
            test_args[17].test_cases.emplace_back(122, test_case_t{false, 18692, 122});
            test_args[4].test_cases.emplace_back(124, test_case_t{true, 10181, 124});
            test_args[5].test_cases.emplace_back(125, test_case_t{true, 20918, 125});
            test_args[26].test_cases.emplace_back(125, test_case_t{true, 17023, 125});
            test_args[27].test_cases.emplace_back(126, test_case_t{false, 27380, 126});
            test_args[6].test_cases.emplace_back(127, test_case_t{true, 31656, 127});
            test_args[8].test_cases.emplace_back(127, test_case_t{false, 16933, 127});
            test_args[18].test_cases.emplace_back(127, test_case_t{true, 29430, 127});
            test_args[18].test_cases.emplace_back(129, test_case_t{true, 13522, 129});
            test_args[20].test_cases.emplace_back(129, test_case_t{true, 18136, 129});
            test_args[25].test_cases.emplace_back(131, test_case_t{true, 6285, 131});
            test_args[29].test_cases.emplace_back(132, test_case_t{true, 4113, 132});
            test_args[10].test_cases.emplace_back(133, test_case_t{true, 9068, 133});
            test_args[11].test_cases.emplace_back(134, test_case_t{true, 2802, 134});
            test_args[30].test_cases.emplace_back(134, test_case_t{true, 22335, 134});
            test_args[12].test_cases.emplace_back(135, test_case_t{true, 30543, 135});
            test_args[14].test_cases.emplace_back(137, test_case_t{true, 21440, 137});
            test_args[22].test_cases.emplace_back(138, test_case_t{false, 6842, 138});
            test_args[23].test_cases.emplace_back(138, test_case_t{true, 16041, 138});
            test_args[28].test_cases.emplace_back(138, test_case_t{true, 13829, 138});
            test_args[15].test_cases.emplace_back(140, test_case_t{false, 27653, 140});
            test_args[24].test_cases.emplace_back(140, test_case_t{true, 2491, 140});
            test_args[31].test_cases.emplace_back(140, test_case_t{false, 7787, 140});
            test_args[16].test_cases.emplace_back(141, test_case_t{true, 1096, 141});
            test_args[0].test_cases.emplace_back(142, test_case_t{true, 22246, 142});
            test_args[2].test_cases.emplace_back(143, test_case_t{false, 30832, 143});
            test_args[17].test_cases.emplace_back(144, test_case_t{false, 7309, 144});
            test_args[4].test_cases.emplace_back(146, test_case_t{true, 24851, 146});
            test_args[5].test_cases.emplace_back(147, test_case_t{false, 31064, 147});
            test_args[26].test_cases.emplace_back(147, test_case_t{true, 30455, 147});
            test_args[27].test_cases.emplace_back(148, test_case_t{true, 27760, 148});
            test_args[6].test_cases.emplace_back(149, test_case_t{true, 4507, 149});
            test_args[8].test_cases.emplace_back(149, test_case_t{false, 25021, 149});
            test_args[18].test_cases.emplace_back(151, test_case_t{false, 15337, 151});
            test_args[20].test_cases.emplace_back(151, test_case_t{false, 25948, 151});
            test_args[25].test_cases.emplace_back(153, test_case_t{true, 24242, 153});
            test_args[29].test_cases.emplace_back(154, test_case_t{false, 279, 154});
            test_args[10].test_cases.emplace_back(155, test_case_t{true, 29358, 155});
            test_args[11].test_cases.emplace_back(156, test_case_t{false, 5731, 156});
            test_args[30].test_cases.emplace_back(156, test_case_t{true, 19499, 156});
            test_args[12].test_cases.emplace_back(157, test_case_t{false, 9014, 157});
            test_args[14].test_cases.emplace_back(159, test_case_t{true, 19210, 159});
            test_args[22].test_cases.emplace_back(160, test_case_t{false, 5604, 160});
            test_args[23].test_cases.emplace_back(160, test_case_t{true, 17579, 160});
            test_args[28].test_cases.emplace_back(160, test_case_t{true, 5728, 160});
            test_args[15].test_cases.emplace_back(162, test_case_t{true, 1857, 162});
            test_args[24].test_cases.emplace_back(162, test_case_t{true, 28317, 162});
            test_args[31].test_cases.emplace_back(162, test_case_t{false, 5949, 162});
            test_args[16].test_cases.emplace_back(163, test_case_t{false, 17274, 163});
            test_args[0].test_cases.emplace_back(164, test_case_t{false, 22260, 164});
            test_args[2].test_cases.emplace_back(165, test_case_t{true, 18917, 165});
            test_args[17].test_cases.emplace_back(166, test_case_t{false, 32690, 166});
            test_args[4].test_cases.emplace_back(168, test_case_t{true, 28895, 168});
            test_args[5].test_cases.emplace_back(169, test_case_t{false, 11542, 169});
            test_args[26].test_cases.emplace_back(169, test_case_t{false, 7589, 169});
            test_args[27].test_cases.emplace_back(170, test_case_t{false, 3898, 170});
            test_args[6].test_cases.emplace_back(171, test_case_t{false, 26958, 171});
            test_args[8].test_cases.emplace_back(171, test_case_t{false, 10131, 171});
            test_args[18].test_cases.emplace_back(173, test_case_t{true, 6411, 173});
            test_args[20].test_cases.emplace_back(173, test_case_t{false, 13400, 173});
            test_args[20].test_cases.emplace_back(175, test_case_t{true, 25328, 175});
            test_args[25].test_cases.emplace_back(175, test_case_t{true, 24942, 175});
            test_args[29].test_cases.emplace_back(176, test_case_t{true, 16466, 176});
            test_args[10].test_cases.emplace_back(177, test_case_t{true, 23084, 177});
            test_args[11].test_cases.emplace_back(178, test_case_t{true, 22123, 178});
            test_args[30].test_cases.emplace_back(178, test_case_t{false, 27204, 178});
            test_args[12].test_cases.emplace_back(179, test_case_t{false, 21147, 179});
            test_args[14].test_cases.emplace_back(181, test_case_t{true, 1345, 181});
            test_args[22].test_cases.emplace_back(182, test_case_t{true, 11463, 182});
            test_args[23].test_cases.emplace_back(182, test_case_t{false, 11817, 182});
            test_args[15].test_cases.emplace_back(184, test_case_t{true, 27189, 184});
            test_args[24].test_cases.emplace_back(184, test_case_t{true, 18029, 184});
            test_args[31].test_cases.emplace_back(184, test_case_t{false, 5172, 184});
            test_args[16].test_cases.emplace_back(185, test_case_t{true, 20263, 185});
            test_args[0].test_cases.emplace_back(186, test_case_t{false, 30629, 186});
            test_args[2].test_cases.emplace_back(187, test_case_t{true, 19200, 187});
            test_args[17].test_cases.emplace_back(188, test_case_t{true, 13337, 188});
            test_args[4].test_cases.emplace_back(190, test_case_t{true, 5065, 190});
            test_args[5].test_cases.emplace_back(191, test_case_t{true, 30909, 191});
            test_args[26].test_cases.emplace_back(191, test_case_t{true, 16542, 191});
            test_args[27].test_cases.emplace_back(192, test_case_t{false, 23005, 192});
            test_args[28].test_cases.emplace_back(192, test_case_t{false, 10111, 192});
            test_args[6].test_cases.emplace_back(193, test_case_t{true, 23983, 193});
            test_args[8].test_cases.emplace_back(193, test_case_t{true, 11263, 193});
            test_args[18].test_cases.emplace_back(195, test_case_t{false, 8957, 195});
            test_args[25].test_cases.emplace_back(197, test_case_t{true, 23468, 197});
            test_args[20].test_cases.emplace_back(198, test_case_t{false, 28158, 198});
            test_args[29].test_cases.emplace_back(198, test_case_t{false, 16324, 198});
            test_args[10].test_cases.emplace_back(199, test_case_t{true, 29049, 199});
            test_args[11].test_cases.emplace_back(200, test_case_t{true, 23679, 200});
            test_args[30].test_cases.emplace_back(200, test_case_t{true, 22537, 200});
            test_args[12].test_cases.emplace_back(201, test_case_t{false, 15197, 201});
            test_args[14].test_cases.emplace_back(203, test_case_t{false, 3325, 203});
            test_args[22].test_cases.emplace_back(204, test_case_t{false, 11477, 204});
            test_args[23].test_cases.emplace_back(204, test_case_t{false, 26879, 204});
            test_args[15].test_cases.emplace_back(206, test_case_t{false, 29311, 206});
            test_args[24].test_cases.emplace_back(206, test_case_t{false, 9526, 206});
            test_args[31].test_cases.emplace_back(206, test_case_t{false, 28750, 206});
            test_args[16].test_cases.emplace_back(207, test_case_t{true, 22526, 207});
            test_args[0].test_cases.emplace_back(209, test_case_t{true, 12567, 209});
            test_args[17].test_cases.emplace_back(210, test_case_t{true, 15742, 210});
            test_args[4].test_cases.emplace_back(212, test_case_t{false, 5631, 212});
            test_args[26].test_cases.emplace_back(213, test_case_t{false, 20220, 213});
            test_args[5].test_cases.emplace_back(214, test_case_t{true, 31616, 214});
            test_args[27].test_cases.emplace_back(214, test_case_t{false, 9616, 214});
            test_args[28].test_cases.emplace_back(214, test_case_t{true, 5652, 214});
            test_args[6].test_cases.emplace_back(215, test_case_t{false, 24832, 215});
            test_args[8].test_cases.emplace_back(215, test_case_t{true, 25410, 215});
            test_args[18].test_cases.emplace_back(217, test_case_t{false, 8019, 217});
            test_args[2].test_cases.emplace_back(219, test_case_t{true, 22737, 219});
            test_args[25].test_cases.emplace_back(219, test_case_t{false, 27005, 219});
            test_args[29].test_cases.emplace_back(220, test_case_t{false, 21068, 220});
            test_args[10].test_cases.emplace_back(221, test_case_t{true, 30463, 221});
            test_args[20].test_cases.emplace_back(221, test_case_t{true, 30756, 221});
            test_args[11].test_cases.emplace_back(222, test_case_t{false, 26747, 222});
            test_args[30].test_cases.emplace_back(222, test_case_t{false, 3715, 222});
            test_args[12].test_cases.emplace_back(223, test_case_t{true, 16894, 223});
            test_args[14].test_cases.emplace_back(225, test_case_t{false, 28083, 225});
            test_args[22].test_cases.emplace_back(226, test_case_t{false, 14589, 226});
            test_args[23].test_cases.emplace_back(226, test_case_t{false, 4551, 226});
            test_args[15].test_cases.emplace_back(228, test_case_t{true, 6682, 228});
            test_args[24].test_cases.emplace_back(228, test_case_t{true, 30394, 228});
            test_args[31].test_cases.emplace_back(228, test_case_t{true, 19131, 228});
            test_args[16].test_cases.emplace_back(229, test_case_t{false, 18051, 229});
            test_args[0].test_cases.emplace_back(231, test_case_t{false, 17021, 231});
            test_args[17].test_cases.emplace_back(232, test_case_t{true, 29420, 232});
            test_args[4].test_cases.emplace_back(234, test_case_t{false, 12705, 234});
            test_args[5].test_cases.emplace_back(236, test_case_t{false, 24073, 236});
            test_args[26].test_cases.emplace_back(236, test_case_t{true, 660, 236});
            test_args[27].test_cases.emplace_back(236, test_case_t{true, 13436, 236});
            test_args[6].test_cases.emplace_back(237, test_case_t{false, 2673, 237});
            test_args[8].test_cases.emplace_back(237, test_case_t{false, 22288, 237});
            test_args[28].test_cases.emplace_back(237, test_case_t{false, 2691, 237});
            test_args[18].test_cases.emplace_back(239, test_case_t{false, 995, 239});
            test_args[2].test_cases.emplace_back(241, test_case_t{true, 21956, 241});
            test_args[25].test_cases.emplace_back(241, test_case_t{false, 22061, 241});
            test_args[20].test_cases.emplace_back(243, test_case_t{true, 22952, 243});
            test_args[29].test_cases.emplace_back(243, test_case_t{true, 28534, 243});
            test_args[11].test_cases.emplace_back(244, test_case_t{true, 6069, 244});
            test_args[30].test_cases.emplace_back(244, test_case_t{false, 21608, 244});
            test_args[14].test_cases.emplace_back(247, test_case_t{false, 22620, 247});
            test_args[22].test_cases.emplace_back(248, test_case_t{true, 20724, 248});
            test_args[23].test_cases.emplace_back(248, test_case_t{false, 7804, 248});
            test_args[15].test_cases.emplace_back(250, test_case_t{false, 17214, 250});
            test_args[24].test_cases.emplace_back(250, test_case_t{false, 1020, 250});
            test_args[31].test_cases.emplace_back(250, test_case_t{false, 14682, 250});
            test_args[16].test_cases.emplace_back(251, test_case_t{false, 11807, 251});
            test_args[10].test_cases.emplace_back(253, test_case_t{true, 15378, 253});
            test_args[17].test_cases.emplace_back(254, test_case_t{false, 6401, 254});
            test_args[12].test_cases.emplace_back(255, test_case_t{false, 5346, 255});
            test_args[4].test_cases.emplace_back(256, test_case_t{false, 11144, 256});
            test_args[5].test_cases.emplace_back(258, test_case_t{false, 5738, 258});
            test_args[26].test_cases.emplace_back(258, test_case_t{false, 23284, 258});
            test_args[27].test_cases.emplace_back(258, test_case_t{true, 12029, 258});
            test_args[6].test_cases.emplace_back(259, test_case_t{false, 331, 259});
            test_args[8].test_cases.emplace_back(259, test_case_t{false, 18131, 259});
            test_args[26].test_cases.emplace_back(260, test_case_t{false, 1581, 260});
            test_args[28].test_cases.emplace_back(260, test_case_t{false, 6651, 260});
            test_args[18].test_cases.emplace_back(261, test_case_t{false, 16219, 261});
            test_args[25].test_cases.emplace_back(263, test_case_t{true, 28690, 263});
            test_args[0].test_cases.emplace_back(263, test_case_t{true, 27230, 263});
            test_args[2].test_cases.emplace_back(264, test_case_t{false, 12725, 264});
            test_args[20].test_cases.emplace_back(265, test_case_t{false, 28944, 265});
            test_args[29].test_cases.emplace_back(265, test_case_t{true, 32637, 265});
            test_args[11].test_cases.emplace_back(266, test_case_t{true, 4450, 266});
            test_args[30].test_cases.emplace_back(266, test_case_t{true, 25852, 266});
            test_args[14].test_cases.emplace_back(269, test_case_t{true, 23538, 269});
            test_args[22].test_cases.emplace_back(270, test_case_t{false, 12139, 270});
            test_args[23].test_cases.emplace_back(270, test_case_t{true, 32093, 270});
            test_args[15].test_cases.emplace_back(272, test_case_t{false, 29900, 272});
            test_args[31].test_cases.emplace_back(272, test_case_t{false, 19068, 272});
            test_args[16].test_cases.emplace_back(273, test_case_t{true, 3493, 273});
            test_args[10].test_cases.emplace_back(275, test_case_t{true, 11476, 275});
            test_args[12].test_cases.emplace_back(277, test_case_t{true, 663, 277});
            test_args[4].test_cases.emplace_back(278, test_case_t{true, 25450, 278});
            test_args[27].test_cases.emplace_back(280, test_case_t{false, 17877, 280});
            test_args[6].test_cases.emplace_back(281, test_case_t{true, 5406, 281});
            test_args[26].test_cases.emplace_back(282, test_case_t{true, 1670, 282});
            test_args[18].test_cases.emplace_back(283, test_case_t{true, 18801, 283});
            test_args[28].test_cases.emplace_back(283, test_case_t{false, 23397, 283});
            test_args[25].test_cases.emplace_back(285, test_case_t{false, 27988, 285});
            test_args[2].test_cases.emplace_back(286, test_case_t{true, 20294, 286});
            test_args[17].test_cases.emplace_back(286, test_case_t{false, 9856, 286});
            test_args[29].test_cases.emplace_back(287, test_case_t{false, 1996, 287});
            test_args[20].test_cases.emplace_back(288, test_case_t{false, 6326, 288});
            test_args[11].test_cases.emplace_back(289, test_case_t{false, 13310, 289});
            test_args[30].test_cases.emplace_back(289, test_case_t{false, 13365, 289});
            test_args[5].test_cases.emplace_back(291, test_case_t{false, 31813, 291});
            test_args[8].test_cases.emplace_back(291, test_case_t{false, 15638, 291});
            test_args[14].test_cases.emplace_back(291, test_case_t{false, 10982, 291});
            test_args[22].test_cases.emplace_back(292, test_case_t{false, 8900, 292});
            test_args[23].test_cases.emplace_back(292, test_case_t{true, 6733, 292});
            test_args[15].test_cases.emplace_back(294, test_case_t{true, 21129, 294});
            test_args[31].test_cases.emplace_back(294, test_case_t{false, 24734, 294});
            test_args[16].test_cases.emplace_back(296, test_case_t{true, 31277, 296});
            test_args[0].test_cases.emplace_back(296, test_case_t{false, 1132, 296});
            test_args[27].test_cases.emplace_back(302, test_case_t{true, 7943, 302});
            test_args[6].test_cases.emplace_back(303, test_case_t{false, 28113, 303});
            test_args[26].test_cases.emplace_back(304, test_case_t{false, 32400, 304});
            test_args[18].test_cases.emplace_back(305, test_case_t{false, 7306, 305});
            test_args[28].test_cases.emplace_back(305, test_case_t{true, 12471, 305});
            test_args[10].test_cases.emplace_back(307, test_case_t{true, 30856, 307});
            test_args[2].test_cases.emplace_back(308, test_case_t{false, 22658, 308});
            test_args[17].test_cases.emplace_back(308, test_case_t{false, 8654, 308});
            test_args[25].test_cases.emplace_back(308, test_case_t{false, 24293, 308});
            test_args[12].test_cases.emplace_back(309, test_case_t{true, 10812, 309});
            test_args[29].test_cases.emplace_back(309, test_case_t{false, 7065, 309});
            test_args[4].test_cases.emplace_back(310, test_case_t{true, 7819, 310});
            test_args[20].test_cases.emplace_back(310, test_case_t{true, 29965, 310});
            test_args[11].test_cases.emplace_back(311, test_case_t{false, 26311, 311});
            test_args[30].test_cases.emplace_back(311, test_case_t{true, 1658, 311});
            test_args[5].test_cases.emplace_back(313, test_case_t{true, 17966, 313});
            test_args[8].test_cases.emplace_back(313, test_case_t{true, 25093, 313});
            test_args[14].test_cases.emplace_back(313, test_case_t{true, 27529, 313});
            test_args[22].test_cases.emplace_back(314, test_case_t{true, 26621, 314});
            test_args[23].test_cases.emplace_back(315, test_case_t{false, 15262, 315});
            test_args[15].test_cases.emplace_back(316, test_case_t{true, 6089, 316});
            test_args[31].test_cases.emplace_back(316, test_case_t{true, 29022, 316});
            test_args[16].test_cases.emplace_back(318, test_case_t{false, 17418, 318});
            test_args[0].test_cases.emplace_back(318, test_case_t{true, 1751, 318});
            test_args[27].test_cases.emplace_back(324, test_case_t{true, 11818, 324});
            test_args[6].test_cases.emplace_back(325, test_case_t{false, 2435, 325});
            test_args[26].test_cases.emplace_back(326, test_case_t{true, 29493, 326});
            test_args[28].test_cases.emplace_back(327, test_case_t{false, 14306, 327});
            test_args[10].test_cases.emplace_back(329, test_case_t{false, 3163, 329});
            test_args[17].test_cases.emplace_back(330, test_case_t{false, 28747, 330});
            test_args[25].test_cases.emplace_back(330, test_case_t{false, 21071, 330});
            test_args[2].test_cases.emplace_back(331, test_case_t{false, 2268, 331});
            test_args[12].test_cases.emplace_back(331, test_case_t{false, 23457, 331});
            test_args[29].test_cases.emplace_back(331, test_case_t{true, 20669, 331});
            test_args[4].test_cases.emplace_back(332, test_case_t{false, 12546, 332});
            test_args[20].test_cases.emplace_back(332, test_case_t{true, 22687, 332});
            test_args[11].test_cases.emplace_back(333, test_case_t{false, 28862, 333});
            test_args[30].test_cases.emplace_back(334, test_case_t{false, 27031, 334});
            test_args[8].test_cases.emplace_back(335, test_case_t{false, 9074, 335});
            test_args[14].test_cases.emplace_back(335, test_case_t{false, 15881, 335});
            test_args[5].test_cases.emplace_back(336, test_case_t{false, 23876, 336});
            test_args[22].test_cases.emplace_back(336, test_case_t{false, 19853, 336});
            test_args[18].test_cases.emplace_back(337, test_case_t{true, 20418, 337});
            test_args[23].test_cases.emplace_back(337, test_case_t{true, 3998, 337});
            test_args[15].test_cases.emplace_back(338, test_case_t{false, 630, 338});
            test_args[31].test_cases.emplace_back(339, test_case_t{true, 625, 339});
            test_args[0].test_cases.emplace_back(340, test_case_t{false, 17358, 340});
            test_args[6].test_cases.emplace_back(347, test_case_t{false, 6806, 347});
            test_args[26].test_cases.emplace_back(348, test_case_t{false, 23661, 348});
            test_args[28].test_cases.emplace_back(349, test_case_t{true, 21965, 349});
            test_args[10].test_cases.emplace_back(351, test_case_t{false, 14982, 351});
            test_args[2].test_cases.emplace_back(353, test_case_t{false, 19465, 353});
            test_args[4].test_cases.emplace_back(354, test_case_t{false, 4537, 354});
            test_args[11].test_cases.emplace_back(355, test_case_t{false, 8750, 355});
            test_args[27].test_cases.emplace_back(356, test_case_t{true, 10960, 356});
            test_args[30].test_cases.emplace_back(356, test_case_t{true, 9490, 356});
            test_args[8].test_cases.emplace_back(357, test_case_t{true, 12321, 357});
            test_args[5].test_cases.emplace_back(358, test_case_t{false, 22056, 358});
            test_args[14].test_cases.emplace_back(358, test_case_t{false, 5178, 358});
            test_args[22].test_cases.emplace_back(358, test_case_t{true, 24955, 358});
            test_args[18].test_cases.emplace_back(359, test_case_t{false, 11339, 359});
            test_args[15].test_cases.emplace_back(360, test_case_t{false, 14911, 360});
            test_args[23].test_cases.emplace_back(360, test_case_t{true, 31182, 360});
            test_args[17].test_cases.emplace_back(362, test_case_t{true, 2899, 362});
            test_args[25].test_cases.emplace_back(362, test_case_t{true, 11974, 362});
            test_args[0].test_cases.emplace_back(362, test_case_t{false, 21993, 362});
            test_args[12].test_cases.emplace_back(363, test_case_t{false, 4871, 363});
            test_args[20].test_cases.emplace_back(364, test_case_t{true, 30804, 364});
            test_args[29].test_cases.emplace_back(364, test_case_t{false, 32112, 364});
            test_args[29].test_cases.emplace_back(366, test_case_t{false, 849, 366});
            test_args[6].test_cases.emplace_back(369, test_case_t{true, 25626, 369});
            test_args[26].test_cases.emplace_back(370, test_case_t{false, 16346, 370});
            test_args[31].test_cases.emplace_back(371, test_case_t{true, 19637, 371});
            test_args[10].test_cases.emplace_back(373, test_case_t{true, 11343, 373});
            test_args[4].test_cases.emplace_back(376, test_case_t{true, 6160, 376});
            test_args[11].test_cases.emplace_back(377, test_case_t{true, 27081, 377});
            test_args[27].test_cases.emplace_back(378, test_case_t{false, 14242, 378});
            test_args[30].test_cases.emplace_back(378, test_case_t{true, 12178, 378});
            test_args[8].test_cases.emplace_back(379, test_case_t{true, 22674, 379});
            test_args[22].test_cases.emplace_back(380, test_case_t{false, 17500, 380});
            test_args[28].test_cases.emplace_back(381, test_case_t{false, 22289, 381});
            test_args[23].test_cases.emplace_back(382, test_case_t{true, 9705, 382});
            test_args[17].test_cases.emplace_back(384, test_case_t{false, 1606, 384});
            test_args[25].test_cases.emplace_back(384, test_case_t{false, 13928, 384});
            test_args[0].test_cases.emplace_back(384, test_case_t{false, 252, 384});
            test_args[12].test_cases.emplace_back(385, test_case_t{false, 13612, 385});
            test_args[20].test_cases.emplace_back(386, test_case_t{false, 7532, 386});
            test_args[0].test_cases.emplace_back(386, test_case_t{true, 12564, 386});
            test_args[0].test_cases.emplace_back(387, test_case_t{false, 2190, 387});
            test_args[29].test_cases.emplace_back(388, test_case_t{false, 16511, 388});
            test_args[5].test_cases.emplace_back(390, test_case_t{false, 15893, 390});
            test_args[14].test_cases.emplace_back(390, test_case_t{true, 31488, 390});
            test_args[18].test_cases.emplace_back(391, test_case_t{false, 26441, 391});
            test_args[26].test_cases.emplace_back(392, test_case_t{false, 50, 392});
            test_args[6].test_cases.emplace_back(393, test_case_t{false, 8813, 393});
            test_args[31].test_cases.emplace_back(393, test_case_t{false, 23507, 393});
            test_args[4].test_cases.emplace_back(398, test_case_t{false, 27722, 398});
            test_args[11].test_cases.emplace_back(399, test_case_t{false, 27749, 399});
            test_args[27].test_cases.emplace_back(400, test_case_t{true, 624, 400});
            test_args[30].test_cases.emplace_back(400, test_case_t{false, 1261, 400});
            test_args[22].test_cases.emplace_back(402, test_case_t{true, 21394, 402});
            test_args[23].test_cases.emplace_back(404, test_case_t{true, 27232, 404});
            test_args[17].test_cases.emplace_back(406, test_case_t{true, 3126, 406});
            test_args[25].test_cases.emplace_back(406, test_case_t{false, 25800, 406});
            test_args[0].test_cases.emplace_back(409, test_case_t{false, 13680, 409});
            test_args[29].test_cases.emplace_back(410, test_case_t{false, 20089, 410});
            test_args[8].test_cases.emplace_back(411, test_case_t{true, 20181, 411});
            test_args[5].test_cases.emplace_back(412, test_case_t{false, 18267, 412});
            test_args[14].test_cases.emplace_back(412, test_case_t{false, 2547, 412});
            test_args[18].test_cases.emplace_back(413, test_case_t{true, 12638, 413});
            test_args[28].test_cases.emplace_back(413, test_case_t{false, 31762, 413});
            test_args[26].test_cases.emplace_back(414, test_case_t{false, 22547, 414});
            test_args[6].test_cases.emplace_back(415, test_case_t{false, 15135, 415});
            test_args[28].test_cases.emplace_back(415, test_case_t{true, 10356, 415});
            test_args[31].test_cases.emplace_back(415, test_case_t{true, 18780, 415});
            test_args[10].test_cases.emplace_back(417, test_case_t{false, 31787, 417});
            test_args[12].test_cases.emplace_back(417, test_case_t{true, 18482, 417});
            test_args[4].test_cases.emplace_back(420, test_case_t{true, 10090, 420});
            test_args[11].test_cases.emplace_back(421, test_case_t{true, 5758, 421});
            test_args[30].test_cases.emplace_back(423, test_case_t{true, 29822, 423});
            test_args[22].test_cases.emplace_back(424, test_case_t{true, 22728, 424});
            test_args[23].test_cases.emplace_back(426, test_case_t{false, 11939, 426});
            test_args[17].test_cases.emplace_back(428, test_case_t{false, 10115, 428});
            test_args[25].test_cases.emplace_back(428, test_case_t{true, 30296, 428});
            test_args[0].test_cases.emplace_back(431, test_case_t{false, 22505, 431});
            test_args[29].test_cases.emplace_back(432, test_case_t{false, 20753, 432});
            test_args[8].test_cases.emplace_back(433, test_case_t{true, 22062, 433});
            test_args[27].test_cases.emplace_back(433, test_case_t{false, 6892, 433});
            test_args[5].test_cases.emplace_back(434, test_case_t{true, 12613, 434});
            test_args[14].test_cases.emplace_back(434, test_case_t{true, 22223, 434});
            test_args[18].test_cases.emplace_back(435, test_case_t{false, 485, 435});
            test_args[26].test_cases.emplace_back(436, test_case_t{false, 12419, 436});
            test_args[6].test_cases.emplace_back(437, test_case_t{false, 161, 437});
            test_args[28].test_cases.emplace_back(437, test_case_t{true, 30207, 437});
            test_args[31].test_cases.emplace_back(437, test_case_t{false, 6785, 437});
            test_args[10].test_cases.emplace_back(439, test_case_t{false, 3766, 439});
            test_args[12].test_cases.emplace_back(439, test_case_t{false, 17627, 439});
            test_args[4].test_cases.emplace_back(442, test_case_t{true, 11031, 442});
            test_args[11].test_cases.emplace_back(443, test_case_t{false, 11556, 443});
            test_args[30].test_cases.emplace_back(445, test_case_t{false, 11299, 445});
            test_args[22].test_cases.emplace_back(446, test_case_t{false, 11516, 446});
            test_args[23].test_cases.emplace_back(448, test_case_t{false, 25251, 448});
            test_args[17].test_cases.emplace_back(450, test_case_t{false, 5920, 450});
            test_args[25].test_cases.emplace_back(450, test_case_t{true, 27982, 450});
            test_args[0].test_cases.emplace_back(453, test_case_t{true, 19300, 453});
            test_args[8].test_cases.emplace_back(455, test_case_t{true, 11383, 455});
            test_args[5].test_cases.emplace_back(456, test_case_t{true, 5596, 456});
            test_args[14].test_cases.emplace_back(457, test_case_t{false, 11728, 457});
            test_args[18].test_cases.emplace_back(457, test_case_t{false, 1035, 457});
            test_args[28].test_cases.emplace_back(459, test_case_t{true, 5095, 459});
            test_args[31].test_cases.emplace_back(459, test_case_t{false, 1845, 459});
            test_args[10].test_cases.emplace_back(461, test_case_t{true, 25226, 461});
            test_args[12].test_cases.emplace_back(461, test_case_t{true, 30271, 461});
            test_args[4].test_cases.emplace_back(464, test_case_t{false, 22076, 464});
            test_args[30].test_cases.emplace_back(467, test_case_t{true, 10140, 467});
            test_args[22].test_cases.emplace_back(468, test_case_t{true, 23112, 468});
            test_args[26].test_cases.emplace_back(468, test_case_t{true, 17903, 468});
            test_args[23].test_cases.emplace_back(470, test_case_t{false, 6082, 470});
            test_args[25].test_cases.emplace_back(472, test_case_t{true, 23284, 472});
            test_args[0].test_cases.emplace_back(475, test_case_t{false, 30489, 475});
            test_args[8].test_cases.emplace_back(477, test_case_t{true, 13071, 477});
            test_args[5].test_cases.emplace_back(478, test_case_t{true, 11210, 478});
            test_args[14].test_cases.emplace_back(479, test_case_t{false, 14681, 479});
            test_args[18].test_cases.emplace_back(479, test_case_t{true, 4832, 479});
            test_args[18].test_cases.emplace_back(481, test_case_t{true, 20287, 481});
            test_args[28].test_cases.emplace_back(481, test_case_t{false, 11678, 481});
            test_args[31].test_cases.emplace_back(481, test_case_t{true, 12663, 481});
            test_args[10].test_cases.emplace_back(483, test_case_t{true, 11192, 483});
            test_args[12].test_cases.emplace_back(483, test_case_t{true, 323, 483});
            test_args[4].test_cases.emplace_back(486, test_case_t{true, 22920, 486});
            test_args[26].test_cases.emplace_back(490, test_case_t{true, 18380, 490});
            test_args[23].test_cases.emplace_back(492, test_case_t{false, 12246, 492});
            test_args[8].test_cases.emplace_back(499, test_case_t{false, 30862, 499});
            test_args[30].test_cases.emplace_back(499, test_case_t{true, 809, 499});
            test_args[18].test_cases.emplace_back(503, test_case_t{true, 517, 503});
            test_args[10].test_cases.emplace_back(505, test_case_t{true, 22421, 505});
            test_args[4].test_cases.emplace_back(508, test_case_t{true, 15431, 508});
            test_args[14].test_cases.emplace_back(511, test_case_t{false, 4855, 511});
            test_args[23].test_cases.emplace_back(514, test_case_t{false, 713, 514});
            test_args[12].test_cases.emplace_back(515, test_case_t{true, 690, 515});
            test_args[30].test_cases.emplace_back(521, test_case_t{true, 1726, 521});
            test_args[26].test_cases.emplace_back(522, test_case_t{false, 4388, 522});
            test_args[18].test_cases.emplace_back(525, test_case_t{true, 15682, 525});
            test_args[10].test_cases.emplace_back(527, test_case_t{false, 24531, 527});
            test_args[8].test_cases.emplace_back(531, test_case_t{false, 3871, 531});
            test_args[14].test_cases.emplace_back(533, test_case_t{false, 14966, 533});
            test_args[23].test_cases.emplace_back(536, test_case_t{true, 31384, 536});
            test_args[12].test_cases.emplace_back(537, test_case_t{true, 3221, 537});
            test_args[30].test_cases.emplace_back(543, test_case_t{false, 8054, 543});
            test_args[26].test_cases.emplace_back(544, test_case_t{false, 29934, 544});
            test_args[18].test_cases.emplace_back(547, test_case_t{true, 10159, 547});
            test_args[10].test_cases.emplace_back(549, test_case_t{false, 22193, 549});
            test_args[8].test_cases.emplace_back(553, test_case_t{false, 14252, 553});
            test_args[30].test_cases.emplace_back(565, test_case_t{true, 1042, 565});
            test_args[26].test_cases.emplace_back(566, test_case_t{true, 111, 566});
            test_args[18].test_cases.emplace_back(569, test_case_t{true, 27761, 569});
            test_args[10].test_cases.emplace_back(571, test_case_t{true, 29416, 571});
            test_args[8].test_cases.emplace_back(585, test_case_t{true, 22720, 585});
            test_args[30].test_cases.emplace_back(587, test_case_t{false, 22709, 587});
            test_args[26].test_cases.emplace_back(588, test_case_t{true, 48, 588});
            test_args[26].test_cases.emplace_back(589, test_case_t{false, 29848, 589});
            test_args[18].test_cases.emplace_back(601, test_case_t{true, 18143, 601});
            test_args[10].test_cases.emplace_back(603, test_case_t{true, 1430, 603});
            test_args[8].test_cases.emplace_back(617, test_case_t{false, 5056, 617});
            test_args[18].test_cases.emplace_back(623, test_case_t{false, 23116, 623});
            test_args[10].test_cases.emplace_back(625, test_case_t{false, 20208, 625});
            test_args[8].test_cases.emplace_back(649, test_case_t{false, 11704, 649});
            test_args[10].test_cases.emplace_back(657, test_case_t{true, 22705, 657});
            test_args[8].test_cases.emplace_back(671, test_case_t{false, 10273, 671});
            test_args[8].test_cases.emplace_back(673, test_case_t{false, 9173, 673});
            test_args[10].test_cases.emplace_back(679, test_case_t{true, 6438, 679});
            break;
        case 35:
            test_args[1].test_cases.emplace_back(0, test_case_t{true, 2, 0});
            test_args[2].test_cases.emplace_back(0, test_case_t{false, 5, 0});
            test_args[3].test_cases.emplace_back(0, test_case_t{true, 7, 0});
            test_args[4].test_cases.emplace_back(0, test_case_t{true, 10, 0});
            test_args[5].test_cases.emplace_back(0, test_case_t{true, 12, 0});
            test_args[6].test_cases.emplace_back(0, test_case_t{true, 15, 0});
            test_args[7].test_cases.emplace_back(0, test_case_t{false, 17, 0});
            test_args[8].test_cases.emplace_back(0, test_case_t{false, 20, 0});
            test_args[9].test_cases.emplace_back(0, test_case_t{true, 23, 0});
            test_args[10].test_cases.emplace_back(0, test_case_t{true, 25, 0});
            test_args[11].test_cases.emplace_back(0, test_case_t{false, 28, 0});
            test_args[12].test_cases.emplace_back(0, test_case_t{true, 30, 0});
            test_args[13].test_cases.emplace_back(0, test_case_t{false, 33, 0});
            test_args[14].test_cases.emplace_back(0, test_case_t{true, 35, 0});
            test_args[15].test_cases.emplace_back(0, test_case_t{true, 38, 0});
            test_args[16].test_cases.emplace_back(0, test_case_t{false, 41, 0});
            test_args[17].test_cases.emplace_back(0, test_case_t{false, 43, 0});
            test_args[18].test_cases.emplace_back(0, test_case_t{false, 46, 0});
            test_args[19].test_cases.emplace_back(0, test_case_t{false, 48, 0});
            test_args[20].test_cases.emplace_back(0, test_case_t{false, 51, 0});
            test_args[21].test_cases.emplace_back(0, test_case_t{true, 53, 0});
            test_args[22].test_cases.emplace_back(0, test_case_t{false, 56, 0});
            test_args[23].test_cases.emplace_back(0, test_case_t{true, 58, 0});
            test_args[24].test_cases.emplace_back(0, test_case_t{true, 61, 0});
            test_args[25].test_cases.emplace_back(0, test_case_t{false, 64, 0});
            test_args[26].test_cases.emplace_back(0, test_case_t{false, 66, 0});
            test_args[27].test_cases.emplace_back(0, test_case_t{false, 69, 0});
            test_args[28].test_cases.emplace_back(0, test_case_t{true, 71, 0});
            test_args[29].test_cases.emplace_back(0, test_case_t{true, 74, 0});
            test_args[30].test_cases.emplace_back(0, test_case_t{true, 76, 0});
            test_args[31].test_cases.emplace_back(0, test_case_t{true, 79, 0});
            test_args[0].test_cases.emplace_back(0, test_case_t{false, 0, 0});
            test_args[0].test_cases.emplace_back(2, test_case_t{false, 4310, 2});
            test_args[1].test_cases.emplace_back(22, test_case_t{false, 10334, 22});
            test_args[7].test_cases.emplace_back(28, test_case_t{true, 6804, 28});
            test_args[0].test_cases.emplace_back(31, test_case_t{true, 24760, 31});
            test_args[2].test_cases.emplace_back(33, test_case_t{true, 20668, 33});
            test_args[0].test_cases.emplace_back(33, test_case_t{false, 15029, 33});
            test_args[13].test_cases.emplace_back(37, test_case_t{true, 3273, 37});
            test_args[8].test_cases.emplace_back(39, test_case_t{false, 17138, 39});
            test_args[11].test_cases.emplace_back(45, test_case_t{true, 15373, 45});
            test_args[3].test_cases.emplace_back(46, test_case_t{true, 31003, 46});
            test_args[14].test_cases.emplace_back(48, test_case_t{true, 13608, 48});
            test_args[19].test_cases.emplace_back(52, test_case_t{true, 32512, 52});
            test_args[2].test_cases.emplace_back(55, test_case_t{false, 3673, 55});
            test_args[9].test_cases.emplace_back(56, test_case_t{true, 27473, 56});
            test_args[4].test_cases.emplace_back(57, test_case_t{false, 8569, 57});
            test_args[8].test_cases.emplace_back(61, test_case_t{false, 14694, 61});
            test_args[20].test_cases.emplace_back(63, test_case_t{true, 10078, 63});
            test_args[25].test_cases.emplace_back(64, test_case_t{false, 28982, 64});
            test_args[0].test_cases.emplace_back(65, test_case_t{true, 17457, 65});
            test_args[10].test_cases.emplace_back(67, test_case_t{false, 5039, 67});
            test_args[11].test_cases.emplace_back(67, test_case_t{true, 3820, 67});
            test_args[14].test_cases.emplace_back(71, test_case_t{false, 25714, 71});
            test_args[22].test_cases.emplace_back(71, test_case_t{false, 30747, 71});
            test_args[2].test_cases.emplace_back(77, test_case_t{true, 5669, 77});
            test_args[4].test_cases.emplace_back(79, test_case_t{false, 7347, 79});
            test_args[26].test_cases.emplace_back(79, test_case_t{false, 6547, 79});
            test_args[27].test_cases.emplace_back(81, test_case_t{false, 16882, 81});
            test_args[15].test_cases.emplace_back(82, test_case_t{true, 23942, 82});
            test_args[8].test_cases.emplace_back(83, test_case_t{true, 22676, 83});
            test_args[20].test_cases.emplace_back(85, test_case_t{true, 3967, 85});
            test_args[21].test_cases.emplace_back(86, test_case_t{false, 20412, 86});
            test_args[25].test_cases.emplace_back(86, test_case_t{true, 29535, 86});
            test_args[10].test_cases.emplace_back(89, test_case_t{false, 18367, 89});
            test_args[11].test_cases.emplace_back(89, test_case_t{true, 14795, 89});
            test_args[5].test_cases.emplace_back(92, test_case_t{false, 18903, 92});
            test_args[22].test_cases.emplace_back(93, test_case_t{true, 7640, 93});
            test_args[28].test_cases.emplace_back(95, test_case_t{true, 27216, 95});
            test_args[0].test_cases.emplace_back(98, test_case_t{true, 7174, 98});
            test_args[2].test_cases.emplace_back(99, test_case_t{false, 21474, 99});
            test_args[4].test_cases.emplace_back(101, test_case_t{true, 11338, 101});
            test_args[12].test_cases.emplace_back(101, test_case_t{false, 25708, 101});
            test_args[26].test_cases.emplace_back(101, test_case_t{true, 14987, 101});
            test_args[23].test_cases.emplace_back(102, test_case_t{false, 8313, 102});
            test_args[26].test_cases.emplace_back(103, test_case_t{true, 8160, 103});
            test_args[27].test_cases.emplace_back(103, test_case_t{false, 440, 103});
            test_args[15].test_cases.emplace_back(104, test_case_t{false, 11167, 104});
            test_args[8].test_cases.emplace_back(105, test_case_t{true, 20361, 105});
            test_args[20].test_cases.emplace_back(107, test_case_t{false, 23921, 107});
            test_args[21].test_cases.emplace_back(108, test_case_t{true, 22188, 108});
            test_args[25].test_cases.emplace_back(108, test_case_t{false, 21710, 108});
            test_args[29].test_cases.emplace_back(110, test_case_t{false, 4782, 110});
            test_args[11].test_cases.emplace_back(111, test_case_t{false, 19805, 111});
            test_args[10].test_cases.emplace_back(113, test_case_t{false, 28345, 113});
            test_args[5].test_cases.emplace_back(114, test_case_t{false, 25568, 114});
            test_args[16].test_cases.emplace_back(115, test_case_t{true, 1508, 115});
            test_args[22].test_cases.emplace_back(115, test_case_t{true, 29590, 115});
            test_args[28].test_cases.emplace_back(117, test_case_t{false, 18661, 117});
            test_args[0].test_cases.emplace_back(120, test_case_t{true, 1541, 120});
            test_args[2].test_cases.emplace_back(121, test_case_t{false, 12425, 121});
            test_args[4].test_cases.emplace_back(123, test_case_t{false, 10180, 123});
            test_args[12].test_cases.emplace_back(123, test_case_t{false, 22041, 123});
            test_args[23].test_cases.emplace_back(124, test_case_t{false, 25861, 124});
            test_args[26].test_cases.emplace_back(125, test_case_t{true, 17022, 125});
            test_args[27].test_cases.emplace_back(125, test_case_t{false, 27379, 125});
            test_args[6].test_cases.emplace_back(127, test_case_t{false, 29238, 127});
            test_args[8].test_cases.emplace_back(127, test_case_t{false, 16932, 127});
            test_args[17].test_cases.emplace_back(128, test_case_t{false, 11843, 128});
            test_args[18].test_cases.emplace_back(129, test_case_t{true, 22177, 129});
            test_args[20].test_cases.emplace_back(129, test_case_t{true, 18135, 129});
            test_args[21].test_cases.emplace_back(130, test_case_t{false, 10372, 130});
            test_args[25].test_cases.emplace_back(130, test_case_t{false, 6285, 130});
            test_args[29].test_cases.emplace_back(132, test_case_t{false, 4113, 132});
            test_args[11].test_cases.emplace_back(133, test_case_t{true, 2802, 133});
            test_args[10].test_cases.emplace_back(135, test_case_t{true, 9067, 135});
            test_args[24].test_cases.emplace_back(135, test_case_t{true, 18647, 135});
            test_args[5].test_cases.emplace_back(136, test_case_t{false, 30556, 136});
            test_args[16].test_cases.emplace_back(137, test_case_t{true, 29388, 137});
            test_args[22].test_cases.emplace_back(137, test_case_t{false, 6841, 137});
            test_args[28].test_cases.emplace_back(139, test_case_t{false, 13829, 139});
            test_args[0].test_cases.emplace_back(142, test_case_t{false, 22245, 142});
            test_args[2].test_cases.emplace_back(143, test_case_t{true, 30831, 143});
            test_args[30].test_cases.emplace_back(143, test_case_t{false, 15117, 143});
            test_args[4].test_cases.emplace_back(145, test_case_t{false, 24850, 145});
            test_args[12].test_cases.emplace_back(145, test_case_t{true, 1245, 145});
            test_args[26].test_cases.emplace_back(147, test_case_t{true, 30454, 147});
            test_args[27].test_cases.emplace_back(147, test_case_t{true, 27759, 147});
            test_args[6].test_cases.emplace_back(149, test_case_t{false, 11020, 149});
            test_args[8].test_cases.emplace_back(150, test_case_t{true, 25021, 150});
            test_args[17].test_cases.emplace_back(150, test_case_t{false, 14841, 150});
            test_args[20].test_cases.emplace_back(151, test_case_t{true, 25947, 151});
            test_args[25].test_cases.emplace_back(152, test_case_t{true, 24242, 152});
            test_args[21].test_cases.emplace_back(153, test_case_t{true, 28872, 153});
            test_args[11].test_cases.emplace_back(155, test_case_t{true, 5731, 155});
            test_args[24].test_cases.emplace_back(157, test_case_t{true, 11314, 157});
            test_args[5].test_cases.emplace_back(158, test_case_t{true, 20918, 158});
            test_args[10].test_cases.emplace_back(158, test_case_t{true, 29357, 158});
            test_args[16].test_cases.emplace_back(159, test_case_t{true, 12583, 159});
            test_args[22].test_cases.emplace_back(159, test_case_t{true, 5604, 159});
            test_args[18].test_cases.emplace_back(161, test_case_t{true, 293, 161});
            test_args[28].test_cases.emplace_back(161, test_case_t{false, 5728, 161});
            test_args[2].test_cases.emplace_back(165, test_case_t{true, 18917, 165});
            test_args[30].test_cases.emplace_back(165, test_case_t{true, 22334, 165});
            test_args[0].test_cases.emplace_back(165, test_case_t{false, 22259, 165});
            test_args[4].test_cases.emplace_back(167, test_case_t{true, 28894, 167});
            test_args[12].test_cases.emplace_back(167, test_case_t{false, 30542, 167});
            test_args[27].test_cases.emplace_back(169, test_case_t{true, 3898, 169});
            test_args[26].test_cases.emplace_back(170, test_case_t{true, 7589, 170});
            test_args[6].test_cases.emplace_back(171, test_case_t{false, 17007, 171});
            test_args[8].test_cases.emplace_back(172, test_case_t{false, 10131, 172});
            test_args[17].test_cases.emplace_back(172, test_case_t{true, 31802, 172});
            test_args[20].test_cases.emplace_back(173, test_case_t{false, 13399, 173});
            test_args[25].test_cases.emplace_back(174, test_case_t{true, 24941, 174});
            test_args[20].test_cases.emplace_back(175, test_case_t{true, 25328, 175});
            test_args[21].test_cases.emplace_back(175, test_case_t{true, 32159, 175});
            test_args[31].test_cases.emplace_back(176, test_case_t{false, 25451, 176});
            test_args[11].test_cases.emplace_back(177, test_case_t{false, 22122, 177});
            test_args[24].test_cases.emplace_back(179, test_case_t{false, 2491, 179});
            test_args[5].test_cases.emplace_back(180, test_case_t{true, 31063, 180});
            test_args[10].test_cases.emplace_back(180, test_case_t{false, 23084, 180});
            test_args[16].test_cases.emplace_back(181, test_case_t{true, 7954, 181});
            test_args[22].test_cases.emplace_back(181, test_case_t{false, 11462, 181});
            test_args[18].test_cases.emplace_back(183, test_case_t{true, 18252, 183});
            test_args[2].test_cases.emplace_back(187, test_case_t{false, 19199, 187});
            test_args[0].test_cases.emplace_back(187, test_case_t{true, 30628, 187});
            test_args[4].test_cases.emplace_back(189, test_case_t{false, 5065, 189});
            test_args[12].test_cases.emplace_back(190, test_case_t{true, 9014, 190});
            test_args[27].test_cases.emplace_back(191, test_case_t{true, 23005, 191});
            test_args[26].test_cases.emplace_back(192, test_case_t{true, 16542, 192});
            test_args[6].test_cases.emplace_back(193, test_case_t{true, 31655, 193});
            test_args[28].test_cases.emplace_back(193, test_case_t{false, 10111, 193});
            test_args[8].test_cases.emplace_back(194, test_case_t{false, 11262, 194});
            test_args[17].test_cases.emplace_back(194, test_case_t{false, 18692, 194});
            test_args[25].test_cases.emplace_back(196, test_case_t{true, 23468, 196});
            test_args[21].test_cases.emplace_back(197, test_case_t{false, 28815, 197});
            test_args[20].test_cases.emplace_back(198, test_case_t{true, 28157, 198});
            test_args[31].test_cases.emplace_back(198, test_case_t{false, 7787, 198});
            test_args[11].test_cases.emplace_back(199, test_case_t{false, 23678, 199});
            test_args[24].test_cases.emplace_back(201, test_case_t{false, 28316, 201});
            test_args[5].test_cases.emplace_back(202, test_case_t{false, 11542, 202});
            test_args[10].test_cases.emplace_back(203, test_case_t{false, 29048, 203});
            test_args[16].test_cases.emplace_back(203, test_case_t{true, 1096, 203});
            test_args[22].test_cases.emplace_back(203, test_case_t{false, 11476, 203});
            test_args[18].test_cases.emplace_back(205, test_case_t{true, 29429, 205});
            test_args[18].test_cases.emplace_back(207, test_case_t{true, 13522, 207});
            test_args[2].test_cases.emplace_back(209, test_case_t{true, 22736, 209});
            test_args[0].test_cases.emplace_back(209, test_case_t{true, 12566, 209});
            test_args[4].test_cases.emplace_back(211, test_case_t{true, 5631, 211});
            test_args[12].test_cases.emplace_back(212, test_case_t{false, 21147, 212});
            test_args[27].test_cases.emplace_back(213, test_case_t{false, 9616, 213});
            test_args[26].test_cases.emplace_back(214, test_case_t{true, 20220, 214});
            test_args[6].test_cases.emplace_back(215, test_case_t{true, 4507, 215});
            test_args[28].test_cases.emplace_back(215, test_case_t{false, 5652, 215});
            test_args[8].test_cases.emplace_back(216, test_case_t{true, 25409, 216});
            test_args[17].test_cases.emplace_back(216, test_case_t{true, 7309, 216});
            test_args[25].test_cases.emplace_back(218, test_case_t{false, 27004, 218});
            test_args[21].test_cases.emplace_back(219, test_case_t{true, 18402, 219});
            test_args[20].test_cases.emplace_back(220, test_case_t{false, 30755, 220});
            test_args[31].test_cases.emplace_back(220, test_case_t{true, 5948, 220});
            test_args[11].test_cases.emplace_back(221, test_case_t{true, 26746, 221});
            test_args[24].test_cases.emplace_back(223, test_case_t{true, 18029, 223});
            test_args[5].test_cases.emplace_back(224, test_case_t{true, 30908, 224});
            test_args[10].test_cases.emplace_back(225, test_case_t{true, 30462, 225});
            test_args[16].test_cases.emplace_back(225, test_case_t{false, 17273, 225});
            test_args[22].test_cases.emplace_back(225, test_case_t{false, 14588, 225});
            test_args[18].test_cases.emplace_back(229, test_case_t{true, 15336, 229});
            test_args[2].test_cases.emplace_back(231, test_case_t{true, 21956, 231});
            test_args[0].test_cases.emplace_back(231, test_case_t{false, 17020, 231});
            test_args[4].test_cases.emplace_back(233, test_case_t{true, 12704, 233});
            test_args[12].test_cases.emplace_back(234, test_case_t{false, 15196, 234});
            test_args[27].test_cases.emplace_back(235, test_case_t{false, 13436, 235});
            test_args[26].test_cases.emplace_back(236, test_case_t{true, 660, 236});
            test_args[6].test_cases.emplace_back(237, test_case_t{true, 26957, 237});
            test_args[28].test_cases.emplace_back(237, test_case_t{true, 2690, 237});
            test_args[8].test_cases.emplace_back(238, test_case_t{false, 22288, 238});
            test_args[17].test_cases.emplace_back(238, test_case_t{false, 32689, 238});
            test_args[25].test_cases.emplace_back(240, test_case_t{false, 22060, 240});
            test_args[21].test_cases.emplace_back(241, test_case_t{false, 21373, 241});
            test_args[20].test_cases.emplace_back(242, test_case_t{false, 22951, 242});
            test_args[31].test_cases.emplace_back(242, test_case_t{false, 5172, 242});
            test_args[11].test_cases.emplace_back(243, test_case_t{false, 6069, 243});
            test_args[24].test_cases.emplace_back(245, test_case_t{true, 9526, 245});
            test_args[5].test_cases.emplace_back(246, test_case_t{true, 31615, 246});
            test_args[16].test_cases.emplace_back(247, test_case_t{true, 20262, 247});
            test_args[22].test_cases.emplace_back(248, test_case_t{false, 20724, 248});
            test_args[18].test_cases.emplace_back(251, test_case_t{false, 6411, 251});
            test_args[2].test_cases.emplace_back(253, test_case_t{true, 12724, 253});
            test_args[4].test_cases.emplace_back(255, test_case_t{false, 11144, 255});
            test_args[12].test_cases.emplace_back(256, test_case_t{true, 16894, 256});
            test_args[10].test_cases.emplace_back(257, test_case_t{false, 15377, 257});
            test_args[27].test_cases.emplace_back(257, test_case_t{true, 12028, 257});
            test_args[26].test_cases.emplace_back(258, test_case_t{false, 23283, 258});
            test_args[6].test_cases.emplace_back(259, test_case_t{true, 23982, 259});
            test_args[28].test_cases.emplace_back(259, test_case_t{false, 6651, 259});
            test_args[8].test_cases.emplace_back(260, test_case_t{false, 18131, 260});
            test_args[17].test_cases.emplace_back(260, test_case_t{true, 13336, 260});
            test_args[26].test_cases.emplace_back(260, test_case_t{true, 1581, 260});
            test_args[25].test_cases.emplace_back(262, test_case_t{false, 28689, 262});
            test_args[0].test_cases.emplace_back(263, test_case_t{false, 27229, 263});
            test_args[20].test_cases.emplace_back(264, test_case_t{true, 28943, 264});
            test_args[21].test_cases.emplace_back(264, test_case_t{false, 9355, 264});
            test_args[31].test_cases.emplace_back(264, test_case_t{false, 28749, 264});
            test_args[11].test_cases.emplace_back(265, test_case_t{false, 4449, 265});
            test_args[24].test_cases.emplace_back(267, test_case_t{true, 30393, 267});
            test_args[5].test_cases.emplace_back(268, test_case_t{true, 24073, 268});
            test_args[16].test_cases.emplace_back(269, test_case_t{true, 22525, 269});
            test_args[22].test_cases.emplace_back(270, test_case_t{false, 12139, 270});
            test_args[18].test_cases.emplace_back(273, test_case_t{false, 8957, 273});
            test_args[2].test_cases.emplace_back(275, test_case_t{true, 20293, 275});
            test_args[4].test_cases.emplace_back(277, test_case_t{false, 25449, 277});
            test_args[10].test_cases.emplace_back(279, test_case_t{false, 11475, 279});
            test_args[27].test_cases.emplace_back(280, test_case_t{true, 17877, 280});
            test_args[6].test_cases.emplace_back(281, test_case_t{true, 24831, 281});
            test_args[28].test_cases.emplace_back(281, test_case_t{false, 23397, 281});
            test_args[17].test_cases.emplace_back(282, test_case_t{false, 15741, 282});
            test_args[26].test_cases.emplace_back(283, test_case_t{false, 1670, 283});
            test_args[25].test_cases.emplace_back(284, test_case_t{false, 27987, 284});
            test_args[20].test_cases.emplace_back(286, test_case_t{true, 6326, 286});
            test_args[21].test_cases.emplace_back(286, test_case_t{false, 17545, 286});
            test_args[31].test_cases.emplace_back(286, test_case_t{true, 19131, 286});
            test_args[11].test_cases.emplace_back(288, test_case_t{true, 13310, 288});
            test_args[12].test_cases.emplace_back(288, test_case_t{true, 5346, 288});
            test_args[24].test_cases.emplace_back(289, test_case_t{false, 1020, 289});
            test_args[5].test_cases.emplace_back(290, test_case_t{false, 5737, 290});
            test_args[16].test_cases.emplace_back(291, test_case_t{true, 18050, 291});
            test_args[8].test_cases.emplace_back(292, test_case_t{false, 15638, 292});
            test_args[22].test_cases.emplace_back(292, test_case_t{false, 8899, 292});
            test_args[18].test_cases.emplace_back(295, test_case_t{false, 8019, 295});
            test_args[0].test_cases.emplace_back(295, test_case_t{false, 1132, 295});
            test_args[2].test_cases.emplace_back(297, test_case_t{false, 22657, 297});
            test_args[27].test_cases.emplace_back(302, test_case_t{true, 7943, 302});
            test_args[6].test_cases.emplace_back(303, test_case_t{false, 2673, 303});
            test_args[28].test_cases.emplace_back(303, test_case_t{false, 12471, 303});
            test_args[17].test_cases.emplace_back(304, test_case_t{false, 29419, 304});
            test_args[26].test_cases.emplace_back(305, test_case_t{false, 32399, 305});
            test_args[25].test_cases.emplace_back(306, test_case_t{false, 24292, 306});
            test_args[20].test_cases.emplace_back(308, test_case_t{true, 29964, 308});
            test_args[21].test_cases.emplace_back(308, test_case_t{false, 2537, 308});
            test_args[31].test_cases.emplace_back(308, test_case_t{false, 14682, 308});
            test_args[4].test_cases.emplace_back(309, test_case_t{false, 7819, 309});
            test_args[11].test_cases.emplace_back(310, test_case_t{false, 26310, 310});
            test_args[12].test_cases.emplace_back(310, test_case_t{false, 663, 310});
            test_args[10].test_cases.emplace_back(311, test_case_t{true, 30856, 311});
            test_args[24].test_cases.emplace_back(311, test_case_t{true, 10692, 311});
            test_args[5].test_cases.emplace_back(313, test_case_t{false, 31812, 313});
            test_args[8].test_cases.emplace_back(314, test_case_t{false, 25093, 314});
            test_args[16].test_cases.emplace_back(314, test_case_t{true, 11807, 314});
            test_args[22].test_cases.emplace_back(314, test_case_t{true, 26620, 314});
            test_args[18].test_cases.emplace_back(317, test_case_t{true, 995, 317});
            test_args[0].test_cases.emplace_back(317, test_case_t{true, 1751, 317});
            test_args[2].test_cases.emplace_back(319, test_case_t{false, 2268, 319});
            test_args[27].test_cases.emplace_back(324, test_case_t{true, 11817, 324});
            test_args[6].test_cases.emplace_back(325, test_case_t{false, 331, 325});
            test_args[28].test_cases.emplace_back(325, test_case_t{false, 14306, 325});
            test_args[17].test_cases.emplace_back(326, test_case_t{true, 6401, 326});
            test_args[26].test_cases.emplace_back(327, test_case_t{true, 29492, 327});
            test_args[25].test_cases.emplace_back(328, test_case_t{true, 21071, 328});
            test_args[20].test_cases.emplace_back(330, test_case_t{true, 22686, 330});
            test_args[21].test_cases.emplace_back(330, test_case_t{false, 16473, 330});
            test_args[31].test_cases.emplace_back(330, test_case_t{true, 19067, 330});
            test_args[4].test_cases.emplace_back(331, test_case_t{true, 12546, 331});
            test_args[11].test_cases.emplace_back(332, test_case_t{true, 28861, 332});
            test_args[10].test_cases.emplace_back(333, test_case_t{false, 3163, 333});
            test_args[24].test_cases.emplace_back(333, test_case_t{false, 1327, 333});
            test_args[5].test_cases.emplace_back(336, test_case_t{true, 17965, 336});
            test_args[8].test_cases.emplace_back(336, test_case_t{false, 9074, 336});
            test_args[16].test_cases.emplace_back(336, test_case_t{false, 3493, 336});
            test_args[22].test_cases.emplace_back(336, test_case_t{false, 19853, 336});
            test_args[18].test_cases.emplace_back(339, test_case_t{false, 16218, 339});
            test_args[0].test_cases.emplace_back(339, test_case_t{false, 17357, 339});
            test_args[2].test_cases.emplace_back(341, test_case_t{false, 19464, 341});
            test_args[12].test_cases.emplace_back(343, test_case_t{false, 10812, 343});
            test_args[27].test_cases.emplace_back(346, test_case_t{false, 10960, 346});
            test_args[6].test_cases.emplace_back(347, test_case_t{false, 5406, 347});
            test_args[28].test_cases.emplace_back(347, test_case_t{true, 21964, 347});
            test_args[26].test_cases.emplace_back(349, test_case_t{true, 23660, 349});
            test_args[25].test_cases.emplace_back(350, test_case_t{false, 11973, 350});
            test_args[21].test_cases.emplace_back(352, test_case_t{true, 8524, 352});
            test_args[31].test_cases.emplace_back(352, test_case_t{false, 24733, 352});
            test_args[4].test_cases.emplace_back(353, test_case_t{true, 4537, 353});
            test_args[11].test_cases.emplace_back(354, test_case_t{false, 8749, 354});
            test_args[10].test_cases.emplace_back(355, test_case_t{false, 14982, 355});
            test_args[24].test_cases.emplace_back(355, test_case_t{false, 21624, 355});
            test_args[5].test_cases.emplace_back(358, test_case_t{true, 23875, 358});
            test_args[8].test_cases.emplace_back(358, test_case_t{true, 12321, 358});
            test_args[16].test_cases.emplace_back(358, test_case_t{false, 31276, 358});
            test_args[17].test_cases.emplace_back(358, test_case_t{false, 9856, 358});
            test_args[22].test_cases.emplace_back(359, test_case_t{false, 24955, 359});
            test_args[18].test_cases.emplace_back(361, test_case_t{true, 18801, 361});
            test_args[0].test_cases.emplace_back(361, test_case_t{false, 21992, 361});
            test_args[20].test_cases.emplace_back(362, test_case_t{true, 30803, 362});
            test_args[2].test_cases.emplace_back(363, test_case_t{true, 13860, 363});
            test_args[12].test_cases.emplace_back(366, test_case_t{false, 23457, 366});
            test_args[27].test_cases.emplace_back(368, test_case_t{true, 14242, 368});
            test_args[6].test_cases.emplace_back(369, test_case_t{true, 28112, 369});
            test_args[26].test_cases.emplace_back(371, test_case_t{true, 16346, 371});
            test_args[25].test_cases.emplace_back(372, test_case_t{true, 13928, 372});
            test_args[21].test_cases.emplace_back(374, test_case_t{true, 7436, 374});
            test_args[31].test_cases.emplace_back(374, test_case_t{false, 29021, 374});
            test_args[4].test_cases.emplace_back(375, test_case_t{true, 6160, 375});
            test_args[11].test_cases.emplace_back(376, test_case_t{true, 27080, 376});
            test_args[10].test_cases.emplace_back(377, test_case_t{false, 11343, 377});
            test_args[24].test_cases.emplace_back(377, test_case_t{true, 14145, 377});
            test_args[5].test_cases.emplace_back(380, test_case_t{true, 22055, 380});
            test_args[8].test_cases.emplace_back(380, test_case_t{false, 22674, 380});
            test_args[16].test_cases.emplace_back(380, test_case_t{true, 17417, 380});
            test_args[17].test_cases.emplace_back(380, test_case_t{false, 8654, 380});
            test_args[28].test_cases.emplace_back(380, test_case_t{false, 22288, 380});
            test_args[22].test_cases.emplace_back(381, test_case_t{false, 17499, 381});
            test_args[18].test_cases.emplace_back(383, test_case_t{false, 7306, 383});
            test_args[0].test_cases.emplace_back(383, test_case_t{false, 252, 383});
            test_args[20].test_cases.emplace_back(384, test_case_t{false, 7532, 384});
            test_args[2].test_cases.emplace_back(385, test_case_t{true, 5045, 385});
            test_args[0].test_cases.emplace_back(385, test_case_t{false, 12563, 385});
            test_args[0].test_cases.emplace_back(386, test_case_t{true, 2190, 386});
            test_args[27].test_cases.emplace_back(390, test_case_t{false, 624, 390});
            test_args[6].test_cases.emplace_back(391, test_case_t{false, 2435, 391});
            test_args[26].test_cases.emplace_back(393, test_case_t{false, 50, 393});
            test_args[25].test_cases.emplace_back(394, test_case_t{false, 25800, 394});
            test_args[21].test_cases.emplace_back(396, test_case_t{false, 7767, 396});
            test_args[31].test_cases.emplace_back(396, test_case_t{false, 625, 396});
            test_args[4].test_cases.emplace_back(397, test_case_t{true, 27721, 397});
            test_args[11].test_cases.emplace_back(398, test_case_t{true, 27748, 398});
            test_args[12].test_cases.emplace_back(398, test_case_t{false, 4871, 398});
            test_args[24].test_cases.emplace_back(399, test_case_t{true, 9742, 399});
            test_args[16].test_cases.emplace_back(402, test_case_t{false, 18149, 402});
            test_args[17].test_cases.emplace_back(402, test_case_t{false, 28746, 402});
            test_args[22].test_cases.emplace_back(403, test_case_t{false, 21393, 403});
            test_args[20].test_cases.emplace_back(406, test_case_t{true, 17683, 406});
            test_args[2].test_cases.emplace_back(407, test_case_t{false, 21899, 407});
            test_args[0].test_cases.emplace_back(408, test_case_t{false, 13680, 408});
            test_args[10].test_cases.emplace_back(409, test_case_t{false, 31786, 409});
            test_args[5].test_cases.emplace_back(412, test_case_t{false, 15893, 412});
            test_args[8].test_cases.emplace_back(412, test_case_t{true, 20180, 412});
            test_args[27].test_cases.emplace_back(412, test_case_t{true, 6892, 412});
            test_args[28].test_cases.emplace_back(412, test_case_t{true, 31761, 412});
            test_args[6].test_cases.emplace_back(413, test_case_t{false, 6805, 413});
            test_args[28].test_cases.emplace_back(414, test_case_t{false, 10356, 414});
            test_args[18].test_cases.emplace_back(415, test_case_t{true, 20417, 415});
            test_args[26].test_cases.emplace_back(415, test_case_t{false, 22546, 415});
            test_args[25].test_cases.emplace_back(416, test_case_t{false, 30296, 416});
            test_args[21].test_cases.emplace_back(418, test_case_t{true, 30847, 418});
            test_args[12].test_cases.emplace_back(420, test_case_t{true, 13611, 420});
            test_args[24].test_cases.emplace_back(421, test_case_t{true, 27223, 421});
            test_args[4].test_cases.emplace_back(422, test_case_t{false, 10090, 422});
            test_args[16].test_cases.emplace_back(424, test_case_t{false, 24642, 424});
            test_args[22].test_cases.emplace_back(425, test_case_t{true, 22728, 425});
            test_args[20].test_cases.emplace_back(428, test_case_t{false, 22385, 428});
            test_args[31].test_cases.emplace_back(428, test_case_t{false, 19636, 428});
            test_args[2].test_cases.emplace_back(429, test_case_t{true, 11037, 429});
            test_args[0].test_cases.emplace_back(430, test_case_t{false, 22504, 430});
            test_args[10].test_cases.emplace_back(431, test_case_t{true, 3766, 431});
            test_args[11].test_cases.emplace_back(431, test_case_t{true, 5758, 431});
            test_args[5].test_cases.emplace_back(434, test_case_t{true, 18267, 434});
            test_args[8].test_cases.emplace_back(434, test_case_t{true, 22061, 434});
            test_args[17].test_cases.emplace_back(434, test_case_t{false, 2899, 434});
            test_args[27].test_cases.emplace_back(434, test_case_t{true, 2572, 434});
            test_args[6].test_cases.emplace_back(435, test_case_t{true, 25625, 435});
            test_args[18].test_cases.emplace_back(437, test_case_t{false, 11339, 437});
            test_args[26].test_cases.emplace_back(437, test_case_t{false, 12418, 437});
            test_args[28].test_cases.emplace_back(437, test_case_t{true, 30206, 437});
            test_args[25].test_cases.emplace_back(438, test_case_t{false, 27981, 438});
            test_args[21].test_cases.emplace_back(441, test_case_t{false, 20205, 441});
            test_args[24].test_cases.emplace_back(443, test_case_t{false, 4195, 443});
            test_args[4].test_cases.emplace_back(444, test_case_t{false, 11030, 444});
            test_args[16].test_cases.emplace_back(446, test_case_t{false, 12579, 446});
            test_args[16].test_cases.emplace_back(447, test_case_t{true, 7592, 447});
            test_args[22].test_cases.emplace_back(447, test_case_t{false, 11516, 447});
            test_args[20].test_cases.emplace_back(450, test_case_t{false, 12073, 450});
            test_args[31].test_cases.emplace_back(450, test_case_t{false, 23506, 450});
            test_args[2].test_cases.emplace_back(451, test_case_t{true, 11459, 451});
            test_args[12].test_cases.emplace_back(452, test_case_t{false, 18482, 452});
            test_args[0].test_cases.emplace_back(452, test_case_t{false, 19299, 452});
            test_args[11].test_cases.emplace_back(453, test_case_t{false, 11555, 453});
            test_args[10].test_cases.emplace_back(455, test_case_t{false, 25225, 455});
            test_args[5].test_cases.emplace_back(456, test_case_t{false, 12612, 456});
            test_args[17].test_cases.emplace_back(456, test_case_t{false, 1606, 456});
            test_args[27].test_cases.emplace_back(456, test_case_t{true, 17112, 456});
            test_args[6].test_cases.emplace_back(457, test_case_t{false, 8813, 457});
            test_args[18].test_cases.emplace_back(459, test_case_t{true, 26440, 459});
            test_args[28].test_cases.emplace_back(459, test_case_t{true, 5095, 459});
            test_args[25].test_cases.emplace_back(460, test_case_t{true, 23283, 460});
            test_args[21].test_cases.emplace_back(463, test_case_t{false, 16950, 463});
            test_args[24].test_cases.emplace_back(465, test_case_t{false, 2485, 465});
            test_args[24].test_cases.emplace_back(466, test_case_t{false, 27773, 466});
            test_args[8].test_cases.emplace_back(467, test_case_t{true, 11383, 467});
            test_args[22].test_cases.emplace_back(469, test_case_t{false, 23111, 469});
            test_args[26].test_cases.emplace_back(469, test_case_t{false, 17903, 469});
            test_args[20].test_cases.emplace_back(472, test_case_t{true, 16292, 472});
            test_args[31].test_cases.emplace_back(472, test_case_t{false, 18779, 472});
            test_args[12].test_cases.emplace_back(474, test_case_t{false, 17627, 474});
            test_args[0].test_cases.emplace_back(474, test_case_t{false, 30489, 474});
            test_args[11].test_cases.emplace_back(475, test_case_t{true, 30260, 475});
            test_args[4].test_cases.emplace_back(476, test_case_t{true, 22075, 476});
            test_args[10].test_cases.emplace_back(478, test_case_t{false, 11192, 478});
            test_args[17].test_cases.emplace_back(478, test_case_t{true, 3125, 478});
            test_args[27].test_cases.emplace_back(479, test_case_t{true, 1553, 479});
            test_args[6].test_cases.emplace_back(480, test_case_t{true, 15135, 480});
            test_args[16].test_cases.emplace_back(480, test_case_t{true, 11354, 480});
            test_args[18].test_cases.emplace_back(481, test_case_t{true, 12637, 481});
            test_args[28].test_cases.emplace_back(481, test_case_t{false, 11678, 481});
            test_args[25].test_cases.emplace_back(482, test_case_t{false, 12173, 482});
            test_args[2].test_cases.emplace_back(483, test_case_t{true, 24099, 483});
            test_args[21].test_cases.emplace_back(485, test_case_t{false, 1208, 485});
            test_args[24].test_cases.emplace_back(488, test_case_t{false, 647, 488});
            test_args[8].test_cases.emplace_back(489, test_case_t{true, 13070, 489});
            test_args[22].test_cases.emplace_back(491, test_case_t{false, 27752, 491});
            test_args[20].test_cases.emplace_back(494, test_case_t{true, 11617, 494});
            test_args[31].test_cases.emplace_back(494, test_case_t{true, 6785, 494});
            test_args[12].test_cases.emplace_back(496, test_case_t{false, 30270, 496});
            test_args[0].test_cases.emplace_back(496, test_case_t{false, 27727, 496});
            test_args[4].test_cases.emplace_back(498, test_case_t{false, 22919, 498});
            test_args[11].test_cases.emplace_back(499, test_case_t{true, 17858, 499});
            test_args[10].test_cases.emplace_back(500, test_case_t{false, 22420, 500});
            test_args[17].test_cases.emplace_back(500, test_case_t{false, 10115, 500});
            test_args[27].test_cases.emplace_back(501, test_case_t{false, 23633, 501});
            test_args[6].test_cases.emplace_back(502, test_case_t{true, 161, 502});
            test_args[16].test_cases.emplace_back(502, test_case_t{false, 22766, 502});
            test_args[18].test_cases.emplace_back(503, test_case_t{false, 485, 503});
            test_args[28].test_cases.emplace_back(503, test_case_t{false, 23456, 503});
            test_args[25].test_cases.emplace_back(504, test_case_t{false, 22714, 504});
            test_args[2].test_cases.emplace_back(505, test_case_t{false, 25544, 505});
            test_args[21].test_cases.emplace_back(507, test_case_t{true, 22022, 507});
            test_args[24].test_cases.emplace_back(510, test_case_t{true, 1380, 510});
            test_args[8].test_cases.emplace_back(512, test_case_t{true, 30861, 512});
            test_args[20].test_cases.emplace_back(516, test_case_t{true, 26061, 516});
            test_args[31].test_cases.emplace_back(516, test_case_t{false, 1845, 516});
            test_args[4].test_cases.emplace_back(520, test_case_t{false, 15430, 520});
            test_args[11].test_cases.emplace_back(521, test_case_t{true, 25802, 521});
            test_args[10].test_cases.emplace_back(522, test_case_t{false, 24530, 522});
            test_args[17].test_cases.emplace_back(522, test_case_t{true, 5919, 522});
            test_args[22].test_cases.emplace_back(523, test_case_t{true, 2949, 523});
            test_args[27].test_cases.emplace_back(523, test_case_t{false, 14045, 523});
            test_args[6].test_cases.emplace_back(524, test_case_t{true, 345, 524});
            test_args[16].test_cases.emplace_back(524, test_case_t{true, 26141, 524});
            test_args[18].test_cases.emplace_back(525, test_case_t{true, 1035, 525});
            test_args[28].test_cases.emplace_back(525, test_case_t{false, 29362, 525});
            test_args[25].test_cases.emplace_back(526, test_case_t{true, 8000, 526});
            test_args[2].test_cases.emplace_back(527, test_case_t{false, 19947, 527});
            test_args[12].test_cases.emplace_back(528, test_case_t{true, 323, 528});
            test_args[0].test_cases.emplace_back(528, test_case_t{true, 17266, 528});
            test_args[21].test_cases.emplace_back(529, test_case_t{false, 7283, 529});
            test_args[24].test_cases.emplace_back(532, test_case_t{true, 6443, 532});
            test_args[20].test_cases.emplace_back(538, test_case_t{true, 2860, 538});
            test_args[31].test_cases.emplace_back(538, test_case_t{false, 12662, 538});
            test_args[4].test_cases.emplace_back(542, test_case_t{true, 18319, 542});
            test_args[8].test_cases.emplace_back(544, test_case_t{true, 3870, 544});
            test_args[10].test_cases.emplace_back(544, test_case_t{true, 22193, 544});
            test_args[17].test_cases.emplace_back(544, test_case_t{true, 11900, 544});
            test_args[22].test_cases.emplace_back(545, test_case_t{true, 18837, 545});
            test_args[27].test_cases.emplace_back(545, test_case_t{false, 776, 545});
            test_args[6].test_cases.emplace_back(546, test_case_t{false, 1610, 546});
            test_args[16].test_cases.emplace_back(546, test_case_t{true, 28955, 546});
            test_args[18].test_cases.emplace_back(547, test_case_t{true, 4832, 547});
            test_args[28].test_cases.emplace_back(547, test_case_t{true, 9711, 547});
            test_args[2].test_cases.emplace_back(549, test_case_t{true, 30256, 549});
            test_args[18].test_cases.emplace_back(549, test_case_t{false, 20286, 549});
            test_args[25].test_cases.emplace_back(549, test_case_t{false, 19960, 549});
            test_args[21].test_cases.emplace_back(551, test_case_t{true, 22449, 551});
            test_args[11].test_cases.emplace_back(553, test_case_t{true, 11403, 553});
            test_args[24].test_cases.emplace_back(555, test_case_t{false, 27048, 555});
            test_args[12].test_cases.emplace_back(560, test_case_t{true, 690, 560});
            test_args[20].test_cases.emplace_back(560, test_case_t{false, 7647, 560});
            test_args[31].test_cases.emplace_back(560, test_case_t{false, 28143, 560});
            test_args[0].test_cases.emplace_back(560, test_case_t{false, 3013, 560});
            test_args[4].test_cases.emplace_back(564, test_case_t{true, 7125, 564});
            test_args[8].test_cases.emplace_back(566, test_case_t{true, 14251, 566});
            test_args[10].test_cases.emplace_back(566, test_case_t{false, 29415, 566});
            test_args[17].test_cases.emplace_back(566, test_case_t{false, 31871, 566});
            test_args[22].test_cases.emplace_back(567, test_case_t{true, 22807, 567});
            test_args[27].test_cases.emplace_back(567, test_case_t{false, 7138, 567});
            test_args[6].test_cases.emplace_back(568, test_case_t{false, 6762, 568});
            test_args[16].test_cases.emplace_back(569, test_case_t{true, 7741, 569});
            test_args[27].test_cases.emplace_back(569, test_case_t{true, 15239, 569});
            test_args[28].test_cases.emplace_back(569, test_case_t{true, 29932, 569});
            test_args[2].test_cases.emplace_back(571, test_case_t{true, 17648, 571});
            test_args[18].test_cases.emplace_back(571, test_case_t{true, 517, 571});
            test_args[25].test_cases.emplace_back(571, test_case_t{false, 17751, 571});
            test_args[27].test_cases.emplace_back(571, test_case_t{true, 8872, 571});
            test_args[21].test_cases.emplace_back(573, test_case_t{false, 12834, 573});
            test_args[11].test_cases.emplace_back(575, test_case_t{true, 2567, 575});
            test_args[24].test_cases.emplace_back(577, test_case_t{true, 11612, 577});
            test_args[12].test_cases.emplace_back(582, test_case_t{false, 3221, 582});
            test_args[31].test_cases.emplace_back(582, test_case_t{false, 23629, 582});
            test_args[0].test_cases.emplace_back(582, test_case_t{false, 21427, 582});
            test_args[12].test_cases.emplace_back(584, test_case_t{false, 13524, 584});
            test_args[4].test_cases.emplace_back(586, test_case_t{true, 27744, 586});
            test_args[17].test_cases.emplace_back(588, test_case_t{false, 24620, 588});
            test_args[22].test_cases.emplace_back(589, test_case_t{false, 5135, 589});
            test_args[6].test_cases.emplace_back(590, test_case_t{true, 11095, 590});
            test_args[16].test_cases.emplace_back(591, test_case_t{false, 28503, 591});
            test_args[28].test_cases.emplace_back(591, test_case_t{false, 17112, 591});
            test_args[2].test_cases.emplace_back(593, test_case_t{false, 27502, 593});
            test_args[18].test_cases.emplace_back(593, test_case_t{false, 15681, 593});
            test_args[20].test_cases.emplace_back(593, test_case_t{false, 12640, 593});
            test_args[25].test_cases.emplace_back(593, test_case_t{false, 23992, 593});
            test_args[27].test_cases.emplace_back(594, test_case_t{false, 27214, 594});
            test_args[21].test_cases.emplace_back(595, test_case_t{false, 22775, 595});
            test_args[8].test_cases.emplace_back(598, test_case_t{false, 22720, 598});
            test_args[10].test_cases.emplace_back(599, test_case_t{false, 1430, 599});
            test_args[24].test_cases.emplace_back(599, test_case_t{true, 9986, 599});
            test_args[31].test_cases.emplace_back(604, test_case_t{false, 13784, 604});
            test_args[0].test_cases.emplace_back(604, test_case_t{false, 13631, 604});
            test_args[11].test_cases.emplace_back(607, test_case_t{true, 31528, 607});
            test_args[4].test_cases.emplace_back(608, test_case_t{false, 2528, 608});
            test_args[22].test_cases.emplace_back(611, test_case_t{true, 30288, 611});
            test_args[6].test_cases.emplace_back(612, test_case_t{false, 27072, 612});
            test_args[16].test_cases.emplace_back(613, test_case_t{true, 12671, 613});
            test_args[2].test_cases.emplace_back(615, test_case_t{true, 2568, 615});
            test_args[18].test_cases.emplace_back(615, test_case_t{true, 10159, 615});
            test_args[20].test_cases.emplace_back(615, test_case_t{true, 12877, 615});
            test_args[12].test_cases.emplace_back(616, test_case_t{false, 22190, 616});
            test_args[25].test_cases.emplace_back(616, test_case_t{false, 32480, 616});
            test_args[27].test_cases.emplace_back(616, test_case_t{false, 18288, 616});
            test_args[21].test_cases.emplace_back(617, test_case_t{true, 21464, 617});
            test_args[10].test_cases.emplace_back(621, test_case_t{false, 20207, 621});
            test_args[24].test_cases.emplace_back(621, test_case_t{false, 2623, 621});
            test_args[28].test_cases.emplace_back(623, test_case_t{false, 30367, 623});
            test_args[31].test_cases.emplace_back(626, test_case_t{true, 29476, 626});
            test_args[0].test_cases.emplace_back(628, test_case_t{false, 22976, 628});
            test_args[11].test_cases.emplace_back(629, test_case_t{true, 3805, 629});
            test_args[8].test_cases.emplace_back(630, test_case_t{true, 5056, 630});
            test_args[22].test_cases.emplace_back(633, test_case_t{false, 7611, 633});
            test_args[18].test_cases.emplace_back(637, test_case_t{true, 27760, 637});
            test_args[20].test_cases.emplace_back(638, test_case_t{true, 25683, 638});
            test_args[25].test_cases.emplace_back(638, test_case_t{false, 15720, 638});
            test_args[27].test_cases.emplace_back(638, test_case_t{true, 10480, 638});
            test_args[21].test_cases.emplace_back(639, test_case_t{true, 10244, 639});
            test_args[4].test_cases.emplace_back(640, test_case_t{false, 22236, 640});
            test_args[24].test_cases.emplace_back(643, test_case_t{false, 15168, 643});
            test_args[6].test_cases.emplace_back(644, test_case_t{false, 25232, 644});
            test_args[16].test_cases.emplace_back(645, test_case_t{false, 10112, 645});
            test_args[28].test_cases.emplace_back(645, test_case_t{false, 17696, 645});
            test_args[2].test_cases.emplace_back(647, test_case_t{false, 10485, 647});
            test_args[31].test_cases.emplace_back(648, test_case_t{true, 19096, 648});
            test_args[12].test_cases.emplace_back(650, test_case_t{false, 21377, 650});
            test_args[0].test_cases.emplace_back(650, test_case_t{false, 29829, 650});
            test_args[11].test_cases.emplace_back(651, test_case_t{true, 30510, 651});
            test_args[10].test_cases.emplace_back(653, test_case_t{true, 22704, 653});
            test_args[22].test_cases.emplace_back(656, test_case_t{true, 28252, 656});
            test_args[20].test_cases.emplace_back(660, test_case_t{true, 6549, 660});
            test_args[27].test_cases.emplace_back(660, test_case_t{true, 10533, 660});
            test_args[21].test_cases.emplace_back(661, test_case_t{false, 10583, 661});
            test_args[25].test_cases.emplace_back(661, test_case_t{true, 32763, 661});
            test_args[4].test_cases.emplace_back(662, test_case_t{true, 5136, 662});
            test_args[8].test_cases.emplace_back(662, test_case_t{true, 11704, 662});
            test_args[24].test_cases.emplace_back(665, test_case_t{false, 2345, 665});
            test_args[6].test_cases.emplace_back(666, test_case_t{true, 20176, 666});
            test_args[28].test_cases.emplace_back(667, test_case_t{true, 24581, 667});
            test_args[18].test_cases.emplace_back(669, test_case_t{true, 18143, 669});
            test_args[31].test_cases.emplace_back(670, test_case_t{true, 14264, 670});
            test_args[12].test_cases.emplace_back(672, test_case_t{true, 17695, 672});
            test_args[0].test_cases.emplace_back(672, test_case_t{false, 24976, 672});
            test_args[11].test_cases.emplace_back(673, test_case_t{true, 24901, 673});
            test_args[16].test_cases.emplace_back(677, test_case_t{false, 23409, 677});
            test_args[22].test_cases.emplace_back(678, test_case_t{true, 17034, 678});
            test_args[2].test_cases.emplace_back(679, test_case_t{true, 780, 679});
            test_args[27].test_cases.emplace_back(682, test_case_t{false, 25776, 682});
            test_args[21].test_cases.emplace_back(683, test_case_t{true, 11792, 683});
            test_args[25].test_cases.emplace_back(683, test_case_t{false, 9753, 683});
            test_args[4].test_cases.emplace_back(684, test_case_t{false, 20970, 684});
            test_args[8].test_cases.emplace_back(684, test_case_t{true, 10273, 684});
            test_args[8].test_cases.emplace_back(686, test_case_t{false, 9173, 686});
            test_args[10].test_cases.emplace_back(686, test_case_t{false, 6438, 686});
            test_args[24].test_cases.emplace_back(687, test_case_t{true, 30820, 687});
            test_args[28].test_cases.emplace_back(689, test_case_t{true, 3188, 689});
            test_args[18].test_cases.emplace_back(691, test_case_t{true, 23115, 691});
            test_args[31].test_cases.emplace_back(692, test_case_t{true, 10215, 692});
            test_args[20].test_cases.emplace_back(693, test_case_t{false, 7802, 693});
            test_args[0].test_cases.emplace_back(694, test_case_t{false, 8600, 694});
            test_args[11].test_cases.emplace_back(695, test_case_t{true, 4291, 695});
            test_args[6].test_cases.emplace_back(698, test_case_t{true, 16970, 698});
            test_args[16].test_cases.emplace_back(699, test_case_t{true, 20546, 699});
            test_args[22].test_cases.emplace_back(700, test_case_t{true, 8583, 700});
            test_args[16].test_cases.emplace_back(701, test_case_t{true, 18346, 701});
            test_args[12].test_cases.emplace_back(704, test_case_t{false, 7584, 704});
            test_args[27].test_cases.emplace_back(704, test_case_t{false, 26000, 704});
            test_args[25].test_cases.emplace_back(705, test_case_t{true, 19012, 705});
            test_args[4].test_cases.emplace_back(706, test_case_t{true, 1560, 706});
            test_args[8].test_cases.emplace_back(710, test_case_t{true, 3121, 710});
            test_args[24].test_cases.emplace_back(710, test_case_t{false, 27520, 710});
            test_args[2].test_cases.emplace_back(711, test_case_t{false, 6763, 711});
            test_args[28].test_cases.emplace_back(711, test_case_t{false, 15722, 711});
            test_args[31].test_cases.emplace_back(714, test_case_t{false, 11400, 714});
            test_args[21].test_cases.emplace_back(715, test_case_t{true, 8192, 715});
            test_args[0].test_cases.emplace_back(716, test_case_t{true, 1555, 716});
            test_args[11].test_cases.emplace_back(717, test_case_t{true, 4433, 717});
            test_args[10].test_cases.emplace_back(718, test_case_t{true, 12841, 718});
            test_args[6].test_cases.emplace_back(720, test_case_t{true, 7705, 720});
            test_args[22].test_cases.emplace_back(722, test_case_t{false, 8866, 722});
            test_args[16].test_cases.emplace_back(723, test_case_t{true, 6242, 723});
            test_args[18].test_cases.emplace_back(723, test_case_t{true, 28832, 723});
            test_args[27].test_cases.emplace_back(726, test_case_t{true, 28256, 726});
            test_args[25].test_cases.emplace_back(727, test_case_t{true, 18006, 727});
            test_args[24].test_cases.emplace_back(732, test_case_t{true, 9363, 732});
            test_args[12].test_cases.emplace_back(736, test_case_t{true, 1172, 736});
            test_args[21].test_cases.emplace_back(737, test_case_t{false, 5484, 737});
            test_args[4].test_cases.emplace_back(738, test_case_t{false, 13527, 738});
            test_args[11].test_cases.emplace_back(739, test_case_t{false, 27584, 739});
            test_args[21].test_cases.emplace_back(739, test_case_t{false, 2018, 739});
            test_args[11].test_cases.emplace_back(741, test_case_t{true, 28503, 741});
            test_args[6].test_cases.emplace_back(742, test_case_t{true, 31456, 742});
            test_args[8].test_cases.emplace_back(742, test_case_t{false, 27055, 742});
            test_args[2].test_cases.emplace_back(743, test_case_t{false, 7994, 743});
            test_args[28].test_cases.emplace_back(743, test_case_t{false, 10923, 743});
            test_args[16].test_cases.emplace_back(745, test_case_t{true, 21343, 745});
            test_args[18].test_cases.emplace_back(745, test_case_t{true, 7022, 745});
            test_args[31].test_cases.emplace_back(746, test_case_t{false, 16682, 746});
            test_args[10].test_cases.emplace_back(750, test_case_t{false, 19658, 750});
            test_args[25].test_cases.emplace_back(750, test_case_t{false, 20095, 750});
            test_args[27].test_cases.emplace_back(750, test_case_t{false, 26720, 750});
            test_args[22].test_cases.emplace_back(754, test_case_t{false, 22399, 754});
            test_args[24].test_cases.emplace_back(754, test_case_t{true, 15630, 754});
            test_args[12].test_cases.emplace_back(758, test_case_t{false, 15410, 758});
            test_args[4].test_cases.emplace_back(760, test_case_t{false, 15988, 760});
            test_args[6].test_cases.emplace_back(764, test_case_t{false, 2340, 764});
            test_args[2].test_cases.emplace_back(765, test_case_t{true, 8161, 765});
            test_args[28].test_cases.emplace_back(765, test_case_t{true, 29158, 765});
            test_args[16].test_cases.emplace_back(767, test_case_t{true, 31185, 767});
            test_args[18].test_cases.emplace_back(767, test_case_t{false, 28107, 767});
            test_args[31].test_cases.emplace_back(768, test_case_t{false, 23425, 768});
            test_args[10].test_cases.emplace_back(772, test_case_t{false, 3901, 772});
            test_args[25].test_cases.emplace_back(772, test_case_t{true, 28381, 772});
            test_args[27].test_cases.emplace_back(772, test_case_t{true, 24317, 772});
            test_args[11].test_cases.emplace_back(773, test_case_t{true, 7245, 773});
            test_args[8].test_cases.emplace_back(774, test_case_t{true, 31976, 774});
            test_args[24].test_cases.emplace_back(776, test_case_t{false, 30393, 776});
            test_args[24].test_cases.emplace_back(777, test_case_t{true, 32398, 777});
            test_args[0].test_cases.emplace_back(779, test_case_t{true, 24120, 779});
            test_args[12].test_cases.emplace_back(780, test_case_t{true, 30144, 780});
            test_args[4].test_cases.emplace_back(782, test_case_t{false, 16322, 782});
            test_args[22].test_cases.emplace_back(786, test_case_t{false, 24237, 786});
            test_args[28].test_cases.emplace_back(787, test_case_t{false, 13613, 787});
            test_args[16].test_cases.emplace_back(789, test_case_t{false, 32522, 789});
            test_args[18].test_cases.emplace_back(789, test_case_t{true, 6411, 789});
            test_args[31].test_cases.emplace_back(790, test_case_t{true, 31451, 790});
            test_args[25].test_cases.emplace_back(794, test_case_t{true, 670, 794});
            test_args[27].test_cases.emplace_back(794, test_case_t{false, 20422, 794});
            test_args[11].test_cases.emplace_back(795, test_case_t{true, 31752, 795});
            test_args[6].test_cases.emplace_back(796, test_case_t{true, 20291, 796});
            test_args[8].test_cases.emplace_back(796, test_case_t{false, 32645, 796});
            test_args[2].test_cases.emplace_back(797, test_case_t{true, 31106, 797});
            test_args[0].test_cases.emplace_back(801, test_case_t{true, 10755, 801});
            test_args[12].test_cases.emplace_back(802, test_case_t{true, 4681, 802});
            test_args[4].test_cases.emplace_back(804, test_case_t{false, 29445, 804});
            test_args[10].test_cases.emplace_back(805, test_case_t{true, 1051, 805});
            test_args[22].test_cases.emplace_back(808, test_case_t{false, 14490, 808});
            test_args[24].test_cases.emplace_back(809, test_case_t{true, 12828, 809});
            test_args[16].test_cases.emplace_back(811, test_case_t{false, 19475, 811});
            test_args[31].test_cases.emplace_back(812, test_case_t{true, 12094, 812});
            test_args[25].test_cases.emplace_back(816, test_case_t{false, 1918, 816});
            test_args[11].test_cases.emplace_back(817, test_case_t{false, 3465, 817});
            test_args[8].test_cases.emplace_back(818, test_case_t{false, 26121, 818});
            test_args[28].test_cases.emplace_back(819, test_case_t{true, 15952, 819});
            test_args[2].test_cases.emplace_back(820, test_case_t{false, 23646, 820});
            test_args[18].test_cases.emplace_back(821, test_case_t{true, 7914, 821});
            test_args[0].test_cases.emplace_back(823, test_case_t{false, 20730, 823});
            test_args[12].test_cases.emplace_back(824, test_case_t{false, 7815, 824});
            test_args[4].test_cases.emplace_back(826, test_case_t{true, 14525, 826});
            test_args[10].test_cases.emplace_back(827, test_case_t{false, 7202, 827});
            test_args[6].test_cases.emplace_back(828, test_case_t{true, 23982, 828});
            test_args[6].test_cases.emplace_back(829, test_case_t{true, 24483, 829});
            test_args[22].test_cases.emplace_back(830, test_case_t{false, 30737, 830});
            test_args[24].test_cases.emplace_back(832, test_case_t{false, 21615, 832});
            test_args[16].test_cases.emplace_back(833, test_case_t{true, 25333, 833});
            test_args[31].test_cases.emplace_back(834, test_case_t{true, 6535, 834});
            test_args[25].test_cases.emplace_back(838, test_case_t{true, 5231, 838});
            test_args[11].test_cases.emplace_back(839, test_case_t{false, 19341, 839});
            test_args[8].test_cases.emplace_back(840, test_case_t{true, 29050, 840});
            test_args[11].test_cases.emplace_back(841, test_case_t{false, 6722, 841});
            test_args[28].test_cases.emplace_back(841, test_case_t{true, 9504, 841});
            test_args[18].test_cases.emplace_back(843, test_case_t{false, 17813, 843});
            test_args[0].test_cases.emplace_back(845, test_case_t{false, 24786, 845});
            test_args[12].test_cases.emplace_back(847, test_case_t{false, 15196, 847});
            test_args[0].test_cases.emplace_back(847, test_case_t{true, 32474, 847});
            test_args[4].test_cases.emplace_back(848, test_case_t{false, 4239, 848});
            test_args[12].test_cases.emplace_back(848, test_case_t{true, 16199, 848});
            test_args[10].test_cases.emplace_back(849, test_case_t{true, 8038, 849});
            test_args[6].test_cases.emplace_back(851, test_case_t{true, 27783, 851});
            test_args[2].test_cases.emplace_back(852, test_case_t{true, 18503, 852});
            test_args[22].test_cases.emplace_back(852, test_case_t{true, 6931, 852});
            test_args[24].test_cases.emplace_back(854, test_case_t{true, 25435, 854});
            test_args[31].test_cases.emplace_back(856, test_case_t{false, 9220, 856});
            test_args[25].test_cases.emplace_back(860, test_case_t{true, 3362, 860});
            test_args[11].test_cases.emplace_back(863, test_case_t{true, 462, 863});
            test_args[28].test_cases.emplace_back(863, test_case_t{false, 3372, 863});
            test_args[18].test_cases.emplace_back(865, test_case_t{false, 16211, 865});
            test_args[16].test_cases.emplace_back(866, test_case_t{true, 16956, 866});
            test_args[18].test_cases.emplace_back(866, test_case_t{false, 2692, 866});
            test_args[0].test_cases.emplace_back(869, test_case_t{true, 11971, 869});
            test_args[4].test_cases.emplace_back(870, test_case_t{true, 10012, 870});
            test_args[12].test_cases.emplace_back(870, test_case_t{false, 22798, 870});
            test_args[10].test_cases.emplace_back(871, test_case_t{false, 24460, 871});
            test_args[8].test_cases.emplace_back(872, test_case_t{false, 8478, 872});
            test_args[6].test_cases.emplace_back(873, test_case_t{false, 5403, 873});
            test_args[2].test_cases.emplace_back(874, test_case_t{true, 21390, 874});
            test_args[22].test_cases.emplace_back(874, test_case_t{true, 5914, 874});
            test_args[24].test_cases.emplace_back(876, test_case_t{true, 27304, 876});
            test_args[31].test_cases.emplace_back(878, test_case_t{true, 11810, 878});
            test_args[25].test_cases.emplace_back(882, test_case_t{true, 24882, 882});
            test_args[11].test_cases.emplace_back(885, test_case_t{true, 6136, 885});
            test_args[4].test_cases.emplace_back(892, test_case_t{false, 8402, 892});
            test_args[10].test_cases.emplace_back(893, test_case_t{true, 19929, 893});
            test_args[12].test_cases.emplace_back(893, test_case_t{true, 10807, 893});
            test_args[8].test_cases.emplace_back(894, test_case_t{false, 20024, 894});
            test_args[12].test_cases.emplace_back(894, test_case_t{false, 12717, 894});
            test_args[6].test_cases.emplace_back(895, test_case_t{true, 22743, 895});
            test_args[28].test_cases.emplace_back(895, test_case_t{true, 29674, 895});
            test_args[16].test_cases.emplace_back(898, test_case_t{false, 7280, 898});
            test_args[18].test_cases.emplace_back(898, test_case_t{true, 28670, 898});
            test_args[24].test_cases.emplace_back(898, test_case_t{true, 17646, 898});
            test_args[0].test_cases.emplace_back(901, test_case_t{true, 8095, 901});
            test_args[25].test_cases.emplace_back(904, test_case_t{false, 10966, 904});
            test_args[2].test_cases.emplace_back(906, test_case_t{true, 4201, 906});
            test_args[22].test_cases.emplace_back(906, test_case_t{false, 13445, 906});
            test_args[11].test_cases.emplace_back(907, test_case_t{true, 5710, 907});
            test_args[31].test_cases.emplace_back(910, test_case_t{true, 23396, 910});
            test_args[4].test_cases.emplace_back(914, test_case_t{false, 21020, 914});
            test_args[10].test_cases.emplace_back(915, test_case_t{true, 26982, 915});
            test_args[8].test_cases.emplace_back(916, test_case_t{true, 16804, 916});
            test_args[28].test_cases.emplace_back(918, test_case_t{false, 4548, 918});
            test_args[18].test_cases.emplace_back(920, test_case_t{false, 5042, 920});
            test_args[24].test_cases.emplace_back(920, test_case_t{true, 27819, 920});
            test_args[0].test_cases.emplace_back(923, test_case_t{false, 32196, 923});
            test_args[6].test_cases.emplace_back(927, test_case_t{false, 31402, 927});
            test_args[12].test_cases.emplace_back(928, test_case_t{true, 30036, 928});
            test_args[22].test_cases.emplace_back(928, test_case_t{false, 924, 928});
            test_args[11].test_cases.emplace_back(929, test_case_t{false, 2638, 929});
            test_args[16].test_cases.emplace_back(930, test_case_t{false, 841, 930});
            test_args[31].test_cases.emplace_back(932, test_case_t{true, 6074, 932});
            test_args[4].test_cases.emplace_back(936, test_case_t{true, 20105, 936});
            test_args[25].test_cases.emplace_back(936, test_case_t{false, 24894, 936});
            test_args[10].test_cases.emplace_back(937, test_case_t{false, 8646, 937});
            test_args[25].test_cases.emplace_back(937, test_case_t{false, 20892, 937});
            test_args[8].test_cases.emplace_back(938, test_case_t{true, 9273, 938});
            test_args[28].test_cases.emplace_back(940, test_case_t{false, 26048, 940});
            test_args[24].test_cases.emplace_back(942, test_case_t{false, 22324, 942});
            test_args[0].test_cases.emplace_back(945, test_case_t{true, 23680, 945});
            test_args[6].test_cases.emplace_back(949, test_case_t{false, 12603, 949});
            test_args[12].test_cases.emplace_back(950, test_case_t{false, 25207, 950});
            test_args[22].test_cases.emplace_back(950, test_case_t{false, 12272, 950});
            test_args[11].test_cases.emplace_back(951, test_case_t{true, 16143, 951});
            test_args[18].test_cases.emplace_back(952, test_case_t{true, 12672, 952});
            test_args[16].test_cases.emplace_back(953, test_case_t{false, 18546, 953});
            test_args[4].test_cases.emplace_back(958, test_case_t{false, 28887, 958});
            test_args[25].test_cases.emplace_back(959, test_case_t{true, 21794, 959});
            test_args[2].test_cases.emplace_back(960, test_case_t{false, 26894, 960});
            test_args[8].test_cases.emplace_back(960, test_case_t{true, 7441, 960});
            test_args[24].test_cases.emplace_back(964, test_case_t{false, 9480, 964});
            test_args[31].test_cases.emplace_back(964, test_case_t{true, 24661, 964});
            test_args[0].test_cases.emplace_back(967, test_case_t{false, 24686, 967});
            test_args[10].test_cases.emplace_back(969, test_case_t{false, 21006, 969});
            test_args[0].test_cases.emplace_back(969, test_case_t{true, 21349, 969});
            test_args[6].test_cases.emplace_back(971, test_case_t{false, 15147, 971});
            test_args[12].test_cases.emplace_back(972, test_case_t{false, 30294, 972});
            test_args[22].test_cases.emplace_back(972, test_case_t{false, 11421, 972});
            test_args[28].test_cases.emplace_back(972, test_case_t{true, 16071, 972});
            test_args[11].test_cases.emplace_back(973, test_case_t{false, 28480, 973});
            test_args[18].test_cases.emplace_back(974, test_case_t{false, 24935, 974});
            test_args[16].test_cases.emplace_back(975, test_case_t{false, 14883, 975});
            test_args[4].test_cases.emplace_back(981, test_case_t{false, 9896, 981});
            test_args[25].test_cases.emplace_back(981, test_case_t{true, 11107, 981});
            test_args[8].test_cases.emplace_back(982, test_case_t{false, 25005, 982});
            test_args[2].test_cases.emplace_back(983, test_case_t{false, 10052, 983});
            test_args[24].test_cases.emplace_back(986, test_case_t{true, 26610, 986});
            test_args[31].test_cases.emplace_back(986, test_case_t{true, 3865, 986});
            test_args[10].test_cases.emplace_back(991, test_case_t{false, 3399, 991});
            test_args[0].test_cases.emplace_back(991, test_case_t{true, 2381, 991});
            test_args[6].test_cases.emplace_back(993, test_case_t{false, 30157, 993});
            test_args[22].test_cases.emplace_back(994, test_case_t{false, 5277, 994});
            test_args[28].test_cases.emplace_back(994, test_case_t{false, 9661, 994});
            test_args[11].test_cases.emplace_back(995, test_case_t{false, 21858, 995});
            test_args[12].test_cases.emplace_back(995, test_case_t{true, 27546, 995});
            test_args[18].test_cases.emplace_back(996, test_case_t{true, 15302, 996});
            test_args[16].test_cases.emplace_back(997, test_case_t{true, 17243, 997});
            test_args[25].test_cases.emplace_back(1003, test_case_t{true, 28824, 1003});
            test_args[4].test_cases.emplace_back(1004, test_case_t{true, 29701, 1004});
            test_args[8].test_cases.emplace_back(1004, test_case_t{true, 19792, 1004});
            test_args[2].test_cases.emplace_back(1005, test_case_t{false, 30827, 1005});
            test_args[24].test_cases.emplace_back(1008, test_case_t{true, 14368, 1008});
            test_args[24].test_cases.emplace_back(1010, test_case_t{false, 26391, 1010});
            test_args[10].test_cases.emplace_back(1014, test_case_t{true, 17494, 1014});
            test_args[0].test_cases.emplace_back(1014, test_case_t{true, 20697, 1014});
            test_args[22].test_cases.emplace_back(1016, test_case_t{true, 32286, 1016});
            test_args[28].test_cases.emplace_back(1016, test_case_t{true, 5599, 1016});
            test_args[11].test_cases.emplace_back(1017, test_case_t{true, 32619, 1017});
            test_args[12].test_cases.emplace_back(1017, test_case_t{true, 21124, 1017});
            test_args[18].test_cases.emplace_back(1018, test_case_t{false, 28149, 1018});
            test_args[31].test_cases.emplace_back(1018, test_case_t{false, 15966, 1018});
            test_args[16].test_cases.emplace_back(1019, test_case_t{true, 6817, 1019});
            test_args[6].test_cases.emplace_back(1025, test_case_t{false, 26946, 1025});
            test_args[25].test_cases.emplace_back(1025, test_case_t{false, 5618, 1025});
            test_args[4].test_cases.emplace_back(1026, test_case_t{false, 4398, 1026});
            test_args[2].test_cases.emplace_back(1027, test_case_t{false, 21332, 1027});
            test_args[24].test_cases.emplace_back(1032, test_case_t{false, 11942, 1032});
            test_args[8].test_cases.emplace_back(1036, test_case_t{true, 26635, 1036});
            test_args[0].test_cases.emplace_back(1036, test_case_t{false, 28990, 1036});
            test_args[8].test_cases.emplace_back(1038, test_case_t{false, 8797, 1038});
            test_args[28].test_cases.emplace_back(1038, test_case_t{true, 3738, 1038});
            test_args[11].test_cases.emplace_back(1039, test_case_t{false, 15722, 1039});
            test_args[12].test_cases.emplace_back(1039, test_case_t{true, 29689, 1039});
            test_args[22].test_cases.emplace_back(1039, test_case_t{true, 24192, 1039});
            test_args[16].test_cases.emplace_back(1041, test_case_t{true, 20502, 1041});
            test_args[16].test_cases.emplace_back(1043, test_case_t{false, 17594, 1043});
            test_args[6].test_cases.emplace_back(1047, test_case_t{false, 31228, 1047});
            test_args[10].test_cases.emplace_back(1047, test_case_t{false, 23065, 1047});
            test_args[4].test_cases.emplace_back(1049, test_case_t{false, 1990, 1049});
            test_args[18].test_cases.emplace_back(1050, test_case_t{true, 2584, 1050});
            test_args[31].test_cases.emplace_back(1050, test_case_t{true, 7261, 1050});
            test_args[24].test_cases.emplace_back(1054, test_case_t{false, 14569, 1054});
            test_args[24].test_cases.emplace_back(1056, test_case_t{false, 19409, 1056});
            test_args[25].test_cases.emplace_back(1057, test_case_t{true, 29776, 1057});
            test_args[2].test_cases.emplace_back(1059, test_case_t{true, 14850, 1059});
            test_args[8].test_cases.emplace_back(1060, test_case_t{true, 3980, 1060});
            test_args[11].test_cases.emplace_back(1061, test_case_t{false, 10413, 1061});
            test_args[12].test_cases.emplace_back(1061, test_case_t{false, 23568, 1061});
            test_args[22].test_cases.emplace_back(1062, test_case_t{true, 10947, 1062});
            test_args[28].test_cases.emplace_back(1062, test_case_t{false, 11302, 1062});
            test_args[16].test_cases.emplace_back(1065, test_case_t{true, 7961, 1065});
            test_args[0].test_cases.emplace_back(1068, test_case_t{true, 8936, 1068});
            test_args[10].test_cases.emplace_back(1069, test_case_t{true, 8356, 1069});
            test_args[6].test_cases.emplace_back(1070, test_case_t{true, 11784, 1070});
            test_args[4].test_cases.emplace_back(1071, test_case_t{true, 29735, 1071});
            test_args[18].test_cases.emplace_back(1072, test_case_t{false, 19793, 1072});
            test_args[31].test_cases.emplace_back(1073, test_case_t{false, 8355, 1073});
            test_args[24].test_cases.emplace_back(1078, test_case_t{true, 10804, 1078});
            test_args[2].test_cases.emplace_back(1081, test_case_t{true, 2199, 1081});
            test_args[8].test_cases.emplace_back(1082, test_case_t{false, 26702, 1082});
            test_args[11].test_cases.emplace_back(1083, test_case_t{true, 32706, 1083});
            test_args[12].test_cases.emplace_back(1083, test_case_t{false, 13195, 1083});
            test_args[8].test_cases.emplace_back(1084, test_case_t{false, 17392, 1084});
            test_args[22].test_cases.emplace_back(1084, test_case_t{false, 32470, 1084});
            test_args[28].test_cases.emplace_back(1084, test_case_t{true, 30790, 1084});
            test_args[16].test_cases.emplace_back(1087, test_case_t{true, 20635, 1087});
            test_args[16].test_cases.emplace_back(1089, test_case_t{true, 2017, 1089});
            test_args[0].test_cases.emplace_back(1090, test_case_t{false, 14300, 1090});
            test_args[10].test_cases.emplace_back(1091, test_case_t{true, 8717, 1091});
            test_args[6].test_cases.emplace_back(1092, test_case_t{true, 6597, 1092});
            test_args[4].test_cases.emplace_back(1093, test_case_t{true, 8696, 1093});
            test_args[2].test_cases.emplace_back(1103, test_case_t{false, 995, 1103});
            test_args[18].test_cases.emplace_back(1104, test_case_t{true, 8957, 1104});
            test_args[11].test_cases.emplace_back(1105, test_case_t{false, 172, 1105});
            test_args[12].test_cases.emplace_back(1105, test_case_t{true, 5971, 1105});
            test_args[31].test_cases.emplace_back(1105, test_case_t{true, 19073, 1105});
            test_args[8].test_cases.emplace_back(1106, test_case_t{true, 25447, 1106});
            test_args[28].test_cases.emplace_back(1106, test_case_t{false, 13933, 1106});
            test_args[24].test_cases.emplace_back(1110, test_case_t{true, 14758, 1110});
            test_args[16].test_cases.emplace_back(1111, test_case_t{false, 18125, 1111});
            test_args[0].test_cases.emplace_back(1112, test_case_t{false, 25116, 1112});
            test_args[6].test_cases.emplace_back(1114, test_case_t{false, 2985, 1114});
            test_args[10].test_cases.emplace_back(1114, test_case_t{true, 10996, 1114});
            test_args[4].test_cases.emplace_back(1115, test_case_t{true, 12723, 1115});
            test_args[10].test_cases.emplace_back(1116, test_case_t{false, 4976, 1116});
            test_args[22].test_cases.emplace_back(1117, test_case_t{false, 31445, 1117});
            test_args[2].test_cases.emplace_back(1125, test_case_t{true, 14867, 1125});
            test_args[18].test_cases.emplace_back(1126, test_case_t{false, 2734, 1126});
            test_args[11].test_cases.emplace_back(1127, test_case_t{true, 10303, 1127});
            test_args[12].test_cases.emplace_back(1127, test_case_t{true, 23668, 1127});
            test_args[31].test_cases.emplace_back(1127, test_case_t{false, 19352, 1127});
            test_args[8].test_cases.emplace_back(1128, test_case_t{true, 26765, 1128});
            test_args[28].test_cases.emplace_back(1128, test_case_t{true, 11536, 1128});
            test_args[8].test_cases.emplace_back(1130, test_case_t{false, 29914, 1130});
            test_args[24].test_cases.emplace_back(1132, test_case_t{true, 24207, 1132});
            test_args[16].test_cases.emplace_back(1133, test_case_t{true, 20761, 1133});
            test_args[6].test_cases.emplace_back(1136, test_case_t{false, 11834, 1136});
            test_args[0].test_cases.emplace_back(1136, test_case_t{false, 15654, 1136});
            test_args[10].test_cases.emplace_back(1138, test_case_t{true, 8801, 1138});
            test_args[2].test_cases.emplace_back(1147, test_case_t{true, 20732, 1147});
            test_args[4].test_cases.emplace_back(1147, test_case_t{true, 29766, 1147});
            test_args[11].test_cases.emplace_back(1149, test_case_t{false, 18038, 1149});
            test_args[12].test_cases.emplace_back(1149, test_case_t{false, 26089, 1149});
            test_args[18].test_cases.emplace_back(1149, test_case_t{true, 22749, 1149});
            test_args[22].test_cases.emplace_back(1149, test_case_t{false, 20826, 1149});
            test_args[31].test_cases.emplace_back(1149, test_case_t{true, 810, 1149});
            test_args[8].test_cases.emplace_back(1152, test_case_t{false, 10472, 1152});
            test_args[8].test_cases.emplace_back(1154, test_case_t{false, 7161, 1154});
            test_args[16].test_cases.emplace_back(1155, test_case_t{true, 27061, 1155});
            test_args[6].test_cases.emplace_back(1158, test_case_t{true, 29428, 1158});
            test_args[0].test_cases.emplace_back(1158, test_case_t{false, 7791, 1158});
            test_args[28].test_cases.emplace_back(1160, test_case_t{true, 28106, 1160});
            test_args[24].test_cases.emplace_back(1164, test_case_t{false, 31416, 1164});
            test_args[4].test_cases.emplace_back(1169, test_case_t{false, 14957, 1169});
            test_args[10].test_cases.emplace_back(1170, test_case_t{true, 5356, 1170});
            test_args[12].test_cases.emplace_back(1171, test_case_t{false, 5402, 1171});
            test_args[22].test_cases.emplace_back(1171, test_case_t{false, 32643, 1171});
            test_args[31].test_cases.emplace_back(1171, test_case_t{false, 17705, 1171});
            test_args[11].test_cases.emplace_back(1172, test_case_t{false, 5085, 1172});
            test_args[8].test_cases.emplace_back(1176, test_case_t{false, 719, 1176});
            test_args[16].test_cases.emplace_back(1177, test_case_t{true, 20944, 1177});
            test_args[2].test_cases.emplace_back(1179, test_case_t{false, 22746, 1179});
            test_args[18].test_cases.emplace_back(1181, test_case_t{true, 8103, 1181});
            test_args[6].test_cases.emplace_back(1183, test_case_t{true, 2701, 1183});
            test_args[24].test_cases.emplace_back(1186, test_case_t{false, 21483, 1186});
            test_args[0].test_cases.emplace_back(1190, test_case_t{false, 9008, 1190});
            test_args[4].test_cases.emplace_back(1191, test_case_t{false, 21620, 1191});
            test_args[28].test_cases.emplace_back(1192, test_case_t{false, 23527, 1192});
            test_args[22].test_cases.emplace_back(1193, test_case_t{true, 344, 1193});
            test_args[31].test_cases.emplace_back(1193, test_case_t{true, 31810, 1193});
            test_args[11].test_cases.emplace_back(1195, test_case_t{false, 7856, 1195});
            test_args[8].test_cases.emplace_back(1198, test_case_t{false, 32524, 1198});
            test_args[16].test_cases.emplace_back(1199, test_case_t{true, 14322, 1199});
            test_args[10].test_cases.emplace_back(1202, test_case_t{false, 15424, 1202});
            test_args[12].test_cases.emplace_back(1203, test_case_t{true, 23763, 1203});
            test_args[6].test_cases.emplace_back(1205, test_case_t{false, 11881, 1205});
            test_args[24].test_cases.emplace_back(1208, test_case_t{true, 2158, 1208});
            test_args[2].test_cases.emplace_back(1211, test_case_t{true, 14883, 1211});
            test_args[0].test_cases.emplace_back(1212, test_case_t{false, 11772, 1212});
            test_args[28].test_cases.emplace_back(1214, test_case_t{true, 11757, 1214});
            test_args[11].test_cases.emplace_back(1217, test_case_t{true, 17011, 1217});
            test_args[16].test_cases.emplace_back(1222, test_case_t{false, 1438, 1222});
            test_args[4].test_cases.emplace_back(1224, test_case_t{false, 3580, 1224});
            test_args[22].test_cases.emplace_back(1225, test_case_t{true, 20606, 1225});
            test_args[12].test_cases.emplace_back(1226, test_case_t{false, 12103, 1226});
            test_args[31].test_cases.emplace_back(1226, test_case_t{true, 17453, 1226});
            test_args[6].test_cases.emplace_back(1227, test_case_t{true, 6051, 1227});
            test_args[8].test_cases.emplace_back(1230, test_case_t{true, 24287, 1230});
            test_args[24].test_cases.emplace_back(1230, test_case_t{false, 32035, 1230});
            test_args[0].test_cases.emplace_back(1234, test_case_t{true, 5456, 1234});
            test_args[10].test_cases.emplace_back(1235, test_case_t{true, 8880, 1235});
            test_args[28].test_cases.emplace_back(1237, test_case_t{true, 6396, 1237});
            test_args[11].test_cases.emplace_back(1239, test_case_t{true, 10348, 1239});
            test_args[2].test_cases.emplace_back(1243, test_case_t{false, 23862, 1243});
            test_args[22].test_cases.emplace_back(1247, test_case_t{false, 3309, 1247});
            test_args[12].test_cases.emplace_back(1248, test_case_t{true, 32092, 1248});
            test_args[31].test_cases.emplace_back(1248, test_case_t{false, 26436, 1248});
            test_args[6].test_cases.emplace_back(1249, test_case_t{false, 32430, 1249});
            test_args[8].test_cases.emplace_back(1252, test_case_t{false, 10504, 1252});
            test_args[24].test_cases.emplace_back(1252, test_case_t{true, 7326, 1252});
            test_args[16].test_cases.emplace_back(1254, test_case_t{true, 32280, 1254});
            test_args[0].test_cases.emplace_back(1256, test_case_t{false, 15942, 1256});
            test_args[10].test_cases.emplace_back(1257, test_case_t{false, 21009, 1257});
            test_args[28].test_cases.emplace_back(1259, test_case_t{true, 20268, 1259});
            test_args[11].test_cases.emplace_back(1261, test_case_t{false, 16938, 1261});
            test_args[2].test_cases.emplace_back(1265, test_case_t{true, 10810, 1265});
            test_args[22].test_cases.emplace_back(1269, test_case_t{true, 10170, 1269});
            test_args[12].test_cases.emplace_back(1270, test_case_t{true, 10741, 1270});
            test_args[31].test_cases.emplace_back(1270, test_case_t{true, 8493, 1270});
            test_args[6].test_cases.emplace_back(1271, test_case_t{true, 21755, 1271});
            test_args[8].test_cases.emplace_back(1274, test_case_t{false, 30192, 1274});
            test_args[24].test_cases.emplace_back(1274, test_case_t{false, 31514, 1274});
            test_args[0].test_cases.emplace_back(1278, test_case_t{true, 29414, 1278});
            test_args[28].test_cases.emplace_back(1281, test_case_t{true, 25064, 1281});
            test_args[11].test_cases.emplace_back(1283, test_case_t{true, 24320, 1283});
            test_args[16].test_cases.emplace_back(1286, test_case_t{false, 15807, 1286});
            test_args[10].test_cases.emplace_back(1289, test_case_t{false, 21282, 1289});
            test_args[22].test_cases.emplace_back(1291, test_case_t{false, 15712, 1291});
            test_args[12].test_cases.emplace_back(1292, test_case_t{true, 17463, 1292});
            test_args[31].test_cases.emplace_back(1292, test_case_t{false, 17697, 1292});
            test_args[6].test_cases.emplace_back(1293, test_case_t{true, 8731, 1293});
            test_args[31].test_cases.emplace_back(1293, test_case_t{false, 9422, 1293});
            test_args[24].test_cases.emplace_back(1296, test_case_t{false, 25040, 1296});
            test_args[2].test_cases.emplace_back(1297, test_case_t{false, 18174, 1297});
            test_args[0].test_cases.emplace_back(1301, test_case_t{false, 29793, 1301});
            test_args[28].test_cases.emplace_back(1303, test_case_t{false, 18902, 1303});
            test_args[11].test_cases.emplace_back(1305, test_case_t{true, 422, 1305});
            test_args[8].test_cases.emplace_back(1306, test_case_t{false, 26624, 1306});
            test_args[8].test_cases.emplace_back(1308, test_case_t{true, 24138, 1308});
            test_args[16].test_cases.emplace_back(1308, test_case_t{true, 21009, 1308});
            test_args[10].test_cases.emplace_back(1311, test_case_t{false, 25335, 1311});
            test_args[22].test_cases.emplace_back(1313, test_case_t{false, 1254, 1313});
            test_args[12].test_cases.emplace_back(1314, test_case_t{true, 32402, 1314});
            test_args[6].test_cases.emplace_back(1315, test_case_t{false, 16201, 1315});
            test_args[31].test_cases.emplace_back(1317, test_case_t{true, 20099, 1317});
            test_args[24].test_cases.emplace_back(1318, test_case_t{true, 14336, 1318});
            test_args[2].test_cases.emplace_back(1319, test_case_t{true, 24756, 1319});
            test_args[24].test_cases.emplace_back(1320, test_case_t{false, 6879, 1320});
            test_args[0].test_cases.emplace_back(1324, test_case_t{true, 1984, 1324});
            test_args[11].test_cases.emplace_back(1327, test_case_t{false, 21695, 1327});
            test_args[8].test_cases.emplace_back(1330, test_case_t{true, 27694, 1330});
            test_args[16].test_cases.emplace_back(1330, test_case_t{true, 27616, 1330});
            test_args[22].test_cases.emplace_back(1335, test_case_t{false, 20696, 1335});
            test_args[28].test_cases.emplace_back(1335, test_case_t{true, 31913, 1335});
            test_args[12].test_cases.emplace_back(1337, test_case_t{false, 3663, 1337});
            test_args[28].test_cases.emplace_back(1337, test_case_t{true, 19470, 1337});
            test_args[2].test_cases.emplace_back(1341, test_case_t{true, 16323, 1341});
            test_args[24].test_cases.emplace_back(1342, test_case_t{true, 17545, 1342});
            test_args[10].test_cases.emplace_back(1343, test_case_t{true, 25475, 1343});
            test_args[6].test_cases.emplace_back(1348, test_case_t{false, 18215, 1348});
            test_args[11].test_cases.emplace_back(1349, test_case_t{true, 16772, 1349});
            test_args[31].test_cases.emplace_back(1349, test_case_t{false, 3173, 1349});
            test_args[8].test_cases.emplace_back(1352, test_case_t{false, 12197, 1352});
            test_args[16].test_cases.emplace_back(1352, test_case_t{true, 20480, 1352});
            test_args[16].test_cases.emplace_back(1354, test_case_t{false, 15509, 1354});
            test_args[0].test_cases.emplace_back(1356, test_case_t{false, 29644, 1356});
            test_args[28].test_cases.emplace_back(1359, test_case_t{false, 20382, 1359});
            test_args[24].test_cases.emplace_back(1364, test_case_t{false, 3825, 1364});
            test_args[10].test_cases.emplace_back(1365, test_case_t{false, 16078, 1365});
            test_args[22].test_cases.emplace_back(1367, test_case_t{true, 1108, 1367});
            test_args[6].test_cases.emplace_back(1370, test_case_t{true, 32454, 1370});
            test_args[11].test_cases.emplace_back(1371, test_case_t{false, 16302, 1371});
            test_args[31].test_cases.emplace_back(1371, test_case_t{true, 23268, 1371});
            test_args[2].test_cases.emplace_back(1373, test_case_t{true, 6071, 1373});
            test_args[8].test_cases.emplace_back(1374, test_case_t{false, 11856, 1374});
            test_args[16].test_cases.emplace_back(1376, test_case_t{true, 22619, 1376});
            test_args[28].test_cases.emplace_back(1381, test_case_t{false, 7368, 1381});
            test_args[28].test_cases.emplace_back(1383, test_case_t{false, 11264, 1383});
            test_args[24].test_cases.emplace_back(1386, test_case_t{true, 2801, 1386});
            test_args[22].test_cases.emplace_back(1389, test_case_t{true, 15872, 1389});
            test_args[6].test_cases.emplace_back(1392, test_case_t{false, 6260, 1392});
            test_args[31].test_cases.emplace_back(1393, test_case_t{true, 7245, 1393});
            test_args[8].test_cases.emplace_back(1396, test_case_t{true, 9940, 1396});
            test_args[10].test_cases.emplace_back(1398, test_case_t{true, 30359, 1398});
            test_args[16].test_cases.emplace_back(1398, test_case_t{false, 24395, 1398});
            test_args[11].test_cases.emplace_back(1403, test_case_t{true, 25956, 1403});
            test_args[28].test_cases.emplace_back(1405, test_case_t{false, 18948, 1405});
            test_args[2].test_cases.emplace_back(1406, test_case_t{true, 10818, 1406});
            test_args[24].test_cases.emplace_back(1409, test_case_t{false, 29821, 1409});
            test_args[22].test_cases.emplace_back(1411, test_case_t{false, 844, 1411});
            test_args[6].test_cases.emplace_back(1414, test_case_t{true, 28160, 1414});
            test_args[31].test_cases.emplace_back(1416, test_case_t{false, 12194, 1416});
            test_args[8].test_cases.emplace_back(1418, test_case_t{false, 17125, 1418});
            test_args[16].test_cases.emplace_back(1420, test_case_t{true, 23713, 1420});
            test_args[11].test_cases.emplace_back(1425, test_case_t{true, 3067, 1425});
            test_args[11].test_cases.emplace_back(1427, test_case_t{true, 17388, 1427});
            test_args[28].test_cases.emplace_back(1427, test_case_t{true, 31392, 1427});
            test_args[2].test_cases.emplace_back(1428, test_case_t{true, 23932, 1428});
            test_args[10].test_cases.emplace_back(1430, test_case_t{true, 21323, 1430});
            test_args[24].test_cases.emplace_back(1431, test_case_t{true, 18609, 1431});
            test_args[6].test_cases.emplace_back(1436, test_case_t{false, 18104, 1436});
            test_args[6].test_cases.emplace_back(1438, test_case_t{false, 20770, 1438});
            test_args[8].test_cases.emplace_back(1440, test_case_t{false, 30519, 1440});
            test_args[16].test_cases.emplace_back(1442, test_case_t{false, 19881, 1442});
            test_args[22].test_cases.emplace_back(1443, test_case_t{true, 10621, 1443});
            test_args[31].test_cases.emplace_back(1448, test_case_t{false, 20225, 1448});
            test_args[11].test_cases.emplace_back(1449, test_case_t{true, 11057, 1449});
            test_args[28].test_cases.emplace_back(1449, test_case_t{false, 9924, 1449});
            test_args[11].test_cases.emplace_back(1451, test_case_t{false, 9040, 1451});
            test_args[10].test_cases.emplace_back(1452, test_case_t{false, 21356, 1452});
            test_args[24].test_cases.emplace_back(1453, test_case_t{true, 26021, 1453});
            test_args[6].test_cases.emplace_back(1460, test_case_t{true, 9148, 1460});
            test_args[2].test_cases.emplace_back(1461, test_case_t{true, 31232, 1461});
            test_args[8].test_cases.emplace_back(1462, test_case_t{false, 16978, 1462});
            test_args[16].test_cases.emplace_back(1464, test_case_t{false, 1483, 1464});
            test_args[22].test_cases.emplace_back(1465, test_case_t{true, 775, 1465});
            test_args[31].test_cases.emplace_back(1470, test_case_t{false, 26882, 1470});
            test_args[28].test_cases.emplace_back(1471, test_case_t{false, 8729, 1471});
            test_args[11].test_cases.emplace_back(1473, test_case_t{false, 32133, 1473});
            test_args[10].test_cases.emplace_back(1474, test_case_t{false, 25088, 1474});
            test_args[24].test_cases.emplace_back(1475, test_case_t{false, 18167, 1475});
            test_args[6].test_cases.emplace_back(1482, test_case_t{true, 8892, 1482});
            test_args[2].test_cases.emplace_back(1483, test_case_t{false, 6034, 1483});
            test_args[8].test_cases.emplace_back(1484, test_case_t{true, 9554, 1484});
            test_args[16].test_cases.emplace_back(1486, test_case_t{false, 28270, 1486});
            test_args[22].test_cases.emplace_back(1487, test_case_t{false, 32605, 1487});
            test_args[11].test_cases.emplace_back(1495, test_case_t{false, 8325, 1495});
            test_args[10].test_cases.emplace_back(1496, test_case_t{true, 30173, 1496});
            test_args[31].test_cases.emplace_back(1502, test_case_t{true, 8960, 1502});
            test_args[28].test_cases.emplace_back(1504, test_case_t{true, 18407, 1504});
            test_args[2].test_cases.emplace_back(1506, test_case_t{true, 6923, 1506});
            test_args[8].test_cases.emplace_back(1506, test_case_t{false, 8474, 1506});
            test_args[8].test_cases.emplace_back(1507, test_case_t{true, 26907, 1507});
            test_args[24].test_cases.emplace_back(1507, test_case_t{true, 28662, 1507});
            test_args[22].test_cases.emplace_back(1509, test_case_t{false, 19144, 1509});
            test_args[6].test_cases.emplace_back(1514, test_case_t{true, 32031, 1514});
            test_args[11].test_cases.emplace_back(1517, test_case_t{true, 3683, 1517});
            test_args[10].test_cases.emplace_back(1518, test_case_t{true, 1849, 1518});
            test_args[16].test_cases.emplace_back(1518, test_case_t{true, 1188, 1518});
            test_args[31].test_cases.emplace_back(1524, test_case_t{false, 28001, 1524});
            test_args[2].test_cases.emplace_back(1528, test_case_t{true, 3049, 1528});
            test_args[8].test_cases.emplace_back(1529, test_case_t{false, 29489, 1529});
            test_args[22].test_cases.emplace_back(1531, test_case_t{true, 6135, 1531});
            test_args[6].test_cases.emplace_back(1536, test_case_t{true, 4652, 1536});
            test_args[28].test_cases.emplace_back(1536, test_case_t{true, 10788, 1536});
            test_args[11].test_cases.emplace_back(1539, test_case_t{true, 2548, 1539});
            test_args[24].test_cases.emplace_back(1539, test_case_t{false, 25424, 1539});
            test_args[16].test_cases.emplace_back(1540, test_case_t{true, 19108, 1540});
            test_args[24].test_cases.emplace_back(1540, test_case_t{true, 15185, 1540});
            test_args[31].test_cases.emplace_back(1546, test_case_t{true, 25393, 1546});
            test_args[2].test_cases.emplace_back(1550, test_case_t{true, 2964, 1550});
            test_args[10].test_cases.emplace_back(1550, test_case_t{false, 15247, 1550});
            test_args[6].test_cases.emplace_back(1558, test_case_t{false, 6505, 1558});
            test_args[28].test_cases.emplace_back(1558, test_case_t{false, 8512, 1558});
            test_args[8].test_cases.emplace_back(1561, test_case_t{true, 1853, 1561});
            test_args[11].test_cases.emplace_back(1561, test_case_t{true, 8376, 1561});
            test_args[16].test_cases.emplace_back(1562, test_case_t{false, 16949, 1562});
            test_args[24].test_cases.emplace_back(1562, test_case_t{true, 22930, 1562});
            test_args[16].test_cases.emplace_back(1563, test_case_t{false, 21046, 1563});
            test_args[22].test_cases.emplace_back(1563, test_case_t{true, 2007, 1563});
            test_args[31].test_cases.emplace_back(1568, test_case_t{false, 14498, 1568});
            test_args[2].test_cases.emplace_back(1572, test_case_t{true, 10677, 1572});
            test_args[10].test_cases.emplace_back(1573, test_case_t{true, 14820, 1573});
            test_args[6].test_cases.emplace_back(1580, test_case_t{true, 20926, 1580});
            test_args[11].test_cases.emplace_back(1583, test_case_t{false, 15696, 1583});
            test_args[24].test_cases.emplace_back(1584, test_case_t{true, 5560, 1584});
            test_args[16].test_cases.emplace_back(1585, test_case_t{false, 26209, 1585});
            test_args[22].test_cases.emplace_back(1585, test_case_t{false, 22114, 1585});
            test_args[22].test_cases.emplace_back(1587, test_case_t{false, 18081, 1587});
            test_args[28].test_cases.emplace_back(1590, test_case_t{true, 10272, 1590});
            test_args[31].test_cases.emplace_back(1590, test_case_t{false, 13176, 1590});
            test_args[8].test_cases.emplace_back(1593, test_case_t{false, 23965, 1593});
            test_args[2].test_cases.emplace_back(1594, test_case_t{false, 12473, 1594});
            test_args[10].test_cases.emplace_back(1595, test_case_t{true, 20617, 1595});
            test_args[11].test_cases.emplace_back(1605, test_case_t{true, 17036, 1605});
            test_args[24].test_cases.emplace_back(1606, test_case_t{true, 6360, 1606});
            test_args[16].test_cases.emplace_back(1607, test_case_t{false, 3707, 1607});
            test_args[24].test_cases.emplace_back(1608, test_case_t{true, 16372, 1608});
            test_args[22].test_cases.emplace_back(1609, test_case_t{false, 31498, 1609});
            test_args[6].test_cases.emplace_back(1612, test_case_t{true, 31741, 1612});
            test_args[28].test_cases.emplace_back(1612, test_case_t{false, 17054, 1612});
            test_args[31].test_cases.emplace_back(1612, test_case_t{true, 1655, 1612});
            test_args[8].test_cases.emplace_back(1615, test_case_t{true, 5457, 1615});
            test_args[10].test_cases.emplace_back(1618, test_case_t{true, 29599, 1618});
            test_args[2].test_cases.emplace_back(1626, test_case_t{true, 24014, 1626});
            test_args[11].test_cases.emplace_back(1627, test_case_t{false, 8920, 1627});
            test_args[16].test_cases.emplace_back(1629, test_case_t{false, 15163, 1629});
            test_args[24].test_cases.emplace_back(1630, test_case_t{true, 10360, 1630});
            test_args[22].test_cases.emplace_back(1631, test_case_t{true, 16650, 1631});
            test_args[6].test_cases.emplace_back(1634, test_case_t{false, 14548, 1634});
            test_args[28].test_cases.emplace_back(1634, test_case_t{true, 13278, 1634});
            test_args[31].test_cases.emplace_back(1634, test_case_t{true, 29498, 1634});
            test_args[10].test_cases.emplace_back(1640, test_case_t{false, 21765, 1640});
            test_args[8].test_cases.emplace_back(1647, test_case_t{false, 3453, 1647});
            test_args[2].test_cases.emplace_back(1649, test_case_t{true, 28821, 1649});
            test_args[11].test_cases.emplace_back(1650, test_case_t{false, 2917, 1650});
            test_args[16].test_cases.emplace_back(1651, test_case_t{false, 10914, 1651});
            test_args[11].test_cases.emplace_back(1652, test_case_t{true, 16639, 1652});
            test_args[22].test_cases.emplace_back(1653, test_case_t{false, 7366, 1653});
            test_args[6].test_cases.emplace_back(1656, test_case_t{false, 28372, 1656});
            test_args[28].test_cases.emplace_back(1656, test_case_t{true, 12255, 1656});
            test_args[31].test_cases.emplace_back(1657, test_case_t{false, 28149, 1657});
            test_args[10].test_cases.emplace_back(1662, test_case_t{false, 13031, 1662});
            test_args[24].test_cases.emplace_back(1662, test_case_t{true, 4567, 1662});
            test_args[8].test_cases.emplace_back(1669, test_case_t{true, 12445, 1669});
            test_args[16].test_cases.emplace_back(1673, test_case_t{true, 6907, 1673});
            test_args[11].test_cases.emplace_back(1674, test_case_t{false, 16686, 1674});
            test_args[22].test_cases.emplace_back(1675, test_case_t{true, 5097, 1675});
            test_args[28].test_cases.emplace_back(1678, test_case_t{true, 21291, 1678});
            test_args[31].test_cases.emplace_back(1679, test_case_t{false, 4350, 1679});
            test_args[2].test_cases.emplace_back(1681, test_case_t{true, 10580, 1681});
            test_args[10].test_cases.emplace_back(1684, test_case_t{true, 20134, 1684});
            test_args[24].test_cases.emplace_back(1684, test_case_t{true, 15302, 1684});
            test_args[6].test_cases.emplace_back(1688, test_case_t{false, 13924, 1688});
            test_args[8].test_cases.emplace_back(1691, test_case_t{false, 5100, 1691});
            test_args[16].test_cases.emplace_back(1695, test_case_t{true, 24890, 1695});
            test_args[11].test_cases.emplace_back(1696, test_case_t{true, 25119, 1696});
            test_args[22].test_cases.emplace_back(1697, test_case_t{false, 16753, 1697});
            test_args[31].test_cases.emplace_back(1701, test_case_t{false, 16541, 1701});
            test_args[10].test_cases.emplace_back(1706, test_case_t{false, 2401, 1706});
            test_args[6].test_cases.emplace_back(1710, test_case_t{true, 1390, 1710});
            test_args[28].test_cases.emplace_back(1710, test_case_t{true, 6487, 1710});
            test_args[2].test_cases.emplace_back(1713, test_case_t{false, 26695, 1713});
            test_args[24].test_cases.emplace_back(1716, test_case_t{true, 27367, 1716});
            test_args[22].test_cases.emplace_back(1719, test_case_t{false, 31392, 1719});
            test_args[8].test_cases.emplace_back(1723, test_case_t{true, 9122, 1723});
            test_args[16].test_cases.emplace_back(1727, test_case_t{true, 10201, 1727});
            test_args[10].test_cases.emplace_back(1728, test_case_t{false, 25442, 1728});
            test_args[11].test_cases.emplace_back(1728, test_case_t{false, 23675, 1728});
            test_args[6].test_cases.emplace_back(1732, test_case_t{false, 1590, 1732});
            test_args[28].test_cases.emplace_back(1732, test_case_t{false, 18343, 1732});
            test_args[31].test_cases.emplace_back(1733, test_case_t{true, 4168, 1733});
            test_args[6].test_cases.emplace_back(1734, test_case_t{false, 20477, 1734});
            test_args[2].test_cases.emplace_back(1735, test_case_t{true, 31303, 1735});
            test_args[24].test_cases.emplace_back(1739, test_case_t{false, 660, 1739});
            test_args[8].test_cases.emplace_back(1746, test_case_t{false, 220, 1746});
            test_args[16].test_cases.emplace_back(1749, test_case_t{false, 18245, 1749});
            test_args[22].test_cases.emplace_back(1751, test_case_t{false, 1305, 1751});
            test_args[28].test_cases.emplace_back(1754, test_case_t{true, 19100, 1754});
            test_args[31].test_cases.emplace_back(1755, test_case_t{true, 26441, 1755});
            test_args[6].test_cases.emplace_back(1756, test_case_t{false, 27166, 1756});
            test_args[31].test_cases.emplace_back(1756, test_case_t{false, 28253, 1756});
            test_args[2].test_cases.emplace_back(1757, test_case_t{true, 15564, 1757});
            test_args[10].test_cases.emplace_back(1760, test_case_t{false, 12285, 1760});
            test_args[11].test_cases.emplace_back(1760, test_case_t{true, 1962, 1760});
            test_args[8].test_cases.emplace_back(1768, test_case_t{true, 30184, 1768});
            test_args[16].test_cases.emplace_back(1771, test_case_t{true, 440, 1771});
            test_args[24].test_cases.emplace_back(1771, test_case_t{false, 25016, 1771});
            test_args[22].test_cases.emplace_back(1773, test_case_t{false, 17840, 1773});
            test_args[6].test_cases.emplace_back(1778, test_case_t{true, 25718, 1778});
            test_args[31].test_cases.emplace_back(1778, test_case_t{false, 7182, 1778});
            test_args[2].test_cases.emplace_back(1779, test_case_t{true, 463, 1779});
            test_args[10].test_cases.emplace_back(1782, test_case_t{true, 2317, 1782});
            test_args[11].test_cases.emplace_back(1782, test_case_t{false, 25893, 1782});
            test_args[28].test_cases.emplace_back(1786, test_case_t{false, 28472, 1786});
            test_args[8].test_cases.emplace_back(1790, test_case_t{true, 20197, 1790});
            test_args[24].test_cases.emplace_back(1794, test_case_t{true, 27823, 1794});
            test_args[22].test_cases.emplace_back(1795, test_case_t{true, 5835, 1795});
            test_args[22].test_cases.emplace_back(1797, test_case_t{true, 510, 1797});
            test_args[6].test_cases.emplace_back(1800, test_case_t{false, 28402, 1800});
            test_args[31].test_cases.emplace_back(1800, test_case_t{true, 2754, 1800});
            test_args[2].test_cases.emplace_back(1801, test_case_t{true, 22375, 1801});
            test_args[16].test_cases.emplace_back(1803, test_case_t{true, 27600, 1803});
            test_args[10].test_cases.emplace_back(1804, test_case_t{false, 13573, 1804});
            test_args[11].test_cases.emplace_back(1804, test_case_t{false, 24427, 1804});
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
