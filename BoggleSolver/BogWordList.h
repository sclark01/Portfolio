/*bogWordList.h
*/
#ifndef BOGWORDLIST_H
#define BOGWORDLIST_H

struct BogLett {
  char c;
  int row;
  int col;
};

struct BogWord{
  int numLetts;
  BogLett* letts;
};

struct BogWordList{
  int numWords;
  BogWord* words;
};

#endif



