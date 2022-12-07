cmake_minimum_required(VERSION 3.15.0)

project(wordle)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(
  wordle
  src/cli.cxx
)
target_link_libraries(wordle ${CONAN_LIBS})
