/*BogValidator.cpp
* Shea Clark-Tieche
* Comp15 Spring
*
* This program takes in user input and sees if they are valid solutions
* for a given boggle board. It operates in much of the same way as the
* solver solution. Essentially, it solves a boggle board using a dictionary
* of real words given by a user. It outputs either OK or NO before each word
* entered depending on if it's valid or not. The boggle board is solved by 
* iterating through each spot and recursing through each possible neighbor
* until all neighbors are invalid. 
*/

#include "BogValidator.h"

//default constructor sets all variables to default
BogValidator::BogValidator()
{
    max_word = 0;
    row = 0;
    col = 0;
    max_word = 0;
    board = NULL;
    
}

//default destructor does a deep delete of dynamic memory used,
//namely the boggle board which is a 2d dynamic array
BogValidator::~BogValidator()
{
  for (int j = 0; j < row; j++){
    delete [] board[j];
  }
  delete [] board;
}

//reads in a dictionary
//reads in a list of words until a centinal "." is read
//returns true unless there is not enough dynamic memory for the 
//dictionary to store all the words
bool BogValidator::readDict()
{
  string word = "";
  bool success = false;
  
  while (word != "."){
    cin >> word;
    success = dict.insert(word);
    if (success == false){
      return success;  //makes sure no problem inserting into dict
    }
  }
  
  return success;
}

//reads in a user specified board of dimensions col by row
//if the user did not provide enough letter for the board it will start 
//interpreting the user input as a board until it has entirely filled the
//amout of spots as specified by user. If file ends early, stops reading
//in data
bool BogValidator::readBoard()
{
  char input;
  int r = 0;
  int c = 0;
  bool success = false;

  cin >> row;
  cin >> col; 
  max_word = row*col; //largest possible word
  
  board = new BoardLet*[row];
  
  for (int i = 0; i < row; i++){
    board[i] = new BoardLet[col];  //creates new dynamic array for board
  }
  
  while (r != row && c != col && !cin.eof()){
    success = true;
    cin >> input;
    input = toupper(input);     //puts input in proper format
    board[r][c].visit = false;
    board[r][c].let.c = input;
    board[r][c].let.row = r;
    board[r][c].let.col = c;
    c++;   
    if (c == col){
      r++;
      c = 0;
    }
  }
  
  return success;
}

//checkWords takes a list of user provided words and verifies that they
// are either in the dictionary or not. This function uses two vectors and 
//three dictionaries as well as three helper functions
//it reads in a list of words until the file is at the end. In order to make
//sure the same word isn't input more than once, either by cin.eof() or the 
//user I have a dictionary of words that have already been verified and 
//is a word is in that dictionary it is automatically put on the array of 
//invalid words. Also checks to make sure word is composed of letters and 
//if not it's also thrown on the invalid array
void BogValidator::checkWords()
{
  string input;
  
  while(!cin.eof()){
    cin >> input;
    if(!isletts(input) && !done.isWord(input)){
      invalid.push_back(input);
      done.insert(input);
      continue;
    }
    input = to_upper(input);
    //stores a dictionary of potential words, i.e. they're real words
    //but unknown if they're in the board
    if(dict.isWord(input) && !done.isWord(input)){
      check.insert(input);
      potent.push_back(input); //uses this array to compare words that
			      //were stored in the potential dictionary
			      //to see if those words were found in bog board
    }
    else{
      invalid.push_back(input); //all other words are invalid
    }
    done.insert(input); //all words get put in done dictionary
  }
  validateWords(); //solves boggle board with dictionary of potential words
  compare(); //compares what words are found in board to what words were
	      //potential words 
}

//validateWords uses a dictionary of words that are real words and were input
//by the user to solve a boggle board. This is function calls solve which is
//a recursive function to walk through the board
bool BogValidator::validateWords()
{
  string test; 
  bool word = false;
  
  for (int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
	test = "";
	init_board();
	word = solve(i,j,test);
    }
  } 
 return word;
}  

