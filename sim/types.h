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
const int NUM_PRIORITIES = 2;

const int NETWORK_LATENCY = 10;

typedef unsigned int uint;

typedef uint address_t;      // cannot be addr_t because cygwin defines
typedef uint address_tag_t;
typedef enum {INVALID, SHARED, EXCLUSIVE, MODIFIED} permit_tag_t;
typedef enum {READ, WRITE, INVALIDATE} busop_t;
typedef enum {REPLY = 0, REQUEST} pri_t;
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

extern int cur_cycle;
extern int cache_line_size;


#endif
