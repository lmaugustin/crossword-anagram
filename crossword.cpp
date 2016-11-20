
/*
 * Overall main flow:
 *
 * 1. Read list of words from input
 * 2. Build anagram puzzle by placing words onto the puzzle
 * 3. Display the solution showing all words placed
 * 4. Display the unsolved puzzle
 * 5. Generate the anagram clues
 * 6. Display the anagram clues.
 *
 * Primary data structures:
 *
 * class Word
 *   This is one anagram word in the puzzle.
 * class Puzzle
 *   This is a puzzle.  A puzzle is primarily a list of words.
 *
 */

#include "puzzle.h"
#include <iostream>

int main() {
  Puzzle P;

  cout << "Anagram Crossword Puzzle Generator" << endl;
  cout << "----------------------------------" << endl << endl;
  cout << "Enter a list of up to 20 words.  A '.' on a line by itself ends the list.  A word may be at most 15 letters." << endl;
  P.ReadWords(cin);
  P.Generate();
  cout << endl << "Solution:" << endl << endl;
  P.PrintSolution(cout);
  cout << endl << "Crossword Puzzle:" << endl << endl;
  P.PrintPuzzle(cout);
  cout << endl << "Clues:" << endl << endl;
  P.PrintClues(cout);

  return 0;

}
