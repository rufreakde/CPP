//
// Created by Habib Gahbiche on 15/11/2017.
//

#include <cmath>
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

Point Point::operator+(const Point &rhs) {
    return Point{this->x + rhs.x, this->y + rhs.y};
}

Point Point::operator-(const Point &rhs) {
    return Point{this->x - rhs.x, this->y - rhs.y};
}

double Point::distance_to(const Point &rhs) {
    return std::sqrt( pow(this->x+rhs.x, 2) + pow(this->y + rhs.y, 2) );
}


