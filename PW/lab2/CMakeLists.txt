cmake_minimum_required(VERSION 3.3)
project(lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -std=c++11")

set(SOURCE_FILES main.cpp resource.h resource.rc registerClass.h)
add_executable(lab2 ${SOURCE_FILES})