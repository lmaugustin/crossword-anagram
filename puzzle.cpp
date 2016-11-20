#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "puzzle.h"

using namespace std;

Puzzle::Puzzle() {
  words.reserve(20);
}

pair_array_t *letter_matches(string s1, string s2) {
  pair_array_t *v;
  v = new pair_array_t;

  for (int a = 0; a < s1.length(); a++) {
    for (int b = 0; b < s2.length(); b++) {
      if(s1[a] == s2[b]) {
	v->push_back(*(new Pair(a,b)));
      }
    }
  }
  return v;
}

void Puzzle::ReadWords(istream &istr) {
  // Read input from istr and store the words read from the input into the words array
  // Insert the words so that they are stored ordered by descending length.  e.g. words[0] is the longest
  // word, words[1] is the next longest word, etc. until words.back() is the shortest word.
  // Convert words to all upper case as they are read in and stored.
  string theline;
  bool inserted;
  
  while(true) {
    getline(istr, theline);
    inserted = false;
   
    if(theline[0] == '.') {
      return;
    }
    for(int i = 0; i < theline.size(); i++) { theline[i] = toupper(theline[i]); }
    if (words.size() == 0) {
      words.push_back(*(new Word(theline)));
    } else {
      for (auto io = words.begin(); io != words.end(); io++) {
	if(io->GetWord().size() <= theline.size() ) {
	  words.insert(io, *(new Word(theline)) );
	  inserted = true;
	  break;
	}
      }
      if( ! inserted) { // append to the very end
	words.push_back(*(new Word(theline)));
      }
    }
  }
}

bool Puzzle::place(int w) {
  pair_array_t *pa;

  if(w >= words.size()) return true;

  // For debugging purposes...
  // cout << "Trying to place: " << words[w].GetWord() << endl;
  // PrintSolution(cout);

  for(int i = 0; i < w; i++) { // for every word already on the board
    pa = letter_matches(words[w].GetWord(), words[i].GetWord());  // for every letter of intersection with one of those words
    for(auto it = pa->begin(); it != pa->end(); it++) {
      if(insert_word(w, i, it->x, it->y)) {  // try to insert the new word at that point on the board
	if(place(w+1)) return true;          // if it works try inserting the remainder of the words
      }
      clear(w); // make sure to clear this word and any unplaced words from the board before trying again
    }
  }

  return false;
}

void Puzzle::clear(int w) {
  for(int i = w; i < words.size(); i++) {
    words[i].row = -1;
    words[i].col = -1;
    words[i].direction = Word::NOT_ON_PUZZLE;
  }
}

bool Puzzle::insert_word(int word_to_add, int word_to_intersect, int add_word_index, int intersect_word_index) {
  int row, col;
  
  if(words[word_to_intersect].direction == Word::HORIZONTAL) {
    // Word already on the board words[word_to_intersect] is Horizontal
    // word[w] must be placed vertically
    col = words[word_to_intersect].col + intersect_word_index;
    row = words[word_to_intersect].row - add_word_index;
    if(legal_word_spot(word_to_add,word_to_intersect,row,col,Word::VERTICAL)) {
      words[word_to_add].col = col;
      words[word_to_add].row = row;
      words[word_to_add].direction = Word::VERTICAL;
      return true;
    }
  } else {
    // words[word_to_intersect].direction == Word::VERTICAL
    // Word already on the board is Vertical
    // word[word_to_add] must be placed horizontally
    col = words[word_to_intersect].col - add_word_index;
    row = words[word_to_intersect].row + intersect_word_index;
    if(legal_word_spot(word_to_add,word_to_intersect,row,col,Word::HORIZONTAL)) {
      words[word_to_add].col = col;
      words[word_to_add].row = row;
      words[word_to_add].direction = Word::HORIZONTAL;
      return true;
    }
  }
  // Word could not be placed on the board at the target location
  return false;
}

// Place words on the puzzle.
// Assume that the words array is initially ordered from largest word to smallest word.
void Puzzle::Generate() {       
  int loopcount = 0;
  int looplimit = (words.size() * words.size());

  while(true) {
    // Place the initial word. This should be the longest word.  It will be at the head of the word list.
    // Place it horizontally in the middle of the board.
    words[0].col = (Puzzle::COLS - words[0].GetWord().length()) / 2;
    words[0].row = Puzzle::ROWS / 2;
    words[0].direction = Word::HORIZONTAL;
    // Recursively start placing each of the next words
    if(place(1)) return;  // Success
    //
    // Otherwise, randomly shuffle the word order and try again from the beginning
    //
    random_shuffle(words.begin(), words.end());    
    if(loopcount++ > looplimit) {
      cerr << "Unable to place all words. Giving up." << endl;
      return;
    }
    clear(0);
  }
}
  
