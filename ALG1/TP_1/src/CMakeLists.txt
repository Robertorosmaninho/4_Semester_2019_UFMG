cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(src
        include/graph.h
        graph.cpp
        main.cpp)
