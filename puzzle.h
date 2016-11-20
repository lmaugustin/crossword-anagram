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
  bool place(int w);
  void clear(int w);
  char get_letter_at(int r, int c, char blank);
  bool insert_word(int word_to_add, int word_to_intersect, int add_word_index, int intersect_word_index);
  void check_for_intersect(string s1, string s2, int &index1, int &index2);
  bool legal_word_spot(int word_to_add, int word_to_intersect,int row, int col, int dir);
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
