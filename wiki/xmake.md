<div align="center">

<!--prettier-ignore-->
[Overview](https://github.com/jcbhmr/wordle#readme)
| **[Dev wiki](https://github.com/jcbhmr/wordle/tree/main/wiki)**

</div>

This project uses [xmake] for its all-in-one build system. It handles Conan
package fetching & installation, private packages, hooks, plugins, and more. And
it does it all using [Lua] instead of a completely new DSL like [CMake]. Such a
complex configuration tool doesn't come without its quirks. This is a document
designated to recording, documenting, and explaining those quirks as they arise
in this project.

## Private package index

The first crux of this project is that it's a [monorepo]. It has multiple
subpackages. These subpackages could eventually turn into fully complete
stand-along packages, but for now they're stuck in this repo.

To use these packages, we need to use xmake's local "repository" feature. In
xmake, a repository refers to an index of build manifests that detail either
where to download a source code bundle (and then how to build it), or how to
install an existing compiled package. In this case, we have a `build/packages/`
folder that contains build artifacts ready to be consumed by xmake.

```lua
add_repositories("local-repo build") -- This checks the build/packages/ folder.
```

We have decided to keep build artifacts in the `build/` folder _checked into
source control_. This means that another user can use this package without
running the `tools/gen-repo-index.sh` script. However, while developing it's
recommended to run this script locally to keep this local package index
up-to-date if you make changes to the subpackages.

This package index should also be auto-generated by GitHub Actions alleviating
the need to watch it closely when commiting.

### Why not publish the package index as an orphan Git branch?

Well, the answer is simple: then you'd have to publish your changes to GitHub in
order to then just download them again on your local machine to test a change in
one of the subpackages. This isn't ideal. If we could solve this problem and use
the remote if the local doesn't exist, that would be ideal. I just don't know
how to do that yet, so we're doing it this way for now.

## Changing the local configuration

xmake has local configuration options that you can change to affect a variety of
different things. To see a TUI menu, you can run:

```sh
xmake f --menu
```

The most interesting setting is the `mode` option which is then consumed and
used by the `mode.debug` and `mode.release` rules.

```sh
xmake f -m release
xmake f -m debug
```

## Using platform-specific switches

In order to abstract things, it's useful to provide different implementations of
a public function for different operating systems or platforms. You can do the
same thing in xmake with the `is_plat()` function.

This example adds the `-lpthread` flag (likely required when using
`#include <future>`) when the platform is `"linux"` or `"macosx"`.

```lua
target("my-app") do
  if is_plat("linux", "macosx") then
    add_syslinks("pthread")
  end
end
```

## Using Conan requirements

```sh
add_requires("conan::fmt/9.0.0", {alias="fmt"})
```

xmake also has its own package index ([xmake-io/xmake-repo]) for packages that
use xmake (or wrappers around existing non-xmake packages). This means that you
_can_ use `add_requires("zlib")` if your package is reasonably popular, and
it'll probably work.

⚠️ [xmake-io/xmake-repo] doesn't update their packages regularily! You will
often find that Conan or vcpkg versions of the same project have newer versions.
If possible, use these more recent versions.

[argparse] is a good example of this: <!-- Last updated: 2022-12-07 -->

- **[conan::argparse]:** v2.9 ⭐
- **[vcpkg::argparse]:** v2.8
- **[(xmake) argparse]:** v2.6

⚠️ You also need to make sure that you use the proper aliasing. By default,
Conan packages aren't recognized. Instead, you need to add a
`{alias="$PACKAGE_NAME"}` parameter to get you C++ code to work. I don't know
exactly why this happens or what causes it. The official documentation even uses
this strategy.

📚 Further reading: [add_requires - xmake]

## Lua tips & tricks

The xmake docs indicate that you should use non-standard indentation for things
like `target()`. These functions _don't actually create a new block context_,
nor do they open up a new function like some JavaScript testing frameworks.
Instead, it acts like CMake: it's imperative.

```lua
target("wordle")
  set_languages("clatest", "cxxlatest")
  set_kind("binary")
  add_files("src/*.cpp")
  add_packages("ftxui", "nlohmann_json", "fetch", "argparse")
target_end()
```

But, this imperative custom indentation convention means that Lua formatters
don't recognize it, and will reformat the code that you write to remove those
indentations.

```lua
target("wordle")
set_languages("clatest", "cxxlatest")
set_kind("binary")
add_files("src/*.cpp")
add_packages("ftxui", "nlohmann_json", "fetch", "argparse")
target_end()
```

Instead, the [official formatting recommendation] if you use such formatters is
to use `do ... done` blocks.

```lua
target("wordle") do
  set_languages("clatest", "cxxlatest")
  set_kind("binary")
  add_files("src/*.cpp")
  add_packages("ftxui", "nlohmann_json", "fetch", "argparse")
end
```

## C++ version mismatches

By default, it seems like xmake compiles with a very outdated (pre-C++11)
compiler mode. To fix this, make sure you use:

```lua
-- Doing it right before add_files() makes the most sense to me.
target("my-app") do
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
end
```

[xmake]: https://xmake.io/#/
[lua]: https://www.lua.org/
[cmake]: https://cmake.org/
[monorepo]: https://semaphoreci.com/blog/what-is-monorepo
[xmake-io/xmake-repo]: https://github.com/xmake-io/xmake-repo#readme
[argparse]: https://github.com/p-ranav/argparse#readme
[(xmake) argparse]:
  https://github.com/xmake-io/xmake-repo/tree/master/packages/a/argparse
[conan::argparse]: https://conan.io/center/argparse
[vcpkg::argparse]: https://vcpkg.io/en/packages.html
[tap]: https://node-tap.org/
[official formatting recommendation]:
  https://xmake.io/#/guide/syntax_description?id=code-formatting
[add_requires - xmake]:
  https://xmake.io/#/manual/global_interfaces?id=add_requires