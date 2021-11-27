add_subdirectory(ui)
add_subdirectory(ui_std)

target_sources(IndexUIInclude PRIVATE
        include.cc
        index.cc)