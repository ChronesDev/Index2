add_library(ImGui OBJECT
        Impl/imconfig.h
        Impl/imgui.h
        Impl/imgui.cpp
        Impl/imgui_demo.cpp
        Impl/imgui_draw.cpp
        Impl/imgui_internal.h
        Impl/imgui_tables.cpp
        Impl/imgui_widgets.cpp
        Impl/imstb_rectpack.h
        Impl/imstb_textedit.h
        Impl/imstb_truetype.h
        Impl/backends/imgui_impl_dx9.h
        Impl/backends/imgui_impl_dx9.cpp
        Impl/backends/imgui_impl_win32.h
        Impl/backends/imgui_impl_win32.cpp)
target_include_directories(ImGui PUBLIC "Impl")