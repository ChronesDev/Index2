cmake_minimum_required(VERSION 3.19)
project(Index)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(Index_IncludeDir "Index/Include/Include_Index/")
set(IndexUI_IncludeDir "Index/Include/Include_IndexUI/")

add_library(Index OBJECT index.cc)

target_include_directories(Index PUBLIC ${Index_IncludeDir})
target_include_directories(Index PUBLIC ${IndexUI_IncludeDir})
target_link_libraries(Index PUBLIC IndexInclude)
target_link_libraries(Index PUBLIC IndexUIInclude)