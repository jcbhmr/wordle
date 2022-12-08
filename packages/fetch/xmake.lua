set_project("fetch")
set_version("1.0.0")
set_xmakever("2.7.3") -- As of 2022/12/07, this is the latest version of xmake.

add_requires("conan::cpr/1.9.0", {alias="cpr"})

target("fetch") do
  set_kind("static")
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
  add_headerfiles("src/*.h", {prefixdir = "fetch"})
  add_packages("cpr")
end

target("fetch/test/example") do
  set_kind("binary")
  set_languages("clatest", "cxxlatest")
  add_files("test/example.cpp")
  add_deps("fetch")
end

target("fetch/test/json") do
  set_kind("binary")
  set_languages("clatest", "cxxlatest")
  add_files("test/json.cpp")
  add_deps("fetch")
end
