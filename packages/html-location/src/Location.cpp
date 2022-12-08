#include "Location.h"
#include <skyr/url.hpp>
#include <string>

html_location::Location::Location(const std::string &url) {}

std::string html_location::Location::href() const { return ""; }

std::string html_location::Location::origin() const { return "null"; }

std::string html_location::Location::protocol() const { return "file:"; }

std::string html_location::Location::host() const { return ""; }

std::string html_location::Location::hostname() const { return ""; }

std::string html_location::Location::port() const { return ""; }

std::string html_location::Location::pathname() const { return "/"; }

std::string html_location::Location::search() const { return ""; }

std::string html_location::Location::hash() const { return ""; }

void html_location::Location::assign(const std::string &url) {}

void html_location::Location::replace(const std::string &url) {}

void html_location::Location::reload() {}
