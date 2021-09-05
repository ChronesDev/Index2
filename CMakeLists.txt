cmake_minimum_required(VERSION 3.19)
project(Index)

set(CMAKE_CXX_STANDARD 20)

set(Index_IncludeDir PUBLIC "Index/Include/Include_Index/")

add_library(Index STATIC index.cc)

target_include_directories(Index PUBLIC ${Index_IncludeDir})
target_link_libraries(Index PUBLIC IndexInclude)