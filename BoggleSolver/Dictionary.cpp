/*dictionary.cpp
*Comp15 Spring 2013
*Name: Shea Clark-Tieche
*Date: 2 April 2013
*This program uses a Trie to store a dictionary of words. It also checks to
see if a user given word is a prefix or a word of any of the dictionary 
entries. 
*/

#include "dictionary.h"

//Default constructor creates the root TrieNode
Dictionary::Dictionary()
{
	root = new TrieNode;
	root->word = false;
	for (int i = 0; i < NUM_LETTERS; i++){
		root->Children[i] = NULL;
	}
	isEmpty = true;
}

//function called by user to insert a string into the dictionary. returns
//true if the word was stored 
bool Dictionary::insert(string s)
{
	if (isEmpty == true){ //only happens once, on first insert
		isEmpty = false;
	}
	bool success = false;
	int* word = getWord(s); //converts string to array of ints
	int i = 0; //index for recursive function 
	
	success = insert(root, word, i);
	delete [] word;
	
	return success;
}

//recursively words through Trie. When it reachs the last spot it sets that
//root to true to indicate that a word is stored there. returns true if word
//was inserted correctly, false if not enough memory 
bool Dictionary::insert(TrieNode* r, int* w, int i)
{
	int index = w[i]; //stores currect "character" being insert
	i++;
	TrieNode* next;
	if (index == END_WORD){ //indicates the end of the word 
		r->word = true;
		return true;
	}
	else if(r->Children[index] == NULL){
		next = new TrieNode;
		if (next == NULL) { //makes sure there is enough memory 
			return false;
		}
       init(next); //not having this was giving me unconditional jumps, but 
      //adding it causes my program to run A LOT slower, probably because
      //it's a loop
		r->Children[index] = next;
		return insert(next, w, i);
	}
	else {
		next = r->Children[index];
		return insert(next, w, i);
	}
}

//function a user calls to see if a string is a prefix of any of the words
//stored in the dictionary. returns true if prefix is found.
bool Dictionary::isPrefix(string s)
{
	bool success = false;
	int* word = getWord(s);
	int index = 0;
	//checks to see if the empty string is being searched for
	if ((word[index] == END_WORD) && !isEmpty){
		delete [] word;
		return true;
	}
	success = isPrefix(root, word, index);
	delete [] word;
	return success;
}

//recursive function to go through Trie to find if a word is a prefix. 
//Returns true when the Trie continues on, but the string is at the end 
//(i.e. their is no next "character"). returns true if prefix is found.
bool Dictionary::isPrefix(TrieNode* r, int* w, int i)
{
	int index = w[i];
	i++;
	if(r->Children[index] != NULL){
		if(w[i] == END_WORD){ 
			return true;
		}
		else {
			return isPrefix(r->Children[index], w, i);
		}
	}
	else {
		return false;
	}
}

//function a user calls to see if a word is in the dictionary. returns true
//if the word is found
bool Dictionary::isWord(string s)
{
	bool success = false;
	int* word = getWord(s);
	int index = 0;
	//checks to see if the empty string is being searched for AND the
	//empty string has been inserted
	if ((word[index] == END_WORD) && root->word == true){
		delete [] word;
		return true;
	}
	success = isWord(root, word, index);
	delete [] word;
	return success;
}

//recursive function that goes through the Trie to see if a word is stored
//in it. Returns true when it sees that it is a terminal point (word equals
//true) AND it's on the last character in the word being searched for. 
//returns true if the word is found 
bool Dictionary::isWord(TrieNode* r, int* w, int i)
{
	int index = w[i];
	i++;
	if(r->Children[index] != NULL){
		TrieNode* next = r->Children[index];
		if((next->word == true) && w[i] == END_WORD){
			return true;
		}
		else {
			return isWord(next, w, i);
		}
	}
	else 
		return false;
}

//turns a string into an array of ints, each int corresponds to 0-25 (a-z)
//so each word is now represented as an array of ints, the letters being
//their int value. The array is one larger than the string and the final 
//location is set to the senital value, -1. Returns pointer to array.
int* Dictionary::getWord(string s)
{
	s = cleanWord(s);
	int len = s.length();
	int* Word = new int[len + 1];
	for (int i = 0; i < len; i++){
		Word[i] = charToInt(s[i]);
	}
	Word[len] = END_WORD;
	return Word;
}

//takes out all non-alpha characters from a string and returns the new, 
//clean string 
string Dictionary::cleanWord(string s)
{
  int len = s.length();
  string clean;
  for(int i = 0; i < len; i++) {
    if (isalpha(s[i]) != false) {
      clean += tolower(s[i]);
    }
  }
  
  return clean;
}
		
//converts a character into an integer 
int Dictionary::charToInt(char c)
{
	return (c - 'a');
}

//wrote this function so that I can set every new node's Children equal to
//but if I used it, it cause my program to run increadibly slow.
void Dictionary::init(TrieNode* tn)
{
	tn->word = false;
	for(int i = 0; i < NUM_LETTERS; i++){
		tn->Children[i] = NULL;
	
	}
}

int Dictionary::num_words()
{
    int count = 0;
    
    return  num_words(root, count);
    
}

int Dictionary::num_words(TrieNode* r, int count)
{
    if (r->word == true) {
	count++;
    }
    for (int i = 0; i < NUM_LETTERS; i++){
	    if(r->Children[i] != NULL){
		count = num_words(r->Children[i], count); 
	    }
    }
    return count;
}
/*
void Dictionary::print()
{
    string head = "";
    print(head, root);
}

void Dictionary::print(string head, TrieNode* r)
{
     if (r == NULL) {
	return;
    }

     if (r->word == true) {
	 cout << head << endl;
	 head = "";
     }

    TrieNode* next = NULL;
    for (int ){
	if (r->Children[i] != NULL){
	    next = r->Children[i];
	    head +=  toChar(i);
	    print(head, r->Children[i]);
	}
     }
}
*/
char Dictionary::toChar(int i){
    return alphabet[i];
}


