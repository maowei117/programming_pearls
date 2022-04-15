cmake_minimum_required (VERSION 3.0)
project(Programming_Pearls)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -g -Wall -Werror -fPIC")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

add_executable("random_test" src/random_test.cpp)

add_executable("1_1" src/1_1.cpp)
add_executable("1_2" src/1_2.cpp src/BitSet.cpp)
add_executable("1_3" src/1_3.cpp src/BitSet.cpp)
add_executable("1_4" src/1_4.cpp)
add_executable("1_5" src/1_5.cpp src/BitSet.cpp)