cmake_minimum_required(VERSION 3.3)
project(lab3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -std=c++11")

set(SOURCE_FILES main.cpp wndProc.cpp resource.h resource.rc LineClass.cpp LineClass.h RectangleClass.cpp RectangleClass.h)
add_executable(lab3 ${SOURCE_FILES})