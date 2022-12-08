#include <fetch/fetch.h>
#include <argparse/argparse.hpp>

int main(int argc, char** argv) {
  fetch::fetch("");

  argparse::ArgumentParser parser;
  parser.add_argument("foo")
    .help("foo help");
  parser.add_argument("bar")
    .help("bar help");
  parser.add_argument("-b", "--baz")
    .help("baz help")
    .default_value(std::string("default baz"))
    .implicit_value(std::string("implicit baz"));
  parser.add_argument("-q", "--qux")
    .help("qux help")
    .default_value(false)
    .implicit_value(true);

  try {
    parser.parse_args(argc, argv);
  }
  catch (const std::runtime_error& err) {
    std::cout << err.what() << std::endl;
    std::cout << parser;
    exit(0);
  }
}
