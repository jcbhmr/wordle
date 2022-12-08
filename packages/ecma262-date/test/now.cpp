#include <iostream>
#include "../src/index.h"

int main() {
  using namespace ecma262_date;

  auto date = Date();
  std::cout << date.toISOString() << "\n";
}
