// #include <ecma262-date/index.h>
#include <fetch/index.h>
#include <argparse/argparse.hpp>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "ftxui.h"

#include <chrono>
#include <ctime>
#include <string>
namespace ecma262_date {
class Date {
 private:
  std::chrono::system_clock::time_point m_time;

 public:
  Date() { this->m_time = std::chrono::system_clock::now(); }
  Date(const std::string& date) {
    std::tm tm = {};
    std::istringstream ss(date);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (!ss) {
      throw std::runtime_error("Could not parse date: " + date);
    }
    this->m_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
  }

  std::string toISOString() {
    auto time = std::chrono::system_clock::to_time_t(this->m_time);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d");
    return ss.str();
  }

  explicit operator std::string() { return this->toISOString(); }
};
}  // namespace ecma262_date

#include <fstream>
#include <future>
#include <stdexcept>
#include <streambuf>
#include <string>
namespace nodejs {
namespace fs {
namespace promises {
std::future<std::string> readFile(const std::string& path) {
  // https://stackoverflow.com/a/2602060
  auto f = std::ifstream(path);
  if (!f) {
    throw std::runtime_error("Could not open file: " + path);
  }
  std::string result;

  f.seekg(0, std::ios::end);
  result.reserve(f.tellg());
  f.seekg(0, std::ios::beg);

  result.assign(std::istreambuf_iterator<char>(f),
                std::istreambuf_iterator<char>());

  auto promise = std::promise<std::string>();
  promise.set_value(result);
  return promise.get_future();
}
}  // namespace promises
}  // namespace fs
}  // namespace nodejs

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
    auto dictJson = NodeFS::promises::readFile(dictPath).get();
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
