/*BogScorer.h
* Shea Clark-Tieche
* Comp15 Spring 2013
*
* This is the header file for the bogscorer program. It uses a static
* array with the point values stored where the index is the length of the
* word to assign points. These are available functions
*/

#include <iostream>
#include <string>

using namespace std;

static const int values[9] = {0,0,0,1,1,2,3,5,11};

class BogScorer
{
  public:
    BogScorer();
    ~BogScorer();
    void score(); //scores the word
  private:
    int num_words; //number of words that are valid
    int tot_score; //overall total score
    void points(string); //actually counts letters to assign points
};