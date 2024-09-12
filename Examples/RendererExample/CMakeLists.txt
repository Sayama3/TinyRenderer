cmake_minimum_required(VERSION 3.16)

add_executable(RendererExample src/main.cpp)

target_link_libraries(RendererExample PUBLIC TinyRenderer)
