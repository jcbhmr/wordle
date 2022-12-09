#include "Board.h"
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "LetterResult.h"

Board::Board(const std::string& word) : m_word(word) {}

std::vector<std::pair<std::string, std::vector<LetterResult>>> Board::guesses()
    const {
  return this->m_guesses;
}

std::string Board::word() const {
  return this->m_word;
}

/**
 * Guesses a word on the Wordle board in the next row. It will...
 * 1. Throw if the guess is not the same length as this->m_word.
 * 2. Throw if this guess would make the total guesses exceed 6.
 * 3. Compute the LetterResult for each letter in the guess based on
 *     this->m_word.
 * 4. Add the guess and its LetterResults to this->m_guesses.
 * 5. Return the LetterResults.
 */
std::vector<LetterResult> Board::guess(const std::string& guess) {
  if (guess.size() != this->m_word.size()) {
    throw std::runtime_error("Guess must be the same length as the word.");
  }

  if (this->m_guesses.size() >= 6) {
    throw std::runtime_error("Cannot guess more than 6 times.");
  }

  // Do the following for each letter LETTER at index I in the guess:
  // 1. If LETTER is the same as this->m_word[I], the LetterResult is GREEN.
  // 2. If LETTER exists in this->m_word, then the LetterResult is YELLOW.
  // 3. Otherwise, the LetterResult is GRAY.
  //
  // Examples:
  // guess="HELLO" and this->m_word="WORLD" ==> letterResults=[🟥, 🟥, 🟨, 🟨, 🟨]
  // guess="WORLD" and this->m_word="SANDY" ==> letterResults=[🟥, 🟥, 🟥, 🟥, 🟥]
  // guess="HELLO" and this->m_word="HELLO" ==> letterResults=[🟩, 🟩, 🟩, 🟩, 🟩]
  auto letterResults = std::vector<LetterResult>();
  for (std::size_t i = 0; i < guess.size(); i++) {
    auto letter = guess[i];
    auto letterResult = LetterResult::GRAY;
    if (letter == this->m_word[i]) {
      letterResult = LetterResult::GREEN;
    } else if (this->m_word.find(letter) != std::string::npos) {
      letterResult = LetterResult::YELLOW;
    }
    letterResults.push_back(letterResult);
  }

  this->m_guesses.push_back(std::make_pair(guess, letterResults));
  return letterResults;
}

bool Board::won() const {
  if (this->m_guesses.empty()) {
    return false;
  }

  auto lastGuess = this->m_guesses.back();
  auto lastGuessWord = lastGuess.first;
  return lastGuessWord == this->m_word;
}
