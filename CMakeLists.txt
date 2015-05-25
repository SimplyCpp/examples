cmake_minimum_required(VERSION 3.2)
project(exemplos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    constructor.cpp
    example_main.h
    hello.cpp
    macro_templ.cpp
    output_iterator.cpp
    sizes.cpp
    stop_watch.cpp)

add_executable(exemplos ${SOURCE_FILES})