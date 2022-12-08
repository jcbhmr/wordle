```lua
if is_plat("linux", "macosx") then
    add_syslinks("pthread")
end
```

```sh
xmake f -m release
xmake f -m debug
```

```sh
add_requires("conan::fmt/9.0.0", {alias="fmt"})
```

https://xmake.io/#/guide/syntax_description?id=code-formatting

https://xmake.io/#/package/local_package
