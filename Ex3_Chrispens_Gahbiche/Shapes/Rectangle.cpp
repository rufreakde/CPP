//
// Created by Rudolf Chrispens on 08.11.17.
//

#include "Rectangle.h"

Rectangle::Rectangle() {}

Rectangle::~Rectangle() = default;

Rectangle::Rectangle(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4) {
    _corners = {_Corner1, _Corner2, _Corner3, _Corner4};
    _name = _Name;
}

void Rectangle::subdivide() {
    _subdivide();
}

void Rectangle::_subdivide() {
    Parallelogram::_subdivide<Rectangle>();
}