#include "word.h"

string Word::GenAnagram() {
  // Generate an anagram for the word and return a copy

  // TBD
  
  return anagram;
}

Word::Word(string s) {
  word = s;
  this->GenAnagram();
  direction = Word::NOT_ON_PUZZLE;
}

Word::Word() {
  direction = Word::NOT_ON_PUZZLE;
}
