#include "render.h"
#include <algorithm>
#include <chrono>
#include <numeric>
#include <thread>
#include "ftxui-index.h"

void render(Board& board) {
  using namespace ftxui;

  auto screen = ScreenInteractive::Fullscreen();
  auto stop = screen.ExitLoopClosure();

  auto header = text("Wordle") | hcenter | color(Color::Blue);

  auto guesses = board.guesses();
  auto word = board.word();
  std::string backingGuess = "";

  auto onGuessChange = [&] {
    std::erase_if(backingGuess, [](char c) { return !std::isalpha(c); });
    std::transform(backingGuess.cbegin(), backingGuess.cend(),
                   backingGuess.begin(),
                   [](char c) { return std::toupper(c); });
    if (backingGuess.size() > word.size()) {
      backingGuess = backingGuess.substr(0, word.size());
    }
  };
  auto onGuessEnter = [&] {
    if (backingGuess.size() == word.size()) {
      board.guess(backingGuess);
      guesses = board.guesses();
      backingGuess = "";
    }

    if (board.won()) {
      stop();
    }
  };

  auto guessOptions = InputOption();
  guessOptions.on_enter = onGuessEnter;
  guessOptions.on_change = onGuessChange;
  auto guess = Input(&backingGuess, "", guessOptions);

  auto component = Container::Vertical({guess});

  screen.Loop(Renderer(component, [&] {
    auto tableRaw = std::vector<std::vector<Element>>();
    for (std::size_t i = 0; i < 6; i++) {
      auto row = std::vector<Element>();

      std::string guess;
      std::vector<LetterResult> results;
      if (i < guesses.size()) {
        guess = guesses[i].first;
        results = guesses[i].second;
      }

      for (std::size_t j = 0; j < word.size(); j++) {
        if (guess.empty()) {
          row.push_back(text("   "));
        } else {
          auto letter = guess[j];
          auto result = results[j];
          auto str = std::string(1, letter);
          auto cell = text(" " + str + " ");
          if (result == LetterResult::GREEN) {
            cell |= bgcolor(Color::Green);
          } else if (result == LetterResult::YELLOW) {
            cell |= bgcolor(Color::Yellow);
          }
          row.push_back(cell);
        }
      }

      tableRaw.push_back(row);
    }

    auto table = Table(tableRaw);
    for (std::size_t i = 0; i < tableRaw.size(); i++) {
      for (std::size_t j = 0; j < tableRaw[i].size(); j++) {
        table.SelectCell(i, j).Border();

        std::string guess;
        std::vector<LetterResult> results;
        if (i < guesses.size()) {
          guess = guesses[i].first;
          results = guesses[i].second;
        }

        for (std::size_t j = 0; j < word.size(); j++) {
          if (guess.empty()) {
            continue;
          }
          auto result = results[j];
          if (result == LetterResult::GREEN) {
            table.SelectCell(i, j).DecorateCells(bgcolor(Color::Green));
          } else if (result == LetterResult::YELLOW) {
            table.SelectCell(i, j).DecorateCells(bgcolor(Color::Yellow));
          }
        }
      }
    }

    return vbox({
        header,
        separator(),
        hbox(table.Render()) | hcenter,
        separator(),
        component->Render(),
    });
  }));
}
