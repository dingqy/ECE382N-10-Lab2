// proc.h
//   by Derek Chiou
//      March 4, 2007
// 
// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.

// for 382N-10

#include "types.h"

extern int cur_cycle;


// models a processor's ld/st stream
class proc_t {
    int proc;
    response_t response;

    address_t addr;
    bool ld_p;

    cache_t *cache;

    bool init_valid = true;

    int record_index;

    int case_index;

public:
    proc_t(int p);

    void init();

    void bind(cache_t *c);

    void advance_one_cycle();

};
