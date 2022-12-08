#include <iostream>
#include "../src/index.h"

int main() {
  namespace fs = nodejs::fs;

  std::string __dirname = DIRNAME;
  std::cout << "__dirname: " << __dirname << "\n";

  auto path = __dirname + "/lorem.txt";
  std::cout << "Contents of " << path << "\n";
  auto result = fs::readFileSync(path);
  std::cout << result << "\n";
}
