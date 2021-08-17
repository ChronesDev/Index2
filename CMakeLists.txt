cmake_minimum_required(VERSION 3.19)
project(Index)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,10000000")

add_executable(Index main.cc src/Window.h)
add_subdirectory(Index)