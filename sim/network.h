// network.h
//   by Derek Chiou
//      March 4, 2007
// 

// for 382N-10

#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include "my_fifo.h"
#include "iu.h"

class network_t {  // output queued
  int num_ports;
  
  my_fifo_t <net_cmd_t> ***from_net_fifos;

 public:
  network_t(int num_ports);
  
  bool to_net(int src_port, pri_t pri, net_cmd_t cmd);
  bool from_net_p(int dest_port, pri_t pri);
  net_cmd_t from_net(int dest_port, pri_t pri);
  
  void bind(int p, iu_t *i);
  void advance_one_cycle();
};
#endif
