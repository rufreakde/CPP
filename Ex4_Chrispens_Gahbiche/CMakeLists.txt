cmake_minimum_required(VERSION 3.8)
project(Ex4_Chrispens_Gahbiche)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES main.cpp Polygon.h Point.cpp Point.h sum_circumference.h transform_reduce.h)
add_executable(Ex4 ${SOURCE_FILES})