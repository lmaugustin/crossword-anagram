#ifndef WORD_H
#define WORD_H

#include <string>

Class Word {
 public:
  Word();
  ~Word();
  Word(string s);      // Create a new Word with the plain text s
  string GetWord() {return s;};
  string GenAnagram(); // Generate a new anagram for the Word. Return the anagram.  Used to generate clues in the puzzle.
  string GetAnagram() {// Return the current anagram. Generates an anagram if one does not exist.
    return anagram;
  };
  void SetWord(string s) {      // Set the plain text for this word.
    word = s;
  };
  void SetPosition(int r, int c, int d) {   // Set the row, column and direction for the position of this word in the puzzle
    row = r; col = c; direction = d;
  };
  void GetPosition(int &r, int &c, int &d) { // Get the position of this word in the puzzle.
    r = row; c = col; d = direction;
  };
  static const int Horizontal = 1;
  static const int Vertical = 2;
 private:
  string word;    // The plaintext word
  string anagram; // An anagram of the word.
  int row, col, direction;
}

#endif
