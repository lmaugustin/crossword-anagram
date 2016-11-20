#ifndef WORD_H
#define WORD_H

#include <string>

using namespace std;

class Word {
 public:
  Word() {};
  ~Word() {};
  Word(string s);      // Create a new Word with the plain text s
  string GetWord() {return word;};
  string GenAnagram(); // Generate a new anagram for the Word. Return the anagram.  Used to generate clues in the puzzle.
  string GetAnagram() {// Return the current anagram. Generates an anagram if one does not exist.
    return anagram;
  };
  void SetWord(string s) {      // Set the plain text for this word.
    word = s;
  };
  static const int HORIZONTAL = 1;
  static const int VERTICAL = 2;
  int row, col, direction;
 private:
  string word;    // The plaintext word
  string anagram; // An anagram of the word.
};

#endif
