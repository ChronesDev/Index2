add_executable(IndexTest1 main.cc)

target_link_libraries(IndexTest1 PUBLIC IndexInclude)
target_include_directories(IndexTest1 PUBLIC ../../Index/Include/Include_Index/)