#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "puzzle.h"

using namespace std;

Puzzle::Puzzle() {
  words.reserve(20);
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

// Place words on the puzzle.
// Assume that the words array is initially ordered from largest word to smallest word.
void Puzzle::Generate() {       
  int loopcount = 0;

  for(int i = 0; i < words.size(); ) {  // Try to place words[i]
    if(i == 0) {
      // Place the first (longest on first pass) word in the center of the board
      words[0].col = (Puzzle::COLS - words[0].GetWord().length()) / 2;
      words[0].row = Puzzle::ROWS / 2;
      words[0].direction = Word::HORIZONTAL;
      i++;
    } else {
      if (try_to_place_word(i)) {
	i++; // successfully found a place for word[i]
      } else {
	// failed to find a place for word[i]
	// randomize the list of words and try again
	random_shuffle(words.begin(), words.end());
	if(loopcount++ > (words.size() * words.size())) {
	  cerr << "Unable to place all words. Giving up." << endl;
	  return;
	}
	i = 0;
	for(auto it = words.begin(); it < words.end(); it++) {
	  it->row = it->col = 0;
	  it->direction = Word::NOT_ON_PUZZLE;
	}
      }
    }
  }
}

void Puzzle::check_for_intersect(string s1, string s2, int &index1, int &index2) {
  for (int a = 0; a < s1.length(); a++) {
    for (int b = 0; b < s2.length(); b++) {
      if(s1[a] == s2[b]) {
	index1 = a;
	index2 = b;
	return;
      }
    }
  }
  index1 = index2 = 01;
}

// Is it legal to put words[w] at (r,c) in direction d ?
bool Puzzle::legal_word_spot(int w, int r, int c, int d) {
  int rowend, colend;

  // Is the (r,c) pair on the board?
  if ((r < 0) || (c < 0))  return false;
  if ((r > Puzzle::ROWS) || (c > Puzzle::COLS)) return false;
  // Is the last character on the board?
  if (d == Word::HORIZONTAL) {
    colend = c + words[w].GetWord().size();
    if(colend > Puzzle::COLS) return false;
  } else if (d == Word::VERTICAL) { // Vertical
    rowend = r + words[w].GetWord().size();
    if(rowend > Puzzle::ROWS) return false;
  }
  // Is there already a Word on the board that is too close to us?
  for(auto it = words.begin(); it != words.end(); it++) {
    if(d == Word::VERTICAL) {
      if(it->direction == Word::VERTICAL) {
	if((it->col == (c-1)) || (it->col == c) || (it->col == (c+1))) return false;
      } else if(it->direction == Word::HORIZONTAL) {
	/*
	if((it->row >= (r-1)) && (it->row <= (r+words[w].GetWord().size()))) {
	  // it is on a row that could run into words[w]
	  if(((it->col + it->GetWord().size()) > (c-1)) &&
	     ((it->col <= c))) return false;
	}
	*/
      }
    } else if (d == Word::HORIZONTAL) {
      if(it->direction == Word::HORIZONTAL) {
	if((it->row == (r-1)) || (it->row == r) || (it->row == (r+1))) return false;
      } else if(it->direction == Word::HORIZONTAL) {
	/*
	if((it-> col >= (c-1)) && ((it->col <= (c + 1 +words[w].GetWord().size())))) {
	  // it is on a column that could run into words[w]
	  
	}
	*/
      }
    }
  }
  return true;
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

bool Puzzle::try_to_place_word(int w) {
  int row, col, rowend, colend;
  int w_index, h_index;
  pair_array_t *pa;
  
  for (int h = 0; h < w; h++) { // look at all previously placed words
    pa = letter_matches(words[w].GetWord(), words[h].GetWord());
    for(auto it = pa->begin(); it != pa->end(); it++) {
      w_index = it->x;
      h_index = it->y;
      if(words[h].direction == Word::HORIZONTAL) {
	// Word already on the board words[h] is Horizontal
	// word[w] must be placed vertically
	col = words[h].col + h_index;
	row = words[h].row - w_index;
	if(legal_word_spot(w,row,col,Word::VERTICAL)) {
	  words[w].col = col;
	  words[w].row = row;
	  words[w].direction = Word::VERTICAL;
	  return true;
	}
      } else {
	// words[h].direction == Word::VERTICAL
	// Word already on the board words[h] is Vertical
	// word[w] must be placed horizontally
	col = words[h].col - w_index;
	row = words[h].row + h_index;
	if(legal_word_spot(w,row,col,Word::HORIZONTAL)) {
	  words[w].col = col;
	  words[w].row = row;
	  words[w].direction = Word::HORIZONTAL;
	  return true;
	}
      }
    }
  }
  return false;
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
