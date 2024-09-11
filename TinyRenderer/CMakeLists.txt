cmake_minimum_required(VERSION 3.16)

set(LibraryName "TinyRenderer")
set(TR_SRC
		src/library.cpp
		src/Math.cpp
		include/TinyRenderer/Math.hpp
)

file(GLOB_RECURSE TR_VENDORS_SRC CONFIGURE_DEPENDS vendors_src/*.cpp vendors_src/*.cxx  vendors_src/*.c)

add_library(${LibraryName} STATIC ${TR_SRC} ${TR_VENDORS_SRC})

target_include_directories(${LibraryName} PUBLIC  include)
target_include_directories(${LibraryName} PRIVATE vendors_include)
target_include_directories(${LibraryName} PRIVATE src)