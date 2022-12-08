#pragma once
#include <map>
#include <optional>
#include <string>

// https://fetch.spec.whatwg.org/#headers
// clang-format off
/*
[Exposed=(Window,Worker)]
interface Headers {
  constructor(optional HeadersInit init);

  undefined append(ByteString name, ByteString value);
  undefined delete(ByteString name);
  ByteString? get(ByteString name);
  boolean has(ByteString name);
  undefined set(ByteString name, ByteString value);
  iterable<ByteString, ByteString>;
};
*/
// clang-format on

namespace fetch {
class Headers {
 public:
  // TODO: Add iterator support to Headers
  std::map<std::string, std::string> m_headers;

 public:
  Headers();
  Headers(const std::map<std::string, std::string>& headers);

  void delete_(const std::string& name);
  std::optional<std::string> get(const std::string& name) const;
  bool has(const std::string& name) const;
  void set(const std::string& name, const std::string& value);

  std::map<std::string, std::string> raw() const;
};
}  // namespace fetch
