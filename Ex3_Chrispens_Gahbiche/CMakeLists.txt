cmake_minimum_required(VERSION 3.8)
project(Ex3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Shapes/Quadrilateral.cpp Shapes/Quadrilateral.h Interfaces/Quad.cpp Interfaces/Quad.h)

add_executable(Ex3 ${SOURCE_FILES})