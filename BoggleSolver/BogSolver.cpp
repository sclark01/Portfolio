/*BogSolver.cpp
* Shea Clark-Tieche
* Comp15 Spring 2013
* 
* This program was written to solve a boggle board. It uses a 2D dyanmic
* array to store all the letters in the board also keeping track of their
* coordinates. This program includes a dictionary against which it compares 
* all possible words in the boggle board to see if it's a valid solution. The
* program uses recursion to go through each spot on the board and use its 
* neighbors to build potential words. When words are found, they're stored
* in a dynamic array of BogWords which is made up of arrays of characters
*/

#include "BogSolver.h"
#include <string>

//Default Constructer
//initializes variables
BogSolver::BogSolver()
{
    MAX_INT = 100; //starting size of array of BogWords
    max_word = 0; //largest possible size of words
    list = new BogWordList; 
    list->words = new BogWord[MAX_INT]; //new array of bogwords
   
    list->numWords = 0; 
    //make sure there are no dangling pointers
    for (int i = 0; i < MAX_INT; i++){
      list->words[i].letts = NULL;
      list->words[i].numLetts = 0;
    }
    
    board = NULL;
    row = 0; 
    col = 0;
}

//destructer, destroys all memory in the heap 
BogSolver::~BogSolver()
{
  kill();
  delete list;
  for (int j = 0; j < row; j++){
    delete [] board[j];
  }
  delete [] board;
}

//reads in a dictionary of words
bool BogSolver::readDict()
{
  string word = ""; //temporary storage for word
  bool success = false;
  
  while (word != "."){ 		//centinal value for dictionary input
    cin >> word;
    success = dict.insert(word); //stores words in a Dictionary
    if (success == false){ 	//checks to make sure there's enough memory
      return success;
    }
  }
  
  return success;
  
}

//reads in a board of lets of size row by column
bool BogSolver::readBoard()
{

  char input;
  int r = 0;
  int c = 0;
  bool success = false;

  cin >> row; //number of rows
  cin >> col; //number of columns
  max_word = row*col; //largest possible word is all boxs
  
  board = new BoardLet*[row];
  
  for (int i = 0; i < row; i++){
    board[i] = new BoardLet[col]; //create 2d array
  }
  
  while (r != row){
    if(cin.eof()){
      cout << "NOT ENOUGH ROWS\n";  //makes sure that there are enough rows
      exit(1);  //exits program if user doesn't supply enough letters
    }
    success = true;
    cin >> input;
    input = toupper(input);
    board[r][c].visit = false; //makes board start clean
    board[r][c].let.c = input;
    board[r][c].let.row = r; 	//board stores all rows and columns
    board[r][c].let.col = c;
    c++;   
    if (c == col){
      r++;
      c = 0;
    }
  }
  
  return success;
}

//
// solve
//  go through whole array
//  for each square, send the coords into solve with an empty string
//  this is the public function which calls the recursive function 
bool BogSolver::solve()
{
  string test; 
  
  for (int i = 0; i < row; i++){  //iterates through each spot on board
    for(int j = 0; j < col; j++){
	int* posr = new int[max_word]; //creates an array that follows the
	int* posc = new int[max_word]; //word through recursion holding path
	if(posr == NULL || posc == NULL){
	  return false; //not enough memory 
	}
	test = ""; //reset test to empty string each time
	init_board(); //reset all spots to false
	solve(i,j,test, posr, posc); //recursion 
	delete [] posr;   //deletes slash resets arrays
	delete [] posc;
    }
  } 
 return true;
}  

//cleans board and sets all bool values back to false for next
//search throughout the board
void BogSolver::init_board()
{
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      board[i][j].visit = false;
    }
  }
}

