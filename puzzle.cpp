#include "puzzle.h"
#include <iomanip>

Puzzle::Puzzle() {
  words.reserve(20);
}

void Puzzle::ReadWords(istream &istr) {
  // Read input from istr and store the words read from the input into the words array
  // Insert the words so that they are stored ordered by descending length.  e.g. words[0] is the longest
  // word, words[1] is the next longest word, etc. until words.back() is the shortest word.
  // Convert words to all upper case as they are read in and stored.

  /*
   * Dummy test data remove when real function is written
   */
  words.push_back(Word("BASEBALL"));
  words.push_back(Word("SMELL"));
  words.push_back(Word("ARTSY"));
  words.push_back(Word("YELL"));
  /*
   * End dummy test data
   */
}

void Puzzle::Generate() {       // Place words on the puzzle.
  // Assume that the words array is ordered from largest word to smallest word.
  // Place the first (longest) word in the center of the board
  words[0].col = (Puzzle::COLS - words[0].GetWord().length()) / 2;
  words[0].row = Puzzle::ROWS / 2;
  words[0].direction = Word::HORIZONTAL;
}

char Puzzle::get_letter_at(int r, int c) {
  int rows, cols;

  return '.';
  
  for (rows = 0; rows < Puzzle::ROWS; rows++) {
    for (cols = 0; cols < Puzzle::COLS; cols++) {
      for(auto it = words.begin(); it != words.end(); it++) {
	//	if(it->
      }
    }
  }
}

void Puzzle::PrintSolution(ostream &ostr) {  // Print the solution
  int r, c;
  char l;

  ostr << "    ";
  for(c = 0; c < Puzzle::COLS; c=c+10) {
    ostr << c/10;
    ostr << "         ";
  }
  ostr << endl;

  ostr << "    ";
  for(c = 0; c < Puzzle::COLS; c++) {
    ostr << c%10;
  }
  ostr << endl;

  ostr << "   -";
  for(c = 0; c < Puzzle::COLS; c++) {
    ostr << '-';
  }
  ostr << '-' << endl;
  
  for(r = 0; r < Puzzle::ROWS; r++) {
    ostr << setfill(' ') << setw(3) << r << "|";
    for(c = 0; c < Puzzle::COLS; c++) {
      l = get_letter_at(r,c);
      ostr << l;
    }
    ostr << '|' << endl;
  }
  ostr << "   -";
  for(r = 0; r < Puzzle::ROWS; r++) {
    ostr << '-';
  }
  ostr << '-' << endl;
}

void Puzzle::PrintPuzzle(ostream &ostr) {
}

void Puzzle::PrintClues(ostream &ostr) {
}
