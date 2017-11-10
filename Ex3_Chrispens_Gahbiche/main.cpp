#include <iostream>
#include <memory>
#include <vector>
#include <array>

#include "./Interfaces/Quad.h"
#include "./shapes/IsoscelesTrapezoid.h"
#include "./shapes/Kite.h"
#include "./shapes/Parallelogram.h"
#include "./Shapes/Quadrilateral.h"
#include "./shapes/Rectangle.h"
#include "./shapes/Rhombus.h"
#include "./shapes/Square.h"
#include "./shapes/Trapezoid.h"

using namespace std;


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {

    //instances
    /*std::unique_ptr<int> isoscelesTrapezoid( new IsoscelesTrapezoid() );
    Kite kite = Kite();
    Parallelogram parallelogram = Parallelogram();
    Quadrilateral quadrilateral = Quadrilateral();
    Rectangle rectangle = Rectangle();
    Rhombus rhombus = Rhombus();
    Square square = Square();
    Trapezoid trapezoid = Trapezoid();*/

    std::array<std::unique_ptr<Quad>, 1> shapeVector{
            std::unique_ptr<Quad>{new Quadrilateral{}}
    };

    //unique_ptr
    /*
    std::unique_ptr IsoscelesTrapezoidUniquePointer = std::make_unique<Kite>(isoscelesTrapezoid);
    std::unique_ptr KiteUniquePointer = std::make_unique(kite);
    std::unique_ptr ParallelogramUniquePointer = std::make_unique(parallelogram);
    std::unique_ptr QuadrilateralUniquePointer = std::make_unique(quadrilateral);
    std::unique_ptr RectangleUniquePointer = std::make_unique(rectangle);
    std::unique_ptr RhombusUniquePointer = std::make_unique(rhombus);
    std::unique_ptr SquareUniquePointer = std::make_unique(square);
    std::unique_ptr TrapezoidUniquePointer = std::make_unique(trapezoid);*/

    return 0;
}