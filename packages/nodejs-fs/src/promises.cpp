#include "promises.h"
#include <fstream>
// #include <future>
#include <stdexcept>
#include <streambuf>
#include <string>

// std::future<std::string>
std::string nodejs::fs::promises::readFile(const std::string& path) {
  // https://stackoverflow.com/a/2602060
  auto ifs = std::ifstream(path);
  if (!ifs) {
    throw std::runtime_error("Could not open file: " + path);
  }
  auto content = std::string((std::istreambuf_iterator<char>(ifs)),
                             (std::istreambuf_iterator<char>()));

  // auto promise = std::promise<std::string>();
  // promise.set_value(content);
  // return promise.get_future();
  return content;
}