//resets all spots in board to false for next walk through the board
void BogValidator::init_board()
{
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      board[i][j].visit = false;
    }
  }
}

//
// solve -- the recursive function 
//   args: (r,c) of the starting point
//         a string that stores the currect possible word
//   recurses through board checking each possible next square
//   builds a new string that it tests against a dictionary. If it's
//   in the dictionary and is greater that three letters it gets stored
//   in another dictionary of valid words 
bool BogValidator::solve(int r, int c, string test)
{
 
  bool pref = false;			// is a prefix is dflt to false
  bool word = false;                    // is a word defaults to false
  int up = r - 1;			// coords of neighbors
  int right = c + 1;
  int down = r +1;
  int left = c - 1;
  
  test += board[r][c].let.c;
  if (board[r][c].let.c == 'Q'){ //accounts for the special case of 'Qu'
   test += "U";
  }
  // add this letter to the string
  
  pref = check.isPrefix(test);	// see if the word so far is a prefix

  if (pref != true){ // if not a prefix, get out now, no hope
      return false;
  }		

  else {
    if (test.length() >= 3){
      word = check.isWord(test);
      if (word == true){
	valid.insert(test);  //if it's a word that user input AND it's
			     //in the board it gets stored in a dictionary 
			     //of valid words 
      }
    }
    board[r][c].visit = true;
    
    if (up >= 0 && !board[up][c].visit){
    	solve(up,c,test);
    }
    if (right < col && !board[r][right].visit){
        solve(r,right,test);
    }
    if (down < row && !board[down][c].visit){
    	solve(down,c,test);
    }
    if(left >= 0 && !board[r][left].visit) {
    	solve(r,left,test);
    }
    if(up >= 0 && right < col && !board[up][right].visit) {
	solve(up, right, test);
    }
    if(down < row && right < col && !board[down][right].visit){
	solve(down, right, test);
    }
    if(down < row && left >= 0 && !board[down][left].visit) {
    	solve(down, left, test);
    }
    if(up >= 0 && left >= 0 && !board[up][left].visit) {
	solve(up, left, test);
    }
    //no where else to go, set me back to false and lets go home
    board[r][c].visit = false;
  }
  return word;
}

//this fucntion compares the array of potential words with the dictionary
//that validateWords() has built. If a word is in the array, but not in the
//dictionary from validateWords() that means it's a real word but not in the
//board this function deals with outputing the proper messages using cout
//after all words have been found and output, the function then outputs the 
//invalid words 
void BogValidator::compare()
{
  int len = potent.size();
  for (int i = 0; i < len; i++)
    if(valid.isWord(potent[i])){ //if potential word was found OK!!
      cout << "OK " << potent[i] << endl;;
    }
    else {
      invalid.push_back(potent[i]); //if not it's invalid
    }
  for (unsigned int j = 0; j < invalid.size(); j++){
    cout << "NO " << invalid[j] << endl;;
  }
  
}

//this function checks the validity of one specific word and returns
//true if the word is in the board or false if not.
//it uses two dictionaries and validateWords() as a helper function
//it also uses the potential array 
bool BogValidator::isValid(string s)
{
  if(!isletts(s)){ //makes sure input is made up of alpha characters
      return false;
    }
  s = to_upper(s);
  if(dict.isWord(s)){ //sees if it's a real word, if so look in board
      check.insert(s);
      potent.push_back(s);
    }
    else {
      return false;
    }

  if (validateWords()){ //solves board with a dictionary of just that word
    return true;
  }
  else
    return false;
}

//makes a string entirely uppercase by iterating through string as array
//and then using cstdlib
string BogValidator::to_upper(string w)
{
  int len = w.length();
  
  for(int i = 0; i < len; i++){
    w[i] = toupper(w[i]);
  }
  
  return w;
}

//also iterates through a string as an array to see if it's made up 
//of only alpha characters. 
bool BogValidator::isletts(string w)
{
  int len = w.length();
  for (int i = 0; i < len; i++){
    if(!isalpha(w[i]))
      return false;
  }
  
  return true;
}
  











  
  
  
  
