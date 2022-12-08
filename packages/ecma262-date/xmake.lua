set_project("ecma262-date")
set_version("1.0.0")
set_xmakever("2.7.3") -- As of 2022/12/07, this is the latest version of xmake.

target("ecma262-date") do
  set_kind("static")
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
  add_headerfiles("src/*.h", {prefixdir = "ecma262-date"})
end

target("ecma262-date/test/now") do
  set_kind("binary")
  set_languages("clatest", "cxxlatest")
  add_files("test/now.cpp")
  add_deps("ecma262-date")
end
