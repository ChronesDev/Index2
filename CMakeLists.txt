cmake_minimum_required(VERSION 3.19)
project(Index)

set(CMAKE_CXX_STANDARD 20)

add_executable(Index main.cc src/Window.h)
add_subdirectory(Index)