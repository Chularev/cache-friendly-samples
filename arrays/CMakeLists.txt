cmake_minimum_required(VERSION 3.13)
project(my_linear_array)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O0)

add_library(lib_linear_array STATIC
    my_blinear_array.h
    empty.cpp

)
target_include_directories(lib_linear_array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(my_blinear_array memmove_linear_array_main.cpp)
target_link_libraries(my_blinear_array lib_linear_array)
perf_profile(my_blinear_array)

add_executable(template bsearch_array.cpp)
perf_profile(template)

add_executable(test_linear_array test_linear_array.cpp)
target_link_libraries(test_linear_array lib_linear_array)




