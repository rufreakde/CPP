//
// Created by Rudolf Chrispens on 08.11.17.
//

#include "Parallelogram.h"

Parallelogram::Parallelogram() {}

Parallelogram::~Parallelogram() = default;

Parallelogram::Parallelogram(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4) {
    _corners = {_Corner1, _Corner2, _Corner3, _Corner4};
    _name = _Name;
}