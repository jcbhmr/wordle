#include <iostream>
#include "../src/index.h"

int main() {
  auto response = fetch::fetch("https://example.org").get();
  std::cout << response.url() << "\n";
  std::cout << response.status() << "\n";
  for (auto& [name, value] : response.headers().m_headers) {
    std::cout << name << ": " << value << "\n";
  }
  std::cout << "Explicitly get Content-Type: "
            << response.headers().get("Content-Type").value_or("<null>")
            << "\n\n";
  std::cout << response.text().get() << "\n";
}
