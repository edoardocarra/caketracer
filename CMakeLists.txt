cmake_minimum_required (VERSION 3.9)

project(caketracer)

set(CMAKE_CXX_STANDARD 14)

add_library(trace_lib STATIC trace.cpp trace.h)

add_executable(viewer viewer.cpp)

target_link_libraries(viewer trace_lib)
