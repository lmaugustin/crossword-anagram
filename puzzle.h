#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <string>
#include <istream>
#include "word.h"

using namespace std;

typedef vector<Word> word_array_t;

class Puzzle {
 public:
  Puzzle();
  ~Puzzle() {};
  static const int ROWS = 15;
  static const int COLS = 15;
  word_array_t words;
  void ReadWords(istream &istr);
  void Generate();                    // Place words on the puzzle.
  void PrintSolution(ostream &ostr);  // Print the solution
  void PrintPuzzle(ostream &ostr);
  void PrintClues(ostream &ostr);
  char get_letter_at(int r, int c, char blank);
};


#endif
