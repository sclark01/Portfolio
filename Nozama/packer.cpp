/*packer.cpp
*Shea C-T
 */


#include "packer.h"


#include <iostream>
//initializes all values
Packer::Packer()
{
	wait_time = 0;
	queue_time = 0;
	time_remaining = 0;
	pack_avail = 0;
	in_process = false;
	wait_sup = 0;
	reg_wait = 0;
	cur_time = 0;
}

void Packer::add(Order toAdd)
{
//keeps track of seperate wait times for each type of order
	if(toAdd.supreme == true){
		pack_line.insertFront(toAdd);
		wait_sup = wait_sup + toAdd.pack;
	}
	else {
		pack_line.insert(toAdd);
		reg_wait = reg_wait + toAdd.pack;
	}
	
	wait_time = wait_sup + reg_wait;
}
//lets pacMan know that an order is ready for pick-up
bool Packer::done_pack()
{
	if (cur_time >= pack_avail && (!isEmpty() || getInProcess())) 
		return true;
	else
		return false;
}
//sends the order being processed back to pacMan
Order Packer::get_pack ()
{
	in_process = false; //nothing is being processed
	
	return process;
}
//when a packer is available to pack, this function sends it!
void Packer::packing(bool sup){

	if (sup || (!getInProcess() && cur_time >= pack_avail)){
		process = pack_line.remove();
		//accounts for an order that may have been interupted
		pack_avail = cur_time + (process.pack - process.interuption);
		in_process = true;
  	}
  	
}
//so that wait time can be accessed publicly 
int Packer::wait() 
{
	return wait_time;
}
//makes supreme wait public
int Packer::sup_wait()
{
  return wait_sup;
}

void Packer::adjust_time()
{
	//accounts for the fact that the time till pack finishes is less
	if (wait_time > 0) {
	  wait_time = wait_time - 1; 
	}
	if (wait_sup > 0) {
	  wait_sup = wait_sup - 1;
	}
	if (reg_wait > 0) {
	  reg_wait = reg_wait -1;
	}
}

bool Packer::isEmpty()
{
	if(pack_line.is_empty()) {
		return true;
	}
	else {
		return false;
	}
}
//finds out if there is a supreme order at the front of the queue and if
//so it stops whatever is being processed and begins processing supreme order
void Packer::check_sup()
{
	Order temp;
	Order wait;
	bool overide = true;
	
	if (isEmpty()){
	  return;
	}
	temp = pack_line.get_head();

	if(temp.supreme == true && process.supreme != true){
		
		wait = process;
		//keeps track of time remaing for interupted order 
		wait.interuption = pack_avail - cur_time;
		packing(overide);
		//doesnt send interupted to the back of the queue
		pack_line.insertFront(wait);
	}
}
		
void Packer::set_time(int t)
{
	cur_time = t;
	
	
}
		
bool Packer::getInProcess()
{
	if (in_process == true)
		return true;
	else
		return false;
}


void Packer::print() {

pack_line.print();
}
		


	
	
