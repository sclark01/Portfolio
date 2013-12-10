/*solverMain.cpp
* Shea Clark-Tieche
* Comp15 Spring 2013
* Main File for bogsolving program. made to interface with website:
* http://www.cs.tufts.edu/~sclark01/bog15
*/

#include "BogSolver.h"

int main()
{
  BogSolver solver;
  
  solver.readDict();
  solver.readBoard();
  solver.solve();
  solver.printWords();
  solver.listWords();
 
  return 0;
}



