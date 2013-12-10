/*pack_manager.cpp
*Shea C-T
 */



#include "pack_manager.h"
#include <iostream>



const int NUM_PACKERS = 3;

PackManager::PackManager(){
	packers = new Packer[NUM_PACKERS];
}
//this way the packers will be clean for sim2
void PackManager::restart(){
	packers = new Packer[NUM_PACKERS];
	post_pack.restart();
	cur_time = 0;
	
}
//how an order is added to a packer 
void PackManager::get_order(Order toPack){
	int index = 0;
	//finds packer with shortest wait time 
	index = find_shortest(toPack.supreme);
	packers[index].add(toPack);
	
}
//hub for all the packer functions
void PackManager::run(int t){

	Order test;

	//run each packer
	for (int i = 0; i < NUM_PACKERS; i++){
		//set time in each packer to current time being run
		packers[i].set_time(t);
		//check to see if package needs to be picked up
		while (packers[i].done_pack() && packers[i].getInProcess()){
			//if so say true, so main manager knows 
			//gets package from the packer
			post_pack.insert(packers[i].get_pack());	
		}
		
		//makes sure that if something was removed, it isnt empty now
		if(!packers[i].isEmpty()){
		    packers[i].packing(false);
		    packers[i].check_sup();
		    packers[i].adjust_time();
		}
	}
	
}	

int PackManager::find_shortest(bool sup){
  //obviously, this keeps the condition from ever working. I did
  //this because I could never get it to work without really messing up
  //my numbers and program, so i essentially commented it out, but with more
  //time I would like to try to implement it better
	sup = false;
	int index = 0;
      if (!sup){
	int shortest = packers[0].wait();
	int temp = 0;
	int i = 0;
	  for (i = 0; i < NUM_PACKERS; i++){
		temp = packers[i].wait();
		if (temp < shortest) {
			shortest = temp;
			index = i;
		}
	  }
	}
	else
	  index = supreme_shortest();
	
	return index;
	
}
// this fuction is never actually called (see above), but i would like 
// to at some point correctly implement it 
int PackManager::supreme_shortest(){
	int shortest = packers[0].sup_wait();
	int temp = 0;
	int i = 0;
	int index = 0;
  for (i = 0; i < NUM_PACKERS; i++){
    temp = packers[i].sup_wait();
	if (temp < shortest) {
		shortest = temp;
		index = i;
	}
  }
  return index;
}
//lets manager know if there are any orders that have been completed that 
//need to be sent to the manager
bool PackManager::post_isEmpty(){
	if (post_pack.is_empty()){
		return true;
	}
	else
		return false; 
}
 
 Order PackManager::grab_order(){
	 return post_pack.remove();
 }
 
 bool PackManager::isEmpty(){
	 
	 for (int i = 0; i < NUM_PACKERS; i++){
		 if (!(packers[i].isEmpty() && !packers[i].getInProcess())) {
			 return false;
		 }
	 }
	 return true;
 }
 
 void PackManager::printer()
 {
	 post_pack.print();
 }
 
 void PackManager::print(){
 for (int i = 0; i < 3; i++){
      packers[i].print();
      }
}
	

