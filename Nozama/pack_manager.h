/*pack_manager.h
 *Comp15, Spring 2013
 *Project 1
 *Name: Shea Clark-Tieche
 *Notes: pack_manager will hold a dynamic array of packers. It will take orders
*	 from the manager and then find the packer who is showing the 
*	 shortest wait time.
 */

#ifndef PACKM_H
#define PACKM_H


#include "packer.h"
#include "queue.h"
#include <iostream>


class PackManager {

	public:
		//sets up a dynamic array of packers
		PackManager();
		//takes in an order
		void get_order(Order);
		//keeps track of time
		void clock();
		//runs the packmanager... like a mini main
		void run(int);
		//says if all the packers queues are empty
		bool isEmpty();
		//gets order that is waiting to be sent out
		Order grab_order();
		//says if there are finished orders or not
		bool post_isEmpty();
		//prints packaged orders
		void printer();
		//resets variables
		void restart();
		//prints packer queues for tests
		void print();
		
	private:
		//pointer for a dynamic array of packers
		Packer*  packers;
		int cur_time;
		//finds the packer with shortest queue
		//returns index to packer
		int find_shortest(bool);
		//finds shortest supreme wait
		int supreme_shortest();
		//gives order to a packer
		void place_order();
		//A queue of orders done being packed at a certain time
		Queue post_pack;
		
};

#endif
