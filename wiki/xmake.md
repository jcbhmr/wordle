```lua
if is_plat("linux", "macosx") then
    add_syslinks("pthread")
end
```

```sh
xmake f -m release
xmake f -m debug
```
