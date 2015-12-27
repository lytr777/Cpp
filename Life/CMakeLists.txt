cmake_minimum_required(VERSION 3.1)
project(Life)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./C/Life")

add_executable(Life main.cpp)