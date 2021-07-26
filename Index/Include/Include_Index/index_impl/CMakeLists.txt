add_subdirectory(core)
add_subdirectory(include)
add_subdirectory(macros)
add_subdirectory(memory)
add_subdirectory(std)
add_subdirectory(ui)

target_sources(IndexInclude PRIVATE include.cc)