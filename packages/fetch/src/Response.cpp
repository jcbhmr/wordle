#include "Response.h"
#include <future>
#include <memory>
#include <sstream>
#include <string>

fetch::Response::Response(const std::string& body,
                          const fetch::ResponseInit& init = {})
    : m_body(std::make_unique<std::istringstream>(body)),
      m_url(init.url),
      m_status(init.status),
      m_headers(init.headers) {}
fetch::Response::Response(const std::shared_ptr<std::istream> body,
                          const fetch::ResponseInit& init = {})
    : m_body(body),
      m_url(init.url),
      m_status(init.status),
      m_headers(init.headers) {}

std::string fetch::Response::url() const {
  return this->m_url;
}

unsigned short fetch::Response::status() const {
  return this->m_status;
}

bool fetch::Response::ok() const {
  return 200 <= this->m_status && this->m_status < 300;
}

fetch::Headers fetch::Response::headers() const {
  return this->m_headers;
}

std::future<std::string> fetch::Response::text() {
  auto str = std::string(std::istreambuf_iterator<char>(*this->m_body), {});
  auto promise = std::promise<std::string>();
  promise.set_value(str);
  return promise.get_future();
}
