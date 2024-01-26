cmake_minimum_required(VERSION 3.10)

project(a2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRE True)

add_executable(a2 main.cpp tests.cpp read.cpp util.cpp)

enable_testing()

add_test(NAME a2 COMMAND $<TARGET_FILE:a2>)

