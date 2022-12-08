add_requires("conan::cpr/1.9.0", {alias="cpr"})

target("fetch") do
  set_kind("static")
  add_files("src/*.cpp")
  add_headerfiles("src/*.h", {prefixdir = "fetch"})
  add_packages("cpr")
end
