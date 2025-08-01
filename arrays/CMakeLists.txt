cmake_minimum_required(VERSION 3.13)
project(my_linear_array)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O0)

add_library(lib_linear_array STATIC
    common.h
    simple_linear_array.h simple_linear_array.cpp
    move_backward_linear_array.h
)
target_include_directories(lib_linear_array PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(simple_linear_array simple_linear_array_main.cpp)
target_link_libraries(simple_linear_array lib_linear_array)

add_executable(move_backward_linear_array move_backward_linear_array_main.cpp)
target_link_libraries(move_backward_linear_array lib_linear_array)

add_executable(test_linear_array test_linear_array.cpp)
target_link_libraries(test_linear_array lib_linear_array)
