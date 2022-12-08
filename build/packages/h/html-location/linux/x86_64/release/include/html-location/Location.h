#pragma once
#include <skyr/url.hpp>
#include <string>

// https://html.spec.whatwg.org/multipage/nav-history-apis.html#location
// clang-format off
/*
[Exposed=Window]
interface Location { // but see also additional creation steps and overridden internal methods
  [LegacyUnforgeable] stringifier attribute USVString href;
  [LegacyUnforgeable] readonly attribute USVString origin;
  [LegacyUnforgeable] attribute USVString protocol;
  [LegacyUnforgeable] attribute USVString host;
  [LegacyUnforgeable] attribute USVString hostname;
  [LegacyUnforgeable] attribute USVString port;
  [LegacyUnforgeable] attribute USVString pathname;
  [LegacyUnforgeable] attribute USVString search;
  [LegacyUnforgeable] attribute USVString hash;

  [LegacyUnforgeable] undefined assign(USVString url);
  [LegacyUnforgeable] undefined replace(USVString url);
  [LegacyUnforgeable] undefined reload();

  [LegacyUnforgeable, SameObject] readonly attribute DOMStringList
ancestorOrigins;
};
*/
// clang-format on

namespace html_location {
class Location {
private:
  skyr::url m_url;

public:
  Location(const std::string &url);

  std::string href() const;
  std::string origin() const;
  std::string protocol() const;
  std::string host() const;
  std::string hostname() const;
  std::string port() const;
  std::string pathname() const;
  std::string search() const;
  std::string hash() const;
};
} // namespace html_location
