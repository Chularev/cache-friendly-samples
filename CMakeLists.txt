cmake_minimum_required(VERSION 3.13)
project(cache_friendly)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-O0)
include(PerfProfiling.cmake)

add_executable(linked_list linked_list.cpp)
perf_profile(linked_list)

add_executable(linear_array linear_array.cpp)
perf_profile(linear_array)

add_executable(bsearch_array bsearch_array.cpp)
perf_profile(bsearch_array)

add_executable(map map.cpp)
perf_profile(map)

add_executable(heap_aux heap_aux.cpp)
perf_profile(heap_aux)

add_executable(bheap_aux bheap_aux.cpp)
perf_profile(bheap_aux)

add_subdirectory(arrays)
