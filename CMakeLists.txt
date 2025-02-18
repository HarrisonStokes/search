cmake_minimum_required(VERSION 3.10)

project(way)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
	src/flags.cc
	src/config.cc
	src/cmdline.cc
	src/search.cc
	src/main.cc
)

add_executable(way ${SOURCES})

#include_directories(src)

