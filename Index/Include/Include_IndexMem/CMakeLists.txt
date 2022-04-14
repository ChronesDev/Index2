add_library(IndexMemInclude OBJECT
        index_mem)

target_include_directories("../Include_Index/")

add_subdirectory(index_mem_impl)