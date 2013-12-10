/*dictionary.h
* Comp15 Spring 2013
* Name: Shea Clark-Tieche
* Date: 2 April 2013
*/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <cctype>

using namespace std;

//number of letters in the alphabet
static const int NUM_LETTERS = 26;
//indicates the end of a word
static const int END_WORD = -1;
//holds the alphabet
static const char alphabet[NUM_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g',
					   'h', 'i', 'j', 'k', 'l', 'm', 'n',
					   'o', 'p', 'q', 'r', 's', 't', 'u',
					    'v','w','x', 'y', 'z'};

struct TrieNode {
	//true if it contains a complete word
	bool word;
	TrieNode* Children[NUM_LETTERS];
};

class Dictionary {
	
	public:
		//default constructor
		Dictionary();
		//adds words to the dictionary
		bool insert(string);
		//checks to see if a string is a prefix of a word
		bool isPrefix(string);
		//checks to see if a word is in the dictionary
		bool isWord(string);
		//returns the number of words in the dictioary
		int num_words();
		//prints out a word in int form
		void print();

	private:
		//points to root TrieNode
		TrieNode* root;
		//says if dictionary is empty or not
		bool isEmpty;
		
		//recursively inserts a word into trie
		bool insert(TrieNode*, int*, int);
		//recursively checks if string is a prefix
		bool isPrefix(TrieNode*, int*, int);
		//recursively checks if word is in dictionary 
		bool isWord(TrieNode*, int*, int);
		//converts strings into array of ints
		int* getWord(string);
		//eliminates all non-alpha characters in string
		string cleanWord(string);
		//converts a character to a string
		int charToInt(char);
		//sets the children of a TrieNode to NULL
		void init(TrieNode*);
		//returns the number of words in the dictionary
		int num_words(TrieNode*, int);
		void print(string, TrieNode*);
		//takes an int and converts it to a character
		char toChar(int);
};

#endif


