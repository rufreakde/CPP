//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_TRAPEZOID_H
#define EX3_TRAPEZOID_H


#include "Quadrilateral.h"

class Trapezoid : public Quadrilateral {
public:
    Trapezoid();
    Trapezoid(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Trapezoid();
};


#endif //EX3_TRAPEZOID_H
