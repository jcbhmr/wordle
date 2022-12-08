#include <iostream>
#include "../src/index.h"

int main() {
  // https://jsonplaceholder.typicode.com/
  auto response =
      fetch::fetch("https://jsonplaceholder.typicode.com/todos/1").get();
  std::cout << "URL: " << response.url() << "\n";
  std::cout << "Status:" << response.status() << "\n";
  std::cout << "Headers:\n";
  for (auto& [name, value] : response.headers().m_headers) {
    std::cout << "  " << name << ": " << value << "\n";
  }
  std::cout << "Explicitly get Content-Type: "
            << response.headers().get("Content-Type").value_or("<null>")
            << "\n";
  std::cout << "Body:\n";
  std::cout << response.text().get() << "\n";
}
