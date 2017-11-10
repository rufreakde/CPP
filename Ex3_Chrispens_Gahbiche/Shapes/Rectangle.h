//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_RECTANGLE_H
#define EX3_RECTANGLE_H


#include "Parallelogram.h"

class Rectangle : public Parallelogram {
public:
    Rectangle();
    Rectangle(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Rectangle();
};


#endif //EX3_RECTANGLE_H
