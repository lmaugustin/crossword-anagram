#include "word.h"
#include <algorithm>

string Word::GenAnagram() {
  anagram = word;
  for(int i = 0; i < ((anagram.size() * 1000) % 17); i++)
    next_permutation(anagram.begin(), anagram.end());

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
