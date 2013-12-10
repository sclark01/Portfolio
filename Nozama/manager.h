/*manager.h
 *Comp15, Spring 2013
 *Project 1
 *Name: Shea Clark-Tieche
 *Notes: This class will serve as the hub for the program. It will store
 *	all the orders in a linked list until their arrive time, at which point
 *	it will send an order to fetch. Once an order has been fetched, the 
 *	order will be returned to the manager who will find the shortest 
 *	packers queue and place it there. After orders have been packaged they 
 * 	will be returned to the manager who will add that orders total time
 *	to the simulation's total time. When the simulation is done, print()
 *	will print the simulation summary. 
 */

#ifndef MANAGER_H
#define MANAGER_H


#include "fetch.h"
#include "packer.h"
#include "queue.h"
#include "pack_manager.h"
#include <iostream>

#include <iostream>

using namespace std;

class Manager {
  
  public:
  //Default constructor	  
  Manager();
  //cins data and stores in linked list
  void get_orders();
  //This function is the command center for the simulation
  void run();

  private:     
  //takes in data and puts it in an order
  Order build(int, string, int, int, int, bool);
  //orders waiting to arrive 
  Queue orders_sim1;
  Queue orders_sim2;
  Queue orders;
  //queue to hold packaged Orders
  Queue been_packed_sim1;
  Queue been_packed_sim2;
  //order recieved
  Order recieve;
  //the fetcher
  Fetch fetcher1;
  //the pack_manager;
  PackManager pacMan;
  //finds the extreme values (min & max)
  void find_extremes();
  //finds the mean values
  void find_means();
  //prints out all the info at the end
  void print();
  //prints the specific info for a simulation
  void print_sim1();
  void print_sim2();
  //adds sim2 times to a queue of orders
  void combine();
  //keeps track of global time
  int time;
  //keeps track of number of orders
  int num_orders;
  //the minimum time for sim1
  int sim1_min;
  //the max time for sim1
  int sim1_max;
  int sim2_min;
  int sim2_max;
  //mean time for sim1
  int sim1_mean;
  int sim2_mean_sup;
  int sim2_mean_reg;
  int sim2_mean_all;
  //total time spent in sim1
  int total_time_sim1;
  
};

#endif


