cmake_minimum_required(VERSION 3.19)
project(Index)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(Index_IncludeDir "Index/Include/Include_Index/")
set(IndexUI_IncludeDir "Index/Include/Include_IndexUI/")

add_executable(IndexTest index.cc)

target_include_directories(IndexTest PUBLIC ${Index_IncludeDir})
target_include_directories(IndexTest PUBLIC ${IndexUI_IncludeDir})