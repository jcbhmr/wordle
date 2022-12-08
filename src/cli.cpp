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
    auto dictJson = NodeFS::promises::readFile(dictPath);
    dict = JSON::parse(dictJson);
  } catch (const std::runtime_error& error) {
    std::cout << error.what() << "\n";
    return 1;
  }

  // Now we move onto showing the fancy FTXUI stuff.

  // The main screen
  Element document = graph([](int x, int y) {
    std::vector<int> result(x, 0);
    for (int i{0}; i < x; ++i) {
      result[i] = ((3 * i) / 2) % y;
    }
    return result;
  });

  document |= color(Color::Red);
  document |= bgcolor(Color::DarkBlue);
  document |= border;

  const int width = 80;
  const int height = 10;
  auto screen =
      Screen::Create(Dimension::Fixed(width), Dimension::Fixed(height));
  Render(screen, document);
  screen.Print();
}
