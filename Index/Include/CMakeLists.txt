add_subdirectory(Include_Index)

target_link_libraries(Index PUBLIC IndexInclude)
target_include_directories(Index PUBLIC Include_Index/)