/*checkerMain.cpp
* Shea Clark-Tieche
* Comp15 Spring 2013
* Main File for program to verify that user input is a valid solution for a
* boggle board. Made to interface with website:
* 	http://www.cs.tufts.edu/~sclark01/bog15
*/

#include "BogValidator.h"

int main()
{
  BogValidator v;
  
  v.readDict();
  v.readBoard();
  v.checkWords();

  return 0;
}
