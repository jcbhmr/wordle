#include <ecma262-date/index.h>
#include <fetch/index.h>
#include <nodejs-fs/index.h>
#include <argparse/argparse.hpp>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "Board.h"
#include "LetterResult.h"
#include "render.h"

int main(int argc, char** argv) {
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
  parser.add_argument("-a", "--answer")
      .default_value(false)
      .implicit_value(true)
      .help("Show the answer word");

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
  auto dailyAnswers = dict["dailyAnswers"].get<std::vector<std::string>>();

  auto differenceMs = +date - +dateOffset;
  auto differenceDays =
      static_cast<std::size_t>(differenceMs / (1000 * 60 * 60 * 24));
  if (differenceDays >= dailyAnswers.size()) {
    throw new std::runtime_error(
        "differenceDays " + std::to_string(differenceDays) +
        " is greater than or equal to dailyAnwers.size() " +
        std::to_string(dailyAnswers.size()));
  }
  auto todaysWord = dailyAnswers[differenceDays];

  if (parser.get<bool>("answer")) {
    std::cout << todaysWord << "\n";
    return 0;
  }

  auto board = Board(todaysWord);
  // Here we just pass it all off to the render function. It handles the heavy
  // lifting.
  render(board);
  std::cout << "\n";
}
