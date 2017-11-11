//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_PARALLELOGRAM_H
#define EX3_PARALLELOGRAM_H


#include <vector>
#include "Trapezoid.h"

class Parallelogram : public Trapezoid {

    std::vector<Parallelogram> _subdivisions;

public:
    Parallelogram();
    Parallelogram(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Parallelogram();

    virtual void subdivide();
    virtual std::array<double,2> midPoint(std::array<double, 2> p1, std::array<double, 2> p2);
    virtual void printSubdivisions();
};


#endif //EX3_PARALLELOGRAM_H