//
// solve -- the real one that does recursion
//   args: (r,c) of the starting point
//         a string that stores a possible word
//   recurses through board checking each possible next square
//   builds a new string that it tests against a dictionary. If it's
//   in the dictionary and is greater that three letters it gets stored
//   in bogwordlist
void BogSolver::solve(int r, int c, string test, int* posr, int* posc){
 
  bool pref = false;			// is a prefix is dflt to false
			
  int up = r - 1;			// coords of neighbors
  int right = c + 1;
  int down = r +1;
  int left = c - 1;
  
  test += board[r][c].let.c;   //adds text character to string to build word

  //add this letter to the string
  int len = test.length();
  posr[len-1] = r;  //keeps track of coordinates of path through board
  posc[len-1] = c;
  
  if (board[r][c].let.c == 'Q'){
   test += "U";  //adds a U to the word if there's a "Q" proceeding it
   len++;
  }
  pref = dict.isPrefix(test);	// see if the word so far is a prefix

  if (pref != true){	 // if not a prefix, get out now, no hope
      return;
  }		

  else {
    if (len >= 3){  //ok to check for valid word
      if (dict.isWord(test)){  //checks to see if word is in dictionary
	addList(test, posr, posc); //stores words if in dictionary 
      }
    }
    board[r][c].visit = true;  //we are now officially looking at this square
			      // and its neighbors so set it to true
    //look at all the neighbors of this spot
    if (up >= 0 && !board[up][c].visit){
    	solve(up,c,test, posr, posc);
    }
    if(up >= 0 && right < col && !board[up][right].visit) {
	solve(up, right, test, posr, posc);
    }
    if (right < col && !board[r][right].visit){
        solve(r,right,test, posr, posc);
    }
    if(down < row && right < col && !board[down][right].visit){
	solve(down, right, test, posr, posc);
    }
    if (down < row && !board[down][c].visit){
    	solve(down,c,test, posr, posc);
    }
    if(down < row && left >= 0 && !board[down][left].visit) {
    	solve(down, left, test, posr, posc);
    }
    if(left >= 0 && !board[r][left].visit) {
    	solve(r,left,test, posr, posc);
    }
    if(up >= 0 && left >= 0 && !board[up][left].visit) {
	solve(up, left, test, posr, posc);
    }
    //theres nothing past this spot, set this spot to false, lets go back
    //up the path and keep looking 
    board[r][c].visit = false;
  }
  
}

//adds a word that has been found to the list of bogwords
//takes a word and that words array of coordinates as arguments 
//stores each word into BogWord list
void BogSolver::addList(string t, int* posr, int* posc)
{ 
    if(inboard.isWord(t)){
      return;  //checks to make sure it hasn't already been stored cause
		//if so there's no need to store it again 
    }
    else {
       inboard.insert(t); //adds word to dictionary that holds all words
			  //that have already been stored so we don't have
			  //add repeats into bogwordlist
    }
    int index = list->numWords; 
    int count = t.length();
    if(index >= MAX_INT-1){
      expand();   //expands array of bogwords if we've run out of room 
    }
    list->numWords = list->numWords + 1;
    list->words[index].letts = new BogLett[count];
    list->words[index].numLetts = count;
    for(int j = 0; j < count; j++) {
      list->words[index].letts[j].c = t[j];
      list->words[index].letts[j].row = posr[j];
      list->words[index].letts[j].col = posc[j];
      if (t[j] == 'Q' && j < count - 1 && t[j+1] == 'U'){
	list->words[index].letts[j+1].c = t[j+1];
	list->words[index].letts[j+1].row = posr[j];
	list->words[index].letts[j+1].col = posc[j];
	j++;  //if next let is U we've done the special case so skip two spots
      } 
    }
}

//returns the number of words currently stored 
int BogSolver::numWords()
{
  return list->numWords;
}

//returns the number of words of a certain length currently stored
int BogSolver::numWords(int len)
{
  int count = 0;
  
  for(int i = 0; i < list->numWords; i++){
    if(list->words[i].numLetts == len){
      count++;
    }
  }
  return count;
}

//returns actual list of BogWords
BogWordList* BogSolver::getWords()
{
  return list;
}

