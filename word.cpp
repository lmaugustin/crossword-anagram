#include "word.h"
#include <algorithm>

string Word::GenAnagram() {
  anagram = word;
  random_shuffle(anagram.begin(), anagram.end());
  return anagram;
}

Word::Word(string s) {
  word = s;
  this->GenAnagram();
  direction = Word::NOT_ON_PUZZLE;
  row = col = -1;
}
