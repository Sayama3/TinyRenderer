cmake_minimum_required(VERSION 3.16)

project(TinyRenderer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_COMPUTED_DEFAULT "20")

add_subdirectory(Libraries)
add_subdirectory(TinyRenderer)

add_subdirectory(Examples)
# add_subdirectory(Tests)