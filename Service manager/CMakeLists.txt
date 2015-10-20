cmake_minimum_required(VERSION 3.2)
project(Service_manager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES servicemanager.cpp servicemanager.h)
add_executable(Service_manager ${SOURCE_FILES})

include_directories(../SettingsLib)