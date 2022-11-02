// test.h
//   Derek Chiou
//     May 19, 2007
#include <vector>
#include <queue>
#include <random>

void init_test();

void finish_test();

typedef struct {
    bool write;
    int address;
    int data;
} test_case_t;

typedef struct {
    bool mem_cache;
    int address;
} test_record_t;

typedef struct {
    int address;
    int data;
} test_result_t;

typedef struct {
    int addr_range;
    std::vector<std::pair<int, test_case_t>> test_cases;
    std::vector<std::pair<int, test_record_t>> test_records;
    std::vector<std::pair<int, test_result_t>> test_results;
    std::vector<std::pair<int, test_result_t>> test_goldens;
    std::default_random_engine random_generator;
} test_args_t;


extern test_args_t test_args[32];
