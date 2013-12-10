/*packer.h
 *Comp15, Spring 2013
 *Project 1
 *Name: Shea Clark-Tieche
 *Notes: The packer will have a queue of Orders. The overloaded constructor 
 *	will create the queue as well as send a supreme customer to the front
 *	of a queue. Packer will take an order off the queue and pack it. If a
 *	supreme customer comes up on the queue it will pause what it's doing
 *	and pack the supreme customer. Packer will return packed orders to the 
 *	manager. 
 */

#ifndef PACKER_H
#define PACKER_H

#include "queue.h"

#include <iostream>

class Packer {
  
  public:
    //default constructor
    Packer();
    //returns the wait time in a packer's queue, so other classes can see it
    int wait();
    //returns the wait time for supreme memebers
    int sup_wait();
    //takes an order off the queue, calculates its pack time, and
    //returns the order. 
    Order packer();
    //adds an order to the queue 
    void add(Order);
    //lets manager know if a queue has orders that are finished
    bool done_pack();
    //returns an order that is finished to the manager
    Order get_pack();
    //actually packages an order 
    void packing(bool);
    //adjusts the time remaining
    void adjust_time();
    //says if all pack queues are empty
    bool isEmpty();
    //checks if an order is supreme
    void check_sup();
    //sets time within packers to current time outside packers
    void set_time(int);
    //check to see if an order is in process
    bool getInProcess();
    //prints a queue
    void print();
    
  private:
    //the linked list of orders waiting to be packed
    Queue pack_line;
    //the wait_time in a packer's Queue
    int wait_time;  
    //the wait time for supreme memeber
    int wait_sup;
    //the wait time for regular memebers
    int reg_wait;
    //the total pack_time of all orders in queue
    int queue_time;
    //the time remaining for an order to be 
    int time_remaining;
    //the time when a packer will again be available
    int pack_avail;
    //the order being processed
    Order process;
    //the current time
    int cur_time;
    //true if an order is in process
    bool in_process;
};

#endif
