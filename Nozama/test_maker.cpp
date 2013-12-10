/* Aaron Tietz
 * Comp 15, Spring 2013
 * Test generator for proj1
 * 
 *   I'm giving you this to show you that coming up with test data is easy in 
 *  the hopes you'll start to do it yourself. The hard part is proving your 
 *  output is correct when you run your program on the test data.  Try making 
 *  small files (NUM_PACKAGES == 5) and working things out by hand.
 *
 * after compiling, to make a file run: ./a.out > test_file_x.txt
 */

#include <iostream>
#include <cstdlib>
using namespace std;
const int FETCH_RANGE  = 5;
const int PACK_RANGE   = 20;
const int TIME_RANGE   = 5;
const int NUM_PACKAGES = 5;

int main(){
 srand (time(NULL));
 int fetch, pack;
  int time = 0;
  for(int i = 1; i <= NUM_PACKAGES; i++){
    fetch = rand() % FETCH_RANGE + 1;
    pack  = rand() % PACK_RANGE + 1;
  
    if(i % 2 == 0){
    cout << "Order " << i << " for supreme customer arrived at time " << time 
         << "\nfetch time " << fetch << " minutes, pack time " << pack << " minutes\n\n";
    }
    else{
    cout << "Order " << i << " for regular customer arrived at time " << time
         << "\nfetch time " << fetch << " minutes, pack time " << pack << " minutes\n\n";   
    }
    time += rand() % TIME_RANGE + 1;
  }
  return 0;
}
