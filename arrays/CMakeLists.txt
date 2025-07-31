cmake_minimum_required(VERSION 3.13)
project(cache_friendly)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O0)

add_library(lib_linear_array STATIC
    common.h
    simple_linear_array.h simple_linear_array.cpp
    move_backward_linear_array.h
)
target_include_directories(lib_linear_array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(base_linear_array base_linear_array_main.cpp)
target_link_libraries(base_linear_array lib_linear_array)

add_executable(my_linear_array move_backward_linear_array_main.cpp)
add_executable(my_linear_array2 my_linear_array2.cpp)

