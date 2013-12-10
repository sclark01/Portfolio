/*queue.h
 *Comp15, Spring 2013
 *Project 1
 *Name: Shea Clark-Tieche
 *Notes: Creates a linked list of Nodes.
 */
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdlib.h>

using namespace std;

//contains all the data for an order
struct Order {
    int order_id;
    string cusType;
    int arrive;
    int fetch;
    int pack;
    int totalSim1;
    int totalSim2;
    int interuption;
    bool supreme;
};
//The node for the linked list
struct Node {
  Order data;
  Node* next;
};

class Queue {

public:

    //default constructor
    Queue();
    //resets a queue to original values
    void restart();
    //puts node on the queue  
    void insert(Order);
    //removes an order from the queue and returns it
    Order remove();
    //inserts an Order to the front of the queue
    void insertFront(Order);
    //checks to see if the queue is empty
    bool is_empty();
    //returns the size of the queue
    int size_queue();
    //prints a given queue
    void print();
    //gives order at front of queue
    Order get_head();
    //adds sim2 times to orders
    void combine(Queue);
    //finds shortest time
    int min_time();
    //finds longest time
    int max_time();
    //returns the total processing time
    int total();
    //returns mean when supreme is running
    int* mean();
    
    

private:

    Node* head;
    Node* tail;
    //number of elements in the queue
    int size;
    //calculates the means for the different order types and returns 
    //an array that holds all these values
    int* calculate_mean(int, int, int, int);

};
#endif
