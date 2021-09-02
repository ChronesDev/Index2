add_subdirectory(ImUI)
add_subdirectory(notification)

target_sources(IndexInclude PRIVATE
        include.cc
        ui.cc
        ui_std.cc
        macros/index_ui_macros.cc
        macros/index_ui_macros_end.cc)