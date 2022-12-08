#include "fetch.h"
#include <cpr/cpr.h>
#include <future>
#include <iostream>
#include <string>
#include "Response.h"
#include "ResponseInit.h"

std::future<fetch::Response> fetch::fetch(const std::string& url) {
  auto response = cpr::Get(cpr::Url{url});
  auto headers = std::map<std::string, std::string>();
  for (auto& [name, value] : response.header) {
    headers[name] = value;
  }

  auto promise = std::promise<fetch::Response>();
  promise.set_value(fetch::Response(
      response.text,
      fetch::ResponseInit{
          .status = static_cast<unsigned short>(response.status_code),
          .headers = headers,
          .url = static_cast<std::string>(response.url),
      }));
  return promise.get_future();
}
