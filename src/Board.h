#pragma once
#include <string>
#include <utility>
#include <vector>
#include "LetterResult.h"

class Board {
 private:
  std::string m_word;
  std::vector<std::pair<std::string, std::vector<LetterResult>>> m_guesses;

 public:
  Board(const std::string& word);

 public:
  std::vector<std::pair<std::string, std::vector<LetterResult>>> guesses()
      const;
  std::string word() const;

 public:
  std::vector<LetterResult> guess(const std::string& guess);
  bool won() const;
};
