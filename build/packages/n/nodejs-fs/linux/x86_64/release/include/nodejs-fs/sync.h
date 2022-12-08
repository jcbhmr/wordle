#pragma once
#include <string>

namespace nodejs {
namespace fs {
std::string readFileSync(const std::string& path);
}  // namespace fs
}  // namespace nodejs
