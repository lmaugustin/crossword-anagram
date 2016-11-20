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
 private:
  char get_letter_at(int r, int c, char blank);
  bool try_to_place_word(int w);
  void check_for_intersect(string s1, string s2, int &index1, int &index2);
  bool legal_word_spot(int w, int r, int c, int d);
};

class Pair {
 public:
  Pair() {};
  ~Pair() {};
  int x, y;
  Pair(int a, int b) { x=a; y=b;};
};

typedef vector<Pair> pair_array_t;

#endif
