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
