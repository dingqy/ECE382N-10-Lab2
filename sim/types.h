// types.h
//   by Derek Chiou
//      March 4, 2007
// 

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.
// for 382N-10

#ifndef TYPES_H
#define TYPES_H

const int ADDR_SIZE = 32;
const int CACHE_LINE_SIZE = 16;    // needs to be consistent with LG_CACHE_LINE_SIZE
const int LG_CACHE_LINE_SIZE = 4;  // needs to be consistent with CACHE_LINE_SIZE
const int MEM_SIZE = 1024;
const int NUM_PRIORITIES = 4;

const int NETWORK_LATENCY = 10;

const int SIZE_INV_QUEUE = 32;
const int SIZE_IU_TO_NET_BUFFER = 2;

typedef unsigned int uint;

typedef uint address_t;      // cannot be addr_t because cygwin defines
typedef uint address_tag_t;
typedef enum {
    INVALID, SHARED, EXCLUSIVE, MODIFIED
} permit_tag_t;
typedef enum {
    READ, WRITE, INVALIDATE
} busop_t;
typedef enum {
    REPLY = 0, WRBACK, FORWARD, REQUEST
} pri_t;
typedef int replacement_t;
typedef int bus_tag_t;

typedef int data_t[CACHE_LINE_SIZE];

typedef struct {
    int num_procs;
    int num_cycles;
    int test;
    int verbose;
} args_t;

extern args_t args;

typedef enum {
    DIR_INVALID, DIR_SHARED_NO_DATA, DIR_SHARED, DIR_OWNED
} dir_state_t;

typedef struct {
    dir_state_t state;
    int owner;
    uint shared_nodes;
} dir_t;

// forward declarations
class iu_t;

class cache_t;

class network_t;

typedef struct {
    bool hit_p;
    bool retry_p;
} response_t;

typedef struct {
    busop_t busop;
    address_t addr;
    bus_tag_t tag;
    permit_tag_t permit_tag;
    data_t data;
} proc_cmd_t;

typedef struct {
    bool valid_p;
    int dest;
    int src;

    proc_cmd_t proc_cmd;
} net_cmd_t;

typedef struct {
    bool valid;
    pri_t pri;
    net_cmd_t net_cmd;
} iu_net_buffer_t;

typedef proc_cmd_t forward_cmd_t;

extern int cur_cycle;
extern int cache_line_size;


#endif
