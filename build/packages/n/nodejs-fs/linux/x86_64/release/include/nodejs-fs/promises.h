#pragma once
// #include <future>
#include <string>

namespace nodejs {
namespace fs {
namespace promises {
// std::future<std::string>
std::string readFile(const std::string& path);
}  // namespace promises
}  // namespace fs
}  // namespace nodejs