// Does words[word_to_add] at (row,col) in direction dir intersect with any other word?
// Is it a valid place to put a word?
bool Puzzle::legal_word_spot(int word_to_add, int word_to_intersect,int row, int col, int dir) {
  int rowend, colend;
  char c;

  // Is the (row,col) starting point on the board?
  if ((row < 0) || (col < 0))  return false;
  if ((row > Puzzle::ROWS) || (col > Puzzle::COLS)) return false;

  // Does the whole word fit on the board, or do we fall off the end of the board?
  if (dir == Word::HORIZONTAL) {
    colend = col + words[word_to_add].GetWord().size();
    if(colend > Puzzle::COLS) return false;
  } else if (dir == Word::VERTICAL) { // Vertical
    rowend = row + words[word_to_add].GetWord().size();
    if(rowend > Puzzle::ROWS) return false;
  }

  // Do we cross another word already on the board?
  for(int i = 0; i < words[word_to_add].GetWord().size(); i++) {
    if(dir == Word::HORIZONTAL) {
      if((c = get_letter_at(row,col+i,'.')) != '.') {
	if(words[word_to_add].GetWord()[i] != c) {
	  return false;
	}
      }
    } else { // VERTICAL
      if((c = get_letter_at(row+i,col,'.')) != '.') {
	if(words[word_to_add].GetWord()[i] != c) {
	  return false;
	}
      }
    }
  }

  // Is there already a Word on the board that is parallel and next to us?
  for(auto it = words.begin(); it != words.end(); it++) {
    if(dir == Word::VERTICAL) {
      if(it->direction == Word::VERTICAL) {
	if((it->col == (col-1)) || (it->col == (col+1))) {
	  // Vertical words in adjacent columns. If we are in overlapping rows we fail.
	  if ((row >= it->row) && (row <= (it->row + it->GetWord().size()))) return false;
	  if ((it->row >= row) && (it->row <= (row+words[word_to_add].GetWord().size()))) return false;
	} else if(it->col == col) {
	  // Vertical words in the same column.  We must be at least one row apart.
	  if ((row >= it->row-1) && (row <= (it->row + 1 + it->GetWord().size()))) return false;
	  if ((it->row >= row-1) && (it->row <= (row+1+words[word_to_add].GetWord().size()))) return false;
	}
      }
    } else if (dir == Word::HORIZONTAL) {
      if(it->direction == Word::HORIZONTAL) {
	if((it->row == (row-1)) || (it->row == (row+1))) {
	  // Horizontal words in adjacent rows.  If we are in overlapping columns we fail
	  if((col >= it->col) && (col <= (it->col +it->GetWord().size()))) return false;
	  if((it->col >= col) && (it->col <= (col + words[word_to_add].GetWord().size()))) return false;
	} else if(it->row == row) {
	  // Horizontal words in the same row.  We must be at least one column apart.
	  if((col >= it->col-1) && (col <= (it->col + 1 + it->GetWord().size()))) return false;
	  if((it->col >= col-1) && (it->col <= (col + 1 + words[word_to_add].GetWord().size()))) return false;
	}
      }
    }
  }

  // Make sure that there is space between the beginning and end of a word
  if(dir == Word::HORIZONTAL) {
    if(get_letter_at(row, col-1,'.') != '.') return false;
    if(get_letter_at(row, col+words[word_to_add].GetWord().size(),'.') != '.') return false;
  } else { // Vertical
    if(get_letter_at(row-1, col,'.') != '.') return false;
    if(get_letter_at(row+words[word_to_add].GetWord().size(),col,'.') != '.') return false;
  }

  // Make sure that when we add a Vertical word we don't abut the beginning or end of an already placed Horizontal word
  if(dir == Word::VERTICAL) {
    for(int i = 0; i < word_to_add; i++) {
      if (i != word_to_intersect) {
	if(words[i].direction == Word::HORIZONTAL) {
	  if(words[i].col == (col+1)) {
	    if((words[i].row >= row) && (words[i].row <= row+words[word_to_add].GetWord().size())) return false;
	  }
	  if((words[i].col+words[i].GetWord().size()) == (col-1)) {
	    if((words[i].row >= row) && (words[i].row <= row+words[word_to_add].GetWord().size())) return false;
	  }
	}
      }
    }
  } else {
    // Make sure that when we add a Horizontal word we don't abut the beginning or end of an already placed Vertical word
    for(int i = 0; i < word_to_add; i++) {
      if (i != word_to_intersect) {
	if(words[i].direction == Word::VERTICAL) {
	  if(words[i].row == (row+1)) {
	    if((words[i].col >= col) && (words[i].col <= col+words[word_to_add].GetWord().size())) return false;
	  }
	  if((words[i].row+words[i].GetWord().size()) == (row-1)) {
	    if((words[i].col >= col) && (words[i].col <= col+words[word_to_add].GetWord().size())) return false;
	  }
	}
      }
    }
  }
  
  return true;
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
  for(auto it = words.begin(); it != words.end(); it++) {
    ostr << "(" << setw(2) << it->row << ", " << setw(2) << it->col << ")";
    switch(it->direction) {
    case Word::HORIZONTAL:
      cout << " Across ";
      break;
    case Word::VERTICAL:
      cout << " Down   ";
      break;
    }
    cout << it->GetAnagram() << endl;
  }
}
