/*fetch.h
 *Comp15, Spring 2013
 *Project 1
 *Name: Shea Clark-Tieche
 *Notes: Fetch will have a queue of orders. Fetch_it() will remove the next
 *	order off the queue and process it for the duration of that order's 
 *	"wait time." After the wait time, fetch_it will return the order. With
 *	modularity in mind, I also have it keep track of the queue wait time 
 */

#ifndef FETCH_H
#define FETCH_H

#include <iostream>
#include "queue.h"

class Fetch {
  
  public: 
    //Default constructor
    Fetch();	
    //returns wait_time, so other classes can see but not change wait_time
    int get_wt();
    //removes order from fetch queue and "fetches" desired object
    //returns an order which is then sent to a packer's queue
    void fetch_it();
    //returns true if fetch queue is empty
    bool is_empty();
    //function for time control in fetch
    void clock(int);
    //takes in an order from manager and inserts it on queue
    void fetcher(Order);
    //says if a fetcher is available to fetch
    bool fetch_avail();
    //resets variables
    void restart();
    //prints queue
    void print();
    //says if there is something to be picked up from being fetched
    bool done_fetch();
    //returns the order being fetched
    Order grab_fetch();

    
    
  private:
	//Queue for fetch
	Queue fetchlist;
	//length of queue
	int wait_time;
	//current global time
	int cur_time;
	//time when fetch will not be fetching something
	int avail;
	//Order being fetched
	Order fetching;
	//says if something is being fetched
	bool in_progress;
	
};

#endif




