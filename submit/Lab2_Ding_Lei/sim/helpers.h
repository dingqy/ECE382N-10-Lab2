// helpers.h
//   by Derek Chiou
//      March 4, 2007
// 

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THE FUNCTIONS IN THIS FILE, BUT CAN ADD ADDITIONAL FUNCTIONS IF YOU NEED TO.
// for 382N-10

#include "types.h"

const int LG_INTERLEAVE_SIZE = 8;

int gen_node(address_t addr);
int gen_local_addr(address_t addr);
int gen_local_cache_line(address_t addr);

bool within_tolerance(double, double, double);

int lg(int x);

void copy_cache_line(data_t dest, data_t src);

void terminate_on_error();

int lg(int x);

char *PRI2STRING(pri_t pri);
