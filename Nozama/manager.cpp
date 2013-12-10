/*manager.cpp
*Name: Shea C-T
*Notes: This is the command center for the program, where all other classes
*	are called from. At this stage, it takes in data, stores the data in
*	a queue. When an order's arrival time arrives it sends it to
*	fetch, and if fetch is done working on an order the order is returned
*	by fecth_it and stored in another queue in manager so the result can
*	be printed. 
 */

#include "manager.h"

#include <iostream>
using namespace std;

/*Does: Constructor, sets time to 0.
 *Arg: None
 *Returns: nothing
 *Calls: nothing
 *Notes: none
 */
Manager::Manager(){
    time = 0;
    sim1_min = 0;
    sim1_max = 0;
    sim2_min = 0;
    sim2_min = 0;
    num_orders = 0;
    total_time_sim1 = 0;
    sim1_mean = 0;
    sim2_mean_sup = 0;
    sim2_mean_reg = 0;
    sim2_mean_all = 0;
    
}

/*Does: gets the data from a user. It sorts the data and stores it
 *Arg: None
 *Returns: nothing
 *Calls: build and orders.insert
 *Notes: none
 */
void Manager::get_orders(){

    string excess;
    int order_id;
    string cus_type;
    int arrive;
    int fetch;
    int pack;
    Order new_order_sim1;
    Order new_order_sim2;
    bool sim1;

    while(cin >> excess){
	sim1 = true;
	cin >> order_id >> excess >> cus_type >> excess >> excess >> excess >> 
	excess >>  arrive >> excess >> excess >> fetch >> excess >> excess >> 
	excess >> pack >> excess;
	new_order_sim1 = build(order_id, cus_type, arrive, fetch, pack, sim1);
       	orders_sim1.insert(new_order_sim1);
	sim1 = false;
	new_order_sim2 = build(order_id, cus_type, arrive, fetch, pack, sim1);
	orders_sim2.insert(new_order_sim2);
	num_orders++;
	
    }

}

/*Does: puts the data from the user into a struct of type order
 *Arg: all the needed values for an order
 *Returns: the newly made order
 *Calls: nothing
 *Notes: none
 */
Order Manager::build(int id, string cus, int a, int f, int p, bool sim1) {

    Order o;

    o.order_id = id;
    o.cusType = cus;
    if (cus == "supreme" && sim1){
	o.supreme = false;
    }
    else if (cus == "supreme" && !sim1){
	o.supreme = true;
    }
    
    else {
	o.supreme = false;
    }
    
    o.arrive = a;
    o.fetch = f;
    o.pack = p;
    o.totalSim1 = 0;
    o.totalSim2 = 0;
    o.interuption = 0;
    return o;
}

/*Does: the function that runs Nozama. 
 *Arg: None
 *Returns: nothing
 *Calls: the is_empty() function on multiple cues, get_head(), remove(),
 *	 fetcher(), fetch_avail(), insert(), print(), clock()
 *Notes: This is the main run center for the program. Once I get a little
 *	  further I'm going to break it into sub functions, but to get started
 *	  I wanted to put it all in one function. This function also controls
 *	  time. It sends the "current time" to fetcher's "clock" so that 
 *	  fetcher can update it's private data to reflect the correct time.
 *	  When an order is done being fetched it is removed and added to a
 *	  new queue in manager, so that it can be printed (just for part II)
 * 
 */
void Manager::run(){

    Order send;
    Order done;
    Order test;

    for (int j = 0; j < 2; j++) {
	    if (j == 0){
		    orders = orders_sim1;
	    }
	    else {
		    time = 0; 
		    fetcher1.restart();
		    pacMan.restart();
		    orders = orders_sim2;
	    }

while (!orders.is_empty() || !fetcher1.is_empty() || !pacMan.isEmpty()) {   
     
    	if (!orders.is_empty()){
		send = orders.get_head();
		if (send.arrive == time){
	   	 orders.remove();
	    	 fetcher1.fetcher(send);
		}
	    }
	fetcher1.clock(time);
	if (fetcher1.done_fetch()){
	    pacMan.get_order(fetcher1.grab_fetch());
	}
	if (fetcher1.fetch_avail() && !fetcher1.is_empty()){
	    fetcher1.fetch_it();
	}
	pacMan.run(time);
	
		while(!pacMan.post_isEmpty()){
			done = pacMan.grab_order();
			done.totalSim1 = time - done.arrive;
			if (j == 0){
				been_packed_sim1.insert(done);
			}
			else {
				
				been_packed_sim2.insert(done);
			}
		}
		time++;
   }
   }
  print();
}

/*Does: adds simulation times from sim2 to the sim2 slot for the orders of  
*	the sim1 finsihed queue.
 *Arg: None
 *Returns: nothing
 *Calls: the combine function in the queue class
 *Notes: none
 */
void Manager::combine(){
	been_packed_sim1.combine(been_packed_sim2);
}

/*Does: prints out the final times and orders
 *Arg: None
 *Returns: nothing
 *Calls: combine, find_extremes, find_means, been_packed_sim1, and print_sim1
 *Notes: none
 */
void Manager::print(){
 combine();
  find_extremes();
  find_means();
 been_packed_sim1.print(); //inlcudes sim2 times as well because of combine()
  print_sim1();
  print_sim2();
  
}

/*Does: prints out the actual stats for sim1
 *Arg: None
 *Returns: nothing
 *Calls: nothing 
 *Notes: none
 */
void Manager::print_sim1(){
    cout << "sim1 min elapsed time " << sim1_min << " minutes\n" 
         << "sim1 max elapsed time " << sim1_max << " minutes\n"
         << "sim1 mean elapsed time " << sim1_mean << " minutes\n"
         << num_orders << " orders processed\n";
    cout << endl;
}

/*Does: prints out the actual stats for sim2
 *Arg: None
 *Returns: nothing
 *Calls: nothing 
 *Notes: nonee
 */
void Manager::print_sim2(){
  cout << "sim2 min total time " << sim2_min << " minutes\n" 
       << "sim2 max total time " << sim2_max << " minutes\n"
       << "sim2 mean total time for all customers " << sim2_mean_all 
	  << " minutes\n"
       << "sim2 mean total time for supreme customers " << sim2_mean_sup 
	  << " minutes\n"
       << "sim2 mean total time for regular customers " << sim2_mean_reg 
	  << " minutes\n"
       << num_orders << " orders processed\n";
}

/*Does: finds the extreme values for each data set
 *Arg: None
 *Returns: nothing
 *Calls: functions in queue class to find the actual values 
 *Notes: none
 */
void Manager::find_extremes(){
  
 sim1_min = been_packed_sim1.min_time();
 sim2_min = been_packed_sim2.min_time();
 sim1_max = been_packed_sim1.max_time();
 sim2_max = been_packed_sim2.max_time();
 
}

/*Does: finds the mean time 
 *Arg: None
 *Returns: nothing
 *Calls: the function in the queue class that gives the total time 
 *Notes: none
 */
void Manager::find_means() {
  int* sim2_means = new int[3];
  
  total_time_sim1 = been_packed_sim1.total();
  
  sim1_mean = total_time_sim1/num_orders;
  sim2_means = been_packed_sim2.mean();
  
  sim2_mean_sup = sim2_means[0];
  sim2_mean_reg = sim2_means[1];
  sim2_mean_all = sim2_means[2];
 
}

	

    
    
    
    
    
