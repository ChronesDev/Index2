cmake_minimum_required(VERSION 3.18.3)
project(Index)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(IndexTest index.cc)

target_compile_options(IndexTest PUBLIC "-fdeclspec" "-fms-extensions")

# Include Dirs
set(Index_IncludeDir "./Index/Include/Include_Index/")
set(IndexMem_IncludeDir "./Index/Include/Include_IndexMem/")
set(IndexUI_IncludeDir "./Index/Include/Include_IndexUI/")

target_include_directories(IndexTest PUBLIC ${Index_IncludeDir})
target_include_directories(IndexTest PUBLIC ${IndexMem_IncludeDir})
target_include_directories(IndexTest PUBLIC ${IndexUI_IncludeDir})


# Testing
add_subdirectory(Test)