#include "Location.h"
#include <skyr/url.hpp>
#include <string>

html_location::Location::Location(const std::string &url) : m_url(url) {}

std::string html_location::Location::href() const { return this->m_url.href(); }

std::string html_location::Location::origin() const {
  return this->m_url.origin();
}

std::string html_location::Location::protocol() const {
  return this->m_url.protocol();
}

std::string html_location::Location::host() const { return this->m_url.host(); }

std::string html_location::Location::hostname() const {
  return this->m_url.hostname();
}

std::string html_location::Location::port() const { return this->m_url.port(); }

std::string html_location::Location::pathname() const {
  return this->m_url.pathname();
}

std::string html_location::Location::search() const {
  return this->m_url.search();
}

std::string html_location::Location::hash() const { return this->m_url.hash(); }
