cmake_minimum_required(VERSION 3.8)
project(Ex3)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Shapes/Quadrilateral.cpp Shapes/Quadrilateral.h Shapes/Kite.cpp Shapes/Kite.h Shapes/Rhombus.cpp Shapes/Rhombus.h Shapes/Square.cpp Shapes/Square.h Shapes/Parallelogram.cpp Shapes/Parallelogram.h Shapes/Trapezoid.cpp Shapes/Trapezoid.h Shapes/IsoscelesTrapezoid.cpp Shapes/IsoscelesTrapezoid.h Shapes/Rectangle.cpp Shapes/Rectangle.h Interfaces/Quad.h Shapes/Quad3D.cpp Shapes/Quad3D.h Shapes/SpecializedRectangle.cpp Shapes/SpecializedRectangle.h Shapes/SpecializedSquare.cpp Shapes/SpecializedSquare.h)

add_executable(Ex3 ${SOURCE_FILES})