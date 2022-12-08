# `fetch()` for C++

🌐 A C++ implementation of the WHATWG [Fetch Standard]

<div align="center">

![](https://i.imgur.com/3LnVrsH.png)

<!--prettier-ignore-->
[Overview](https://github.com/jcbhmr/wordle#readme)
| [Dev wiki](https://github.com/jcbhmr/wordle/tree/main/wiki)
| **[packages/fetch](https://github.com/jcbhmr/wordle/tree/main/packages/fetch)**
| [packages/html-location](https://github.com/jcbhmr/wordle/tree/main/packages/html-location)

</div>

🌐 Uses [libcpr/cpr] under the hood \
💻 Behaves just like the `fetch()` function in JavaScript

## Usage

```cxx
#include <fetch/index.h>
#include <iostream>

int main() {
  auto response = fetch::fetch("https://example.org/").get();
  std::cout << response.text().get() << "\n";
}
```

[fetch standard]: https://fetch.spec.whatwg.org/
[libcpr/cpr]: https://github.com/libcpr/cpr#readme
