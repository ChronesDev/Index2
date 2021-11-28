# add_subdirectory(Yoga)

file(GLOB_RECURSE Lib_Yoga_SrcFiles "SimpleYoga/yoga/*.cpp")
add_library(yogacore STATIC ${Lib_Yoga_SrcFiles})
target_include_directories(yogacore PRIVATE "SimpleYoga/")