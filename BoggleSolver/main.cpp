/*main.cpp
*/

#include "dictionary.h"

int main(){
  Dictionary h;
  string find_x;
  string test;
  
  while(!cin.eof()){
	  cin >> test;
	  h.insert(test);
} 
/*
  h.insert("dogma");
  h.insert("dog");
  h.insert("");
  test = "  **dog  9898ma";
  	*/
//  h.print();
  cout << "Num Words: " << h.num_words() << endl;
  if (h.isWord(test)){
    cerr << "Word: True\n";
  }
  else {
    cerr << "Word: False\n";
  }
    
  if (h.isPrefix(test)){
    cerr << "Prefix: True\n";
  }
  else {
    cerr << "Prefix: False\n";
} 
  return 0;
}


