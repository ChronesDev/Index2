add_library(IndexInclude OBJECT
        index
        index_macros
        index_macros_end)

add_subdirectory(index_impl)

# Include Boost