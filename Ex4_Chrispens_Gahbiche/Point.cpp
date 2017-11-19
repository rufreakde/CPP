//
// Created by Habib Gahbiche on 15/11/2017.
//

#include <cmath>
#include <iostream>
#include "Point.h"

Point::Point(double x, double y) : x(x), y(y) {}

Point::Point() {
    x = double(rand() % 100);
    y = double(rand() % 100);
    //std::cout << "x und y:    " <<  x << "|" << y << std::endl;
}

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
    return std::sqrt( pow(x - rhs.x, 2) + pow(y - rhs.y, 2) );
}

Point &Point::operator=(const Point &rhs) {
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

void Point::print() {
    std::cout << x << "\t" << y << std::endl;
}

const Point Point::midsegment_to(const Point &rhs) {
    return Point{(x+rhs.x)/2, (y+rhs.y)/2};
}


