add_library(IndexUIInclude OBJECT
        index_ui
        index_ui_macros
        index_ui_macros_end)

target_include_directories("../Include_Index/")

add_subdirectory(index_ui_impl)