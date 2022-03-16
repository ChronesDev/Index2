add_executable(Test_ImSDL main.cc)

target_include_directories(Test_ImSDL PUBLIC ./)
target_include_directories(Test_ImSDL PUBLIC ../../Index/Include/Include_Index)
target_include_directories(Test_ImSDL PUBLIC ../../Index/Include/Include_IndexUI)

find_package(OpenGL REQUIRED)

find_package(SDL2 REQUIRED)
target_link_libraries(Test_ImSDL PUBLIC SDL2::SDL2)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(Test_ImSDL PUBLIC imgui::imgui)