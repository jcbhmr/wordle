# `fetch()` for C++

🌐 A C++ implementation of the WHATWG [Fetch Standard]

<div align="center">

![](https://i.imgur.com/3LnVrsH.png)

<!--prettier-ignore-->
[Overview](https://github.com/jcbhmr/wordle#readme)
| [Dev wiki](https://github.com/jcbhmr/wordle/tree/main/wiki)
| **[packages/fetch](https://github.com/jcbhmr/wordle/tree/main/packages/fetch#readme)**
| [packages/html-location](https://github.com/jcbhmr/wordle/tree/main/packages/html-location#readme)

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

## Development

You can run the test suite with xmake using the binary build targets. Running
with an unspecified target will run _all_ binary targets.

⚠️ Make sure you use the `-P.` flag so that xmake uses the current directory,
not the root project directory!

```sh
xmake -P. && xmake r -P.
```

[fetch standard]: https://fetch.spec.whatwg.org/
[libcpr/cpr]: https://github.com/libcpr/cpr#readme
