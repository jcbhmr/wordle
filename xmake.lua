set_project("wordle")
set_version("1.0.0")
set_xmakever("2.7.3") -- As of 2022/12/07, this is the latest version of xmake.

-- The mode.debug rule adds debug symbols when xmake f -m debug. The mode.release
-- rule compiles with extra optimization flags when xmake f -m release.
-- 📚 Docs: https://xmake.io/#/manual/custom_rule?id=modedebug
-- 📚 Docs: https://xmake.io/#/manual/custom_rule?id=moderelease
add_rules("mode.debug", "mode.release")

-- These are all the dependencies that this project uses. These aren't bound to
-- a particular target; this is just the INSTALLATION phase. Later we need to
-- include these definitions in a particular targets linker config.
--
-- ⚠️ The {alias="..."} option is incredibly crucial! Without this, the #include
-- statements won't work. We don't know exactly WHY this happens, but we have
-- noticed that all the official (and supporting) docs always include the alias
-- config option.
add_requires("conan::ftxui/3.0.0", {alias="ftxui"})
add_requires("conan::nlohmann_json/3.11.2", {alias="nlohmann_json"})
add_requires("conan::argparse/2.9", {alias="argparse"})

-- This adds the build/packages/ index generated by xmake package -P . from the
-- packages/*/ subfolders to the repository index. This means we can then use
-- add_requires() with those packages as unqualified names to load them from
-- a local copy. We just need to make sure that we rebuild those packages if
-- they change, and update their version accordingly.
--
-- 📚 Docs: https://xmake.io/#/package/local_package?id=default-packaging-format
-- 📚 Docs: https://xmake.io/#/manual/global_interfaces?id=add_repositories
add_repositories("local-repo build", {rootdir = os.scriptdir()})
add_requires("fetch")

-- This is the root target for the worlde binary. This is the main entry point
-- of the project. Expect the CLI main() function to be in src/cli.cpp.
target("wordle") do
  set_kind("binary")
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
  add_packages("ftxui", "nlohmann_json", "fetch", "argparse")
end
