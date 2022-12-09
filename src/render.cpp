#include "render.h"
#include <algorithm>
#include <chrono>
#include <numeric>
#include <thread>
#include "ftxui-index.h"

void render(Board& board) {
  using namespace ftxui;

  auto screen = ScreenInteractive::FitComponent();

  std::string inputValue = "";
  auto onChange = [&] {
    std::erase_if(inputValue, [](char c) { return !std::isalpha(c); });
    std::transform(inputValue.cbegin(), inputValue.cend(), inputValue.begin(),
                   [](char c) { return std::toupper(c); });
    if (inputValue.size() > board.word().size()) {
      inputValue = inputValue.substr(0, board.word().size());
    }
  };
  auto onEnter = [&] {
    if (inputValue.size() == board.word().size()) {
      board.guess(inputValue);
      inputValue = "";
    }
  };
  auto inputOptions = InputOption();
  inputOptions.on_enter = onEnter;
  inputOptions.on_change = onChange;
  auto input = Input(&inputValue, "", inputOptions);

  auto component = Renderer(input, [&] {
    Elements children;
    auto guesses = board.guesses();
    for (int i = 0; i < 6; i++) {
      Elements row;
      auto guess = (i < guesses.size() ? guesses[i].first : "     ");
      auto colors =
          (i < guesses.size()
               ? guesses[i].second
               : std::vector<LetterResult>{
                     LetterResult::GRAY, LetterResult::GRAY, LetterResult::GRAY,
                     LetterResult::GRAY, LetterResult::GRAY});

      for (int j = 0; j < 5; j++) {
        auto s = std::string(1, guess[j]);
        auto c = colors[j];
        auto bg =
            c == LetterResult::GREEN
                ? bgcolor(Color::DarkGreen)
                : (c == LetterResult::YELLOW ? bgcolor(Color::DarkGoldenrod)
                                             : bgcolor(Color::GrayDark));
        auto child = text(s) | color(Color::White) | bold | center |
                     size(WIDTH, EQUAL, 4) | bg | border;
        row.push_back(child);
      }
      children.push_back(hbox(std::move(row)));
    }

    if (board.won()) {
      auto win = text("YOU WIN!") | bold | center | color(Color::Green);
      children.push_back(win);
      screen.ExitLoopClosure()();
    } else if (board.lost()) {
      auto lose = text("YOU LOSE!") | bold | center | color(Color::Red);
      children.push_back(lose);
      screen.ExitLoopClosure()();
    } else {
      children.push_back(input->Render());
    }

    return window(text("WORDLE") | center, vbox(std::move(children)));
  });
  component = CatchEvent(component, [&](Event event) {
    if (event == Event::Escape) {
      screen.ExitLoopClosure()();
    }
    return false;
  });
  screen.Loop(component);
  // board.guess("AEIOU");
  // auto g = board.guesses();
  // for (auto& p : g) {
  //   std::cout << p.first << ",";
  //   for (auto& l : p.second) {
  //     std::cout << (int)l << " ";
  //   }
  //   std::cout << std::endl;
  // }
}
