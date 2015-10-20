cmake_minimum_required(VERSION 3.1)
project(C_exam)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/Pav/ClionProjects/C_exam")

add_executable(Heap Heap.cpp)