#include "location.h"
#include "Location.h"

namespace html_location {
Location location() {
  static auto location =
      Location("file:///home/username/?0=/usr/bin/my-app&1=--help");
  return location;
}
}  // namespace html_location
