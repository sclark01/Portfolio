/*Queue.cpp
*Shea C-T
 */

#include "queue.h"

/*Does: sets head and tail to NULL, size to zero
 *Arg: none
 *Returns: nothing
 *Calls: nothing
 *Notes: none
 */
Queue::Queue(){

    head = NULL;
    tail = NULL;
    size = 0;
}

void Queue::restart(){
  head = NULL;
  tail = NULL;
  size = 0;
}

/*Does: checks to see if a queue is empty
 *Arg: none
 *Returns: true if empty, false if not
 *Calls: nothing
 *Notes: none
 */
bool Queue::is_empty(){
	if (head == NULL) {
		return true;
	}
	else {	
		return false;
	}
}

/*Does: adds a new order to the queue
 *Arg: an order
 *Returns: true if empty, false if not
 *Calls: nothing
 *Notes: none
 */
void Queue::insert(Order o){
    Node* temp = new Node;
    temp->data = o;
    size++;
    
   // cerr << " and now INSERTING " << temp->data.order_id << endl;
    
    if (head == NULL){
	temp->next = NULL;
	head = temp;
	tail = temp;
    }
    else {
	temp->next = NULL;
	tail->next = temp;
	tail = temp;
	//cerr << " the tail is " << tail->data.order_id << endl;
    }
}
//inserts an order directly to the front of the queue 
void Queue::insertFront(Order o)
{
	Node* temp = new Node; 
	temp->data = o;
	size++;
	
	if (head == NULL){
		temp->next = NULL;
		head = temp;
		tail = temp;
	}
	else {
		temp->next = head;
		head = temp;
	}
}

/*Does: removes an order from a queue
 *Arg: none
 *Returns: the order removed
 *Calls: nothing
 *Notes: exits the program if it tries to remove from an empty list
 */
Order Queue::remove(){

    Order v;
    
    if (head == NULL){
	cerr << "ERROR IN REMOVE\n";
	exit(1);
    }

    Node* kill;
    kill = head;
    
    head = kill->next;
    v = kill->data;

    delete kill;
    size--;
    return v;
}

/*Does: prints a queue of orders
 *Arg: none
 *Returns: nothing
 *Calls: nothing
 *Notes: none
 */
void Queue::print(){
    Node* iter;
    iter = head;
    string cust = "regular";
    Order temp;
   
    while(iter != NULL){
	    
	temp = iter->data;
	
	cout << "Order " << temp.order_id << " for " << temp.cusType 
	<< " customer"" arrive at time " << temp.arrive << endl <<"fetch time "
	<< temp.fetch << " minutes, pack time " << temp.pack << " minutes\n" <<
	"elapsed" << " time sim1 " << temp.totalSim1 << " minutes, total time "
	"sim2 " << temp.totalSim2 << " minutes\n";
	cout << endl;
	
	iter = iter->next;
    }
}

/*Does: sends the order that is at the front of a queue
 *Arg: none
 *Returns: the order head is pointing to
 *Calls: nothing
 *Notes: does not alter queue
 */
Order Queue::get_head(){
	
    	return head->data;
	
}
//in both simulations the overall time is stored in the order under totalSim1,
//so in order to print correctly I just placed the orders that were in sim2's 
//total time into the orders who ran in sim1, but UNDER totalSim2
void Queue::combine(Queue rhs)
{
	Node* iter1 = head;
	Node* iter2 = rhs.head;
	
	while (iter1 != NULL && iter2 != NULL){
		iter1->data.totalSim2 = iter2->data.totalSim1;
		iter1 = iter1->next;
		iter2 = iter2->next;
	}
}
//finds the minimum order time
int Queue::min_time(){
	Node* iter = head;
	int temp;
	int min;
	
	if(iter != NULL)
	  min = iter->data.totalSim1;

	while(iter != NULL){
	  temp = iter->data.totalSim1;
	  if (temp < min) {
	    min = temp;
	  }
	  iter = iter->next;
	}
	return min;

}
//finds the maximum order time 
int Queue::max_time(){
	Node* iter = head;
	int temp;
	int max;
	
	if(iter != NULL)
	  max = iter->data.totalSim1;

	while(iter != NULL){
	  temp = iter->data.totalSim1;
	  if (temp > max) {
	    max = temp;
	  }
	  iter = iter->next;
	}
	return max;

}

int Queue::total(){
  Node* iter = head;
  int total = 0;
  
  while(iter != NULL){
    total = total + iter->data.totalSim1;
    iter = iter->next;
  }

  return total;
}

int* Queue::mean(){
  
  int total_s = 0;
  int count_s = 0;
  int total_r = 0;
  int count_r = 0;
  
  Node* iter = head;
  while(iter != NULL){
    if(iter->data.supreme){
      total_s = total_s + iter->data.totalSim1;
      count_s++;
    }
    else {
      total_r = total_r + iter->data.totalSim1;
      count_r++;
    }
    iter = iter->next;
  }
  
  return calculate_mean(total_s, count_s, total_r, count_r);
}

int* Queue::calculate_mean(int ts, int cs, int tr, int cr){
  //gets stored in an array so i can return all three means 
  int* means = new int[2];
  if (cs != 0 && cr != 0){
    means[0] = ts/cs;
    means[1] = tr/cr;
    means[2] = (tr+ts)/(cr+cs);
  }
  
  return means;
}
      
  
    
    
    
	
