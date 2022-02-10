cmake_minimum_required (VERSION 3.0)
project(Programming_Pearls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -g -Wall -Werror -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

add_executable("1_1" src/1_1.cpp)