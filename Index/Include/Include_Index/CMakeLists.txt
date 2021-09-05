add_library(IndexInclude STATIC
        index
        index_macros
        index_macros_end
        index_ui
        index_ui_macros
        index_ui_macros_end)

add_subdirectory(index_impl)

# Include Boost