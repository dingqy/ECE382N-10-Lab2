// cache.h
//   by Derek Chiou
//      March 4, 2007
// 

// for 382N-10

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.

#ifndef CACHE_H
#define CACHE_H
#include "types.h"

typedef struct {
  address_tag_t   address_tag;
  permit_tag_t permit_tag;
  int          set;
  int          way;
} cache_access_response_t;

class cache_line_t {
 public:
  address_tag_t    address_tag;
  permit_tag_t  permit_tag;
  replacement_t replacement;

  data_t data;
};

class cache_t {
  // cache state
  int node;
  cache_line_t **tags;

  // pointers
  iu_t *iu;

  // management state
  int assoc;
  int num_sets;
  int cache_line_size;

  int lg_assoc;
  int lg_num_sets;
  int lg_cache_line_size;

  int set_shift;
  uint set_mask;

  uint cache_line_mask;

  int address_tag_shift;

  // stats
  int full_hits;
  int partial_hits;
  int misses;

 public:
  cache_t(int __n, int lg_assoc, int lg_num_sets, int lg_cache_line_size);
  void bind(iu_t *i);
  void init(int __n, int lg_assoc, int lg_num_sets, int lg_cache_line_size);

  // stats
  void print_stats();
  double hit_rate();

  // helpers
  address_tag_t gen_address_tag(address_t addr);
  int gen_set(address_t addr);
  int gen_offset(address_t addr);

  // manipulate cache
  bool cache_access(address_t addr, permit_tag_t permit, cache_access_response_t *car);
  void touch_replacement(cache_access_response_t car);
  void modify_permit_tag(cache_access_response_t car, permit_tag_t permit);
  void modify_address_permit_tags(cache_access_response_t car);
  void cache_fill(cache_access_response_t car, data_t data);

  int   read_data(address_t addr, cache_access_response_t car);
  void write_data(address_t addr, cache_access_response_t car, int data);

  // replacement
  cache_access_response_t lru_replacement(address_t addr);

  // processor side
  response_t load(address_t addr, bus_tag_t tag, int *data, bool retried_p);
  response_t store(address_t addr, bus_tag_t tag, int data, bool retried_p);

  // response side
  void reply(proc_cmd_t proc_cmd);

  // snoop side
  response_t snoop(net_cmd_t net_cmd);

};
#endif
