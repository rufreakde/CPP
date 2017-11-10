//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_PARALLELOGRAM_H
#define EX3_PARALLELOGRAM_H


#include "Trapezoid.h"

class Parallelogram : public Trapezoid {
public:
    Parallelogram();
    Parallelogram(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Parallelogram();
};


#endif //EX3_PARALLELOGRAM_H
