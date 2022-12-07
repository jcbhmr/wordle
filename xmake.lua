add_rules("mode.debug", "mode.release")
-- add_requires("conan::cpr/1.9.0")
-- add_requires("conan::ftxui/3.0.0")
add_requires("conan::nlohmann_json/3.11.2")

includes("packages/*/xmake.lua")

target("wordle")
  set_kind("binary")
  add_packages("ftxui", "nlohmann_json")
  add_files("src/*.cxx")
  add_deps("fetch")
