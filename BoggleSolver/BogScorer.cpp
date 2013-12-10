/*BogScorer.cpp
* Shea Clark-Tieche
* Comp15 Spring 2013
*
* This program takes the output produced by bogValidator to correctly
* count the number of words and count the score based on the proper boggle 
* rules.
*/

#include "BogScorer.h"

//default constructer
BogScorer::BogScorer()
{
  num_words = 0;
  tot_score = 0;
}

//no dynamic memory to delete
BogScorer::~BogScorer()
{
}

//this function scores the word. if a word has a "NO" infront it is
//invalid and automatically recieves 0 points. Other valid words are 
//scored based on the number of lets, up to 8 after which they recieve 11 
//points as the max. 
void BogScorer::score()
{
  string valid;
  string word;
  string prev = "";
  int invalid = 0;
  
  while(!cin.eof()){
    cin >> valid; //whether word is valid or not
    cin >> word; //actual word
    if(word == prev){
      continue; //makes sure input from cin.eof() does not double at end
    }
    prev = word;
    if (valid == "OK"){
      num_words++; //counts number of words
      points(word); //actually scores the word based on length 
    }
    else 
      cout << invalid << " NO " << word << endl;
  }
  cout << num_words << " words " << tot_score << " points\n";
}

//this function uses a static array to assign point based on number of 
//letters in the word. It returns the number of point to assign
void BogScorer::points(string w)
{
  int len = w.length();
  int score = 0;
  
  if (len > 8){
    score = 11;
  }
  else {
    score = values[len]; //currect value for num points is stored in array
  }
  tot_score += score;
  cout << score << " OK " << w << endl; //outputs OK and number points
}
  
      
    
