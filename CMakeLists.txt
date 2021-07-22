cmake_minimum_required(VERSION 3.19)
project(Index)

set(CMAKE_CXX_STANDARD 20)

add_executable(Index main.cc Index/Include/Include_Index/index_impl/ui/ui.cc)

add_subdirectory(Index)