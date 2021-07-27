add_subdirectory(ImUI)
add_subdirectory(notification)

target_sources(Index PRIVATE
        include.cc
        ui.cc
        macros/index_ui_macros.cc
        macros/index_ui_macros_end.cc)