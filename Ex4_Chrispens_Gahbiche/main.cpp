#include <iostream>
#include "Polygon.h"
#include "Point.h"

int main() {
    /*
     * Create an 8-gon from the coordinates
        { {0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2} } and check if
        circumference(), area(), coord(int i) return the correct values, since this is actually a
        square { {0,0}, {4,-2}, {6,2}, {2,4} }.
     */

    //std::unique_ptr<Polygon<8>> octagon = std::make_unique<Polygon<8>>(std::array<std::array<double,2>,8>{{{0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2}}});
    //auto oct = octagon.get();
    //oct->printNameCircumferenceArea();

    Polygon<8> polygon {std::array<Point ,8>{{{0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2}}}};
    polygon.printNameCircumferenceArea();

    Polygon<4> polygon2 {std::array<Point ,4>{{{0,0}, {0,2}, {2,2}, {0,2}}}};
    polygon2.printNameCircumferenceArea();


    Point A{0,0};
    A.print();
    Point B{1,1};
    B.print();
    //copy assignment
    A = B;
    A.print();
    Point C = Point{4,4};
    Point D = Point{1,1};
    C.print();
    std::cout << A.distance_to(B) << std::endl;

    return 0;
}