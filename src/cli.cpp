// #include <ecma262-date/index.h>
#include <ecma262-date/index.h>
#include <fetch/index.h>
#include <nodejs-fs/index.h>
#include <argparse/argparse.hpp>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "ftxui-index.h"

enum class CellState : unsigned short {
  GRAY = 0,
  YELLOW = 1,
  GREEN = 2,
};

class BoardState {
 private:
  std::vector<std::string> m_guesses;
  std::string m_word;

 public:
  void backspace() {
    auto lastRow = this->m_guesses.back();
    if (lastRow.size() > 0) {
      lastRow.pop_back();
    }
  }
  bool type(const char c) {
    auto lastRow = this->m_guesses.back();
    lastRow.push_back(c);
    if (lastRow.size() == 4) {
      lastRow.push_back(c);
      this->nextLine();
    }
  }

 private:
  /**
   * 1. Create a new 2D vector of CellState-s.
   * 2. Loop over the guesses,
   *     a. If the guess is not complete, fill the row with GRAY.
   *     b. If the guess is complete, loop over the characters of the guess,
   *         i. If the character is correct, fill the CellState with GREEN.
   *         ii. If the character is present, fill the CellState with YELLOW.
   *         iii. If the character is not present, fill the CellState with GRAY.
   *     c. Push the row into the 2D vector.
   * 4. Return the 2D vector.
   */
  std::vector<std::vector<CellState>> cells() const {
    // 1.
    std::vector<std::vector<CellState>> returnValue;

    // 2.
    for (std::size_t i = 0; i < 6; i++) {
      std::vector<CellState> row;
      std::string guess;
      if (i < this->m_guesses.size()) {
        guess = this->m_guesses[i];
      }

      // 2.a.
      if (guess.size < 5) {
        row = {CellState::GRAY, CellState::GRAY, CellState::GRAY,
               CellState::GRAY, CellState::GRAY};
        continue;
      }

      // 2.b.
      for (std::size_t j; j < 5; j++) {
        if (j >= guess.size()) {
          row.push_back(CellState::GRAY);
          continue;
        }

        if (guess[i] == this->m_word[i]) {
          row.push_back(CellState::GREEN);
        } else if (this->m_word.find(guess[i]) != std::string::npos) {
          row.push_back(CellState::YELLOW);
        } else {
          row.push_back(CellState::GRAY);
        }
      }

      returnValue.push_back(row);
    }

    // 4.
    return returnValue;
  }
};

int main(int argc, char** argv) {
  using namespace ftxui;
  using namespace fetch;
  using namespace argparse;
  using JSON = nlohmann::json;
  using namespace ecma262_date;
  namespace NodeFS = nodejs::fs;

  // Argument defaults
  auto date_DEFAULT = static_cast<std::string>(Date());
  auto dict_DEFAULT =
      std::string(std::getenv("HOME")) + "/.config/wordle/dict.json";

  // Create the parser
  ArgumentParser parser;
  parser.add_argument("date")
      .default_value(date_DEFAULT)
      .help("Which date to use as the answer word");
  parser.add_argument("-d", "--dict")
      .default_value(dict_DEFAULT)
      .help(
          "A JSON dictionary file to use "
          "(https://github.com/jcbhmr/wordle/blob/main/assets/dict/"
          "official.json)");

  // Parse the arguments
  try {
    parser.parse_args(argc, argv);
  } catch (const std::runtime_error& error) {
    std::cout << error.what() << "\n";
    std::cout << parser;
    return 1;
  }
  // The parser auto-exit()-s if the user asks for --help. Don't worry about it.

  // Do some argument post-processing & extraction
  Date date;
  if (parser.get<std::string>("date") == "today") {
    date = Date();
  } else {
    date = Date(parser.get<std::string>("date"));
  }
  std::string dictPath = parser.get<std::string>("dict");

  JSON dict;
  try {
    auto dictJson = NodeFS::readFileSync(dictPath);
    dict = JSON::parse(dictJson);
  } catch (const std::runtime_error& error) {
    std::cout << error.what() << "\n";
    return 1;
  }

  auto validGuesses = dict["validGuesses"].get<std::vector<std::string>>();
  auto dateOffsetString = dict["dateOffset"].get<std::string>();
  auto dateOffset = Date(dateOffsetString);
  auto dailyAnwers = dict["dailyAnswers"].get<std::vector<std::string>>();

  auto differenceMs = +Date() - +dateOffset;
  auto differenceDays =
      static_cast<std::size_t>(differenceMs / (1000 * 60 * 60 * 24));
  if (differenceDays >= dailyAnwers.size()) {
    throw new std::runtime_error(
        "differenceDays " + std::to_string(differenceDays) +
        " is greater than or equal to dailyAnwers.size() " +
        std::to_string(dailyAnwers.size()));
  }
  auto todaysWord = dailyAnwers[differenceDays];

  // std::cout << "differenceDays: " << differenceDays << "\n";
  // std::cout << "todaysWord: " << todaysWord << "\n";
  // std::cout << "date: " << date.toISOString() << "\n";

  // Now we move onto showing the fancy FTXUI stuff. We need to...
  // 1. Create a table that starts out completely blank with 5 columns and 6
  // rows.
  //     This is the Wordle workspace. The user will type keys on the keyboard,
  //     and the table will update to show the user's progress.
  // 2. Dynamically change the content and "selected row" of the table to show
  // that
  //     the user has typed a correct letter. This means we need an external set
  //     of variables to track that.
  // 3. Register all the event listeners we need to handle user input.

  auto table = std::vector<std::vector<std::string>>();
  for (int i = 0; i < 6; i++) {
    auto row = std::vector<std::string>();
    for (int j = 0; j < 5; j++) {
      row.push_back("");
    }
    table.push_back(row);
  }
  auto table = Table(tableRows);

  auto document = table.Render();
  auto screen = Screen::Create(Dimension::Fit(document));
  Render(screen, document);
  screen.Print();
  std::cout << "\n";

  auto renderer = Renderer(container, [&] {
    Elements elements;
    elements.push_back(hbox({
        text(author) | xflex,
    }));
  });
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
  std::cout << "\n";
}
