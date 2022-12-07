set_project("wordle")
set_version("1.0.0", { build = "%Y%m%d%H%M" })
add_rules("mode.debug", "mode.release")

add_requires("conan::ftxui/3.0.0")
add_requires("conan::nlohmann_json/3.11.2")
add_requires("conan::cpr/1.9.0")

target("wordle")
    set_kind("binary")
    set_languages("cxxlatest")
    set_warnings("all", "error")
    add_packages("ftxui", "nlohmann_json", "cpr")
    add_files("src/*.cxx")
    if is_plat("linux", "macosx") then
        add_syslinks("pthread")
    end
