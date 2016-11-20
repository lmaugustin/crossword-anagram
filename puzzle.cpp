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
  for(int i = 1; i < words.size(); i++) {  // Try to place words[i]
    for (int h = 0; h < i; h++) { // look at all previously placed words
      for (int a = 0; a < words[i].GetWord().length(); a++) {
	for (int b = 0; b < words[h].GetWord().length(); b++) {
	  if((words[i].GetWord())[a] == (words[h].GetWord())[b]) {
	    // Common letter between the two words.
	    // We are trying to place words[i]. The letter at position [a] in words[i]
	    // matches the letter at position [b] in words[h].  words[h] is already on the board.
	    if(words[h].direction == Word::HORIZONTAL) {
	      // Word already on the board words[h] is Horizontal
	      // word[i] must be vertical
	      words[i].col = words[h].col + b;
	      words[i].row = words[h].row - a;
	      words[i].direction = Word::VERTICAL;
	    } else {
	      // Word already on the board words[h] is Vertical
	      // word[i] must be horizontal
	      // TBD...
	    }
	  }
	}
      }
    }
  }
}

char Puzzle::get_letter_at(int r, int c, char blank) {
  int target;

  for(auto it = words.begin(); it != words.end(); it++) {
    if(it->direction == Word::HORIZONTAL) {
      if((it->row == r)) {
	// right row, look for the column letter
	target = c - (it->col);
	if ((target >= 0) && (target < it->GetWord().length())) {
	  if(blank == '.') {
	    return (it->GetWord())[target];
	  } else {
	    return ' ';
	  }
	}
      }
    } else { // Word is VERTICAL
      if((it->col == c)) {
	// right column, look for the row letter
	target = r - (it->row);
	if ((target >= 0) && (target < it->GetWord().length())) {
	  if(blank == '.') {
	    return (it->GetWord())[target];
	  } else {
	    return ' ';
	  }
	}
      }
    }
  }
  return blank;
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
      l = get_letter_at(r,c,'.');
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
      l = get_letter_at(r,c,'#');
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

void Puzzle::PrintClues(ostream &ostr) {
}
