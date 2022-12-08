#pragma once
#include <future>
#include <istream>
#include <string>
#include "Headers.h"
#include "ResponseInit.h"

// https://fetch.spec.whatwg.org/#response
// clang-format off
/*
[Exposed=(Window,Worker)]interface Response {
  constructor(optional BodyInit? body = null, optional ResponseInit init = {});

  [NewObject] static Response error();
  [NewObject] static Response redirect(USVString url, optional unsigned short status = 302);
  [NewObject] static Response json(any data, optional ResponseInit init = {});

  readonly attribute ResponseType type;

  readonly attribute USVString url;
  readonly attribute boolean redirected;
  readonly attribute unsigned short status;
  readonly attribute boolean ok;
  readonly attribute ByteString statusText;
  [SameObject] readonly attribute Headers headers;

  [NewObject] Response clone();
};
Response includes Body;
*/
// clang-format on

namespace fetch {
class Response {
 private:
  std::string m_url;
  unsigned short m_status;
  fetch::Headers m_headers;
  std::shared_ptr<std::istream> m_body;

 public:
  Response(const std::string& body);
  Response(const std::string& body, const fetch::ResponseInit& init);
  Response(const std::shared_ptr<std::istream> body);
  Response(const std::shared_ptr<std::istream> body,
           const fetch::ResponseInit& init);

  std::string url() const;
  unsigned short status() const;
  bool ok() const;
  fetch::Headers headers() const;

  std::future<std::string> text();
};
}  // namespace fetch
