/*BogValidator.h
* Shea Clark-Tieche
* Comp15 Spring 2013
*
* This is the header file for my validtor function. These are the available
* functions to validate user input in a boggle board and get the results
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "BogSolver.h"
#include "Dictionary.h"

using namespace std;

class BogValidator
{
  public:
    BogValidator();
    ~BogValidator();
    bool readDict(); //takes in a main dictionary to determin real words
    bool readBoard(); //reads in a boggle board of specified size
    bool isValid(string s); //checks to see if a given string is valid
    void checkWords(); //validates a list of user input words
    
  private:
    Dictionary dict; //stores the main dictionary for determining real words
    Dictionary check; //stores a dictionary of potential words for board
    Dictionary valid; //stores words found in board from potential dictionary
    Dictionary done; //stores all words that have been checked to stop repeats
    int row; //num rows in board
    int col; //num columns in board
    int max_word; //size of largest possible word
    BoardLet** board; // variable for dynamic 2d array to store board
    vector<string> invalid; //array of bad words
    vector<string> potent; //array of potential words to comapre to valid dict
    bool validateWords(); //validates word by calling recursive function
    bool solve(int, int, string); //solves boggle board with possible words
    void init_board(); //resets all spots on board to false
    void compare(); //compares potential words with words found 
    string to_upper(string); //converts string to all uppercase
    bool isletts(string); //verifies string is only alpha characters
};