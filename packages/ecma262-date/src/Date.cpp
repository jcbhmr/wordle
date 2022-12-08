#include "Date.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <stdexcept>
#include <string>

ecma262_date::Date::Date() {
  this->m_time = std::chrono::system_clock::now();
}

ecma262_date::Date::Date(const std::string& date) {
  std::tm tm = {};
  std::istringstream ss(date);
  ss >> std::get_time(&tm, "%Y-%m-%d");
  if (!ss) {
    throw std::runtime_error("Could not parse date: " + date);
  }
  this->m_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string ecma262_date::Date::toISOString() {
  auto time = std::chrono::system_clock::to_time_t(this->m_time);
  std::stringstream ss;
  // https://stackoverflow.com/a/36927792
  ss << std::put_time(std::localtime(&time), "%FT%T%z");
  return ss.str();
}

ecma262_date::Date::operator std::string() {
  return this->toISOString();
}
