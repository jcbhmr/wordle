#pragma once
#include <string>
#include "Headers.h"

// https://fetch.spec.whatwg.org/#responseinit
// clang-format off
/*
dictionary ResponseInit {
  unsigned short status = 200;
  ByteString statusText = "";
  HeadersInit headers;
};
*/
// clang-format on

namespace fetch {
struct ResponseInit {
  unsigned short status = 200;
  std::string statusText = "";
  fetch::Headers headers;
  std::string url;
};
}  // namespace fetch
