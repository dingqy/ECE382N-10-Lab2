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
    permit_tag_t cache_state;
    dir_state_t mem_state;
    int address;
    int data;
    unsigned int sharer_list;
    int owner;
} test_result_t;

typedef struct test_init_t {
    int address;
    data_t data{};

    test_init_t(int address_in, const data_t data_in) : address(address_in) {
        for (int i = 0; i < CACHE_LINE_SIZE; i++) {
            data[i] = data_in[i];
        }
    }
} test_init_t;

typedef struct {
    int addr_range;
    std::vector<test_init_t> test_inits;
    std::vector<std::pair<int, test_case_t>> test_cases;
    std::vector<std::pair<int, test_record_t>> test_records;
    std::vector<std::pair<int, test_result_t>> test_results;
    std::vector<std::pair<int, test_result_t>> test_goldens;
    std::default_random_engine random_generator;
} test_args_t;


extern test_args_t test_args[32];
