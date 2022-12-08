#pragma once
#include <future>
#include <string>
#include "Response.h"

namespace fetch {
std::future<fetch::Response> fetch(const std::string& url);
}  // namespace fetch
