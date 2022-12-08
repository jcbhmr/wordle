set_project("html-location")
set_version("1.0.0")
set_xmakever("2.7.3") -- As of 2022/12/07, this is the latest version of xmake.

add_requires("conan::skyr-url/1.13.0", {alias="skyr-url"})

target("html-location") do
  set_kind("static")
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
  add_headerfiles("src/*.h", {prefixdir = "html-location"})
  add_packages("skyr-url")
end
