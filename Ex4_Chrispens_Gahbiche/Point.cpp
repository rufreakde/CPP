//
// Created by Habib Gahbiche on 15/11/2017.
//

#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point() {}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}
