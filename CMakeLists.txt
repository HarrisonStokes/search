cmake_minimum_required(VERSION 3.10)

project(way)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/lib/flags.cc
	src/lib/config.cc
	src/lib/cmdline.cc
	src/lib/search.cc
	src/main.cc
)

add_executable(way ${SOURCES})

#include_directories(src)

