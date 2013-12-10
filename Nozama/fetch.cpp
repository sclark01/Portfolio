/*fetch.cpp
*Shea C-T
 */

#include "fetch.h"


/*Does: Constructor, wait_time to zero and avail to zero. sets cur_time to -1
 *Arg: None
 *Returns: nothing
 *Calls: nothing
 *Notes: Sets cur_time to negative one so that clock starts running as the 
 *	 program starts, and therefor the first time the program uses is 0
 */
Fetch::Fetch(){
    wait_time = 0;
    cur_time = 0;
    avail = 0;
    in_progress = false;
}
//this function resets the fetcher so that simulation 2 can begin
void Fetch::restart(){
    wait_time = 0;
    cur_time = 0;
    avail = 0;
    in_progress = false;
    fetchlist.restart();
}

/*Does: checks to see if the fetcher's queue is empty
 *Arg: None
 *Returns: true if empty, false if not
 *Calls: nothing
 *Notes: none
 */
bool Fetch::is_empty(){

    if(fetchlist.is_empty() && !in_progress){
	return true;
    }
    else {
	return false;
    }
}

/*Does: Puts an order onto the fetcher's queue
 *Arg: an order
 *Returns: nothing
 *Calls: insert()
 *Notes: none
 */
void Fetch::fetcher(Order order1) {
	fetchlist.insert(order1);
}

/*Does: updates fetch's private data to reflect correct global time
 *Arg: none
 *Returns: nothing
 *Calls: nothing
 *Notes: none
 */
void Fetch::clock(int t) {
	cur_time = t;
}

/*Does: gets an order off the fetch queue
 *Arg: nothing
 *Returns: an Order that is done being fetched
 *Calls: remove
 *Notes: none
 */
void Fetch::fetch_it() {

	fetching = fetchlist.remove();
	avail = cur_time + fetching.fetch;
	in_progress = true;

}

/*Does: checks to see if fetch is ready to fetch a new order
 *Arg: nothing
 *Returns: true if available, false if not
 *Calls: nothing
 *Notes: checks to see if the current time is equal to or larger than the
 *	 next time at which fetch will be available to fetch.
 */
bool Fetch::fetch_avail() {

	if (cur_time >= avail) 
		return true;
	else
		return false;
}
//lets the manager know when an order is ready to leave the fetch warehouse
bool Fetch::done_fetch(){
  
  if (cur_time == avail && in_progress){
    return true;
  }
  else
    return false;
}
//sends the order that is finished being fetched to main 
Order Fetch::grab_fetch(){
  in_progress = false;
  return fetching;
}

void Fetch::print(){
    fetchlist.print();
 }






		
		
		
		
		