//returns a new list of bogwords of a certain length
BogWordList* BogSolver::getWords(int len)
{
  BogWordList* temp;
  temp = new BogWordList;
  temp->words = new BogWord[MAX_INT];
  temp->numWords = 0;
  
  for(int i = 0; i < list->numWords; i++){
    if(list->words[i].numLetts == len){
	 temp->words[temp->numWords].letts = list->words[i].letts;
	 temp->words[temp->numWords].numLetts = len;
	 temp->numWords++;
    }
  }
  
  return temp;
}

//prints the words in HBF format 
//special case for 'Q' makes sure that q & u get output together with
//only one coordinates pair
void BogSolver::printWords()
{
  for (int i = 0; i < MAX_INT; i++){
    if(list->words[i].letts != NULL){
      cout << "< ";
      int len = list->words[i].numLetts;
      
      for (int j = 0; j < len; j++){
	cout << list->words[i].letts[j].c; 
	if(list->words[i].letts[j].c == 'Q' && j < (len -1) && 
	  list->words[i].letts[j+1].c == 'U'){
	  continue;
	}
	cout << " " << list->words[i].letts[j].row << " ";
	cout << list->words[i].letts[j].col << " ";
      }
      cout << ">" << endl;
    }
  }
  cout << "< >" << endl;
}

//prints only the words of a certain length in HBF format
//follows the same special case as above 
void BogSolver::printWords(int len)
{
  for (int i = 0; i < MAX_INT; i++){
    if(list->words[i].numLetts == len){
      cout << "< ";
      int len = list->words[i].numLetts;
      for (int j = 0; j < len; j++){
	cout << list->words[i].letts[j].c << " ";
	if(list->words[i].letts[j].c == 'Q' && j < (len -1) && 
	  list->words[i].letts[j+1].c == 'U'){
	  continue;
	}
	cout << list->words[i].letts[j].row << " "; 
	cout << list->words[i].letts[j].col << " ";
      }
      cout << ">" << endl;
    }
  }
  cout << "< >" << endl;
}

//prints all words in a readable format
//no need for any special cases 
void BogSolver::listWords()
{
  for (int i = 0; i < MAX_INT; i++){
    if(list->words[i].letts != NULL){
      for (int j = 0; j < list->words[i].numLetts; j++){
	cout << list->words[i].letts[j].c; 
      }
      cout << endl;
    }
  }
}

//prints words of a certain user specified length in a readable format
void BogSolver::listWords(int len)
{
  for (int i = 0; i < MAX_INT; i++){
    if(list->words[i].numLetts == len){
      for (int j = 0; j < list->words[i].numLetts; j++){
	cout << list->words[i].letts[j].c; 
      }
      cout << endl;
    }
  }
}

//expands array of bogwords by doing a deep copy
//makes sure all memory is deleted at the end
//sometimes leaks about 1 or 2 blocks of memory, but i'm not sure why
//because I thought I deleted all memory
void BogSolver::expand()
{
  int new_max = MAX_INT + 10; //increases max int by 10
  
  BogWordList* temp = new BogWordList;
  temp->numWords = list->numWords;
  temp->words = new BogWord[new_max];
  
  for(int i = 0; i < new_max; i++){
    if(i < MAX_INT){
      int len = list->words[i].numLetts;
      temp->words[i].letts = new BogLett[len];
      for(int j = 0; j < len; j++){
	temp->words[i].letts[j] = list->words[i].letts[j];
      }
      temp->words[i].numLetts = list->words[i].numLetts;
    }
    else {
      temp->words[i].letts = NULL;
      temp->words[i].numLetts = 0;
    }
  }
  kill();  //kills old memory by doing a deep delete
  delete list; //get rid of everything list was pointing to 
  list = temp;  //sets list to what temp is now pointing to 

  MAX_INT = new_max; //sets MAX_INT to new size of array
  
}

//does a deep delete of what BogWordlist and it's memebers point to 
void BogSolver::kill()
{
  for (int i = 0; i < MAX_INT; i++){
    delete [] list->words[i].letts;
  }
  delete [] list->words;
}

  

  

  
  
  
  
  
  
  
  
  
  



