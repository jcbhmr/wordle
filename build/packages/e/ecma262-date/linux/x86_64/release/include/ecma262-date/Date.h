#include <chrono>
#include <string>

namespace ecma262_date {
class Date {
 private:
  std::chrono::system_clock::time_point m_time;

 public:
  Date();
  Date(const std::string& date);

  std::string toISOString();

  operator std::string();
};
}  // namespace ecma262_date
