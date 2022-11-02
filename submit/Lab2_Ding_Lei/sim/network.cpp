// network.cpp
//   by Derek Chiou
//      March 4, 2007
// 

// STUDENTS: YOU ARE NOT ALLOWED TO MODIFY THIS FILE.

// for 382N-10

#include "types.h"
#include "my_fifo.h"
#include "network.h"
#include "iu.h"
#include "helpers.h"


network_t::network_t(int p) {
  num_ports = p;

  from_net_fifos = new my_fifo_t <net_cmd_t> ** [NUM_PRIORITIES];

  printf("NUM_PRIORITIES = %d\n", NUM_PRIORITIES);

  for (int p = 0; p < NUM_PRIORITIES; ++p) {
    from_net_fifos[p] = new my_fifo_t <net_cmd_t> * [num_ports];

    for (int i = 0; i < num_ports; ++i) {
      char *name = new char[32]; // conservative
      net_cmd_t empty;

      empty.valid_p = false;

      sprintf(name, "net_fifo[%s][%d]", PRI2STRING((pri_t)p), i);
      from_net_fifos[p][i] = new my_fifo_t <net_cmd_t>;
      from_net_fifos[p][i]->init_time(name, 8, empty);
    }
  }
}

bool network_t::to_net(int src_port, pri_t pri, net_cmd_t cmd) {

  NOTE_ARGS(("sending from %d to %d", src_port, cmd.dest));

  // src_port is not needed in this implementation, but may eventually
  // be needed, so we have it here.

  // just enqueue into appropriate fifo if possible

  bool space_p = from_net_fifos[pri][cmd.dest]->space_p();
  if (space_p) from_net_fifos[pri][cmd.dest]->tenqueue(cur_cycle + NETWORK_LATENCY, cmd);

  return(space_p);

}

bool network_t::from_net_p(int dest_port, pri_t pri) {
  return(!from_net_fifos[pri][dest_port]->tempty(cur_cycle));
}
			   
net_cmd_t network_t::from_net(int dest_port, pri_t pri) {
  return(from_net_fifos[pri][dest_port]->tdequeue(cur_cycle));
}
			   

void network_t::advance_one_cycle() {
  
}
