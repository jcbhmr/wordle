add_requires("conan::cpr/1.9.0", {alias="cpr"})

target("fetch") do
  set_kind("static")
  set_languages("clatest", "cxxlatest")
  add_files("src/*.cpp")
  add_headerfiles("src/*.h", {prefixdir = "fetch"})
  add_packages("cpr")
end

target("test:example.org") do
  set_kind("binary")
  set_languages("clatest", "cxxlatest")
  add_files("test/example.org.cpp")
  add_deps("fetch")
end
