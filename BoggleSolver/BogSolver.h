/*BogSolver.h
* Shea Clark-Tieche
* Comp15 Spring 2013
*
* Header file for bogsolver program. These are available functions to solve
* a boggle board and view the solutions
*/
#ifndef BOGSOLVER_H
#define BOGSOLVER_H

#include <iostream>
#include<string>
#include<cctype>
#include<cstdlib>
#include<stack>
#include<vector>
#include "BogWordList.h"
#include "Dictionary.h"

using namespace std;

struct BoardLet {
  BogLett let;
  bool visit;
};

class BogSolver
{
  public:
    BogSolver();
    ~BogSolver();
    bool readDict(); 	//reads in a dictionary
    bool readBoard(); 	//reads in a boggle board
    bool solve(); 	//finds all words in the board
    int numWords();	//returns the number of words in board
    int numWords(int len);	//returns number of words of len length
    BogWordList* getWords(); 	//returns list of BogWords
    BogWordList* getWords(int len); //returns list of Bogowrds of len length
    void printWords(); //prints words in HBF
    void printWords(int len); //prints words of len length in HBF
    void listWords(); //prints words in standard format 
    void listWords(int len); //prints words of len lenght in standard format
    
  private:
    Dictionary dict; //all possible words
    Dictionary inboard; //words currently in the boggle board
    BoardLet** board; //holds boggle board, 2d array of Boardlets
    BogWordList* list; //list of all BogWords
    int row; //number of rows in board
    int col; //number of columns in board 
    void solve(int, int, string, int*, int*); //recursive helper solve
    void addList(string, int*, int*); //adds a word to BogWordList
    int MAX_INT; //max current size of array of BogWords
    int max_word; //largest possible word based on size of board
    void init_board(); //resets board to all false
    void expand(); //expands array of BogWords
    void kill(); //does a deep delete of array of BogWords
};

#endif 







