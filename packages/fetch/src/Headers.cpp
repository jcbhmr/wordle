#include "Headers.h"
#include <map>
#include <optional>
#include <string>

fetch::Headers::Headers() : m_headers(std::map<std::string, std::string>()) {}

fetch::Headers::Headers(const std::map<std::string, std::string>& headers)
    : m_headers(std::map<std::string, std::string>()) {
  for (auto& [name, value] : headers) {
    std::string lowercaseName = name;
    std::transform(lowercaseName.begin(), lowercaseName.end(),
                   lowercaseName.begin(),
                   [](auto c) { return std::tolower(c); });

    this->m_headers[lowercaseName] = value;
  }
}

void fetch::Headers::delete_(const std::string& name) {
  std::string lowercaseName = name;
  std::transform(lowercaseName.begin(), lowercaseName.end(),
                 lowercaseName.begin(), [](auto c) { return std::tolower(c); });

  this->m_headers.erase(lowercaseName);
}

std::optional<std::string> fetch::Headers::get(const std::string& name) const {
  std::string lowercaseName = name;
  std::transform(lowercaseName.begin(), lowercaseName.end(),
                 lowercaseName.begin(), [](auto c) { return std::tolower(c); });

  auto it = this->m_headers.find(lowercaseName);
  if (it == this->m_headers.end()) {
    return std::nullopt;
  } else {
    return it->second;
  }
}

bool fetch::Headers::has(const std::string& name) const {
  std::string lowercaseName = name;
  std::transform(lowercaseName.begin(), lowercaseName.end(),
                 lowercaseName.begin(), [](auto c) { return std::tolower(c); });

  return this->m_headers.find(lowercaseName) != this->m_headers.end();
}

void fetch::Headers::set(const std::string& name, const std::string& value) {
  std::string lowercaseName = name;
  std::transform(lowercaseName.begin(), lowercaseName.end(),
                 lowercaseName.begin(), [](auto c) { return std::tolower(c); });

  this->m_headers[lowercaseName] = value;
}

std::map<std::string, std::string> fetch::Headers::raw() const {
  return this->m_headers;
}
