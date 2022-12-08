#include "sync.h"
#include <fstream>
#include <stdexcept>
#include <streambuf>
#include <string>

std::string nodejs::fs::readFileSync(const std::string& path) {
  // https://stackoverflow.com/a/2602060
  auto ifs = std::ifstream(path);
  if (!ifs) {
    throw std::runtime_error("Could not open file: " + path);
  }
  return std::string((std::istreambuf_iterator<char>(ifs)),
                     (std::istreambuf_iterator<char>()));
}
