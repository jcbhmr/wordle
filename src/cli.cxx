#include <cpr/cpr.h>
#include <iostream>

int main(int argc, char** argv) {
  cpr::Response r =
      cpr::Get(cpr::Url{"https://api.github.com/repos/libcpr/cpr/contributors"},
               cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
               cpr::Parameters{{"anon", "true"}, {"key", "value"}});
  std::cout << r.status_code << "\n";
  std::cout << r.header["content-type"] << "\n";
  std::cout << r.text << "\n";
}
