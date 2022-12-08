set_project("nodejs-fs")
set_version("1.0.0")
set_xmakever("2.7.3") -- As of 2022/12/07, this is the latest version of xmake.

target("nodejs-fs") do
  set_kind("static")
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
  add_headerfiles("src/*.h", {prefixdir = "nodejs-fs"})
end

target("nodejs-fs/test/readFile") do
  set_kind("binary")
  set_languages("clatest", "cxxlatest")
  add_files("test/readFile.cpp")
  add_deps("nodejs-fs")
  add_defines("DIRNAME=\""..os.scriptdir().."/test\"")
end
