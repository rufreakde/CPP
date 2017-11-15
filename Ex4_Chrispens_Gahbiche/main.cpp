#include <iostream>
#include <memory>
#include "Polygon.h"

int main() {
    /*
     * Create an 8-gon from the coordinates
        { {0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2} } and check if
        circumference(), area(), coord(int i) return the correct values, since this is actually a
        square { {0,0}, {4,-2}, {6,2}, {2,4} }.
     */

    std::unique_ptr<Polygon<8>> octagon = std::make_unique<Polygon<8>>(std::array<std::array<double,2>,8>{{{0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2}}});
    auto oct = octagon.get();
    oct->printNameCircumferenceArea();

    return 0;
}