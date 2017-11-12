//
// Created by Habib Gahbiche on 12/11/2017.
//

#ifndef EX3_SPECIALIZEDRECTANGLE_H
#define EX3_SPECIALIZEDRECTANGLE_H


#include <array>
#include "../Interfaces/Quad.h"
#include "Parallelogram.h"

class SpecializedRectangle : public Parallelogram{
public:
    // constructor
    SpecializedRectangle(const std::array<double, 2> _corner1, const std::array<double, 2> _corner2,
                         double _length);

    SpecializedRectangle();
    std::array<double, 2> coord(int i) override ;
    double circumference() override ;
    double area() override ;
private:
    std::array<std::array<double ,2>, 2> _corners;
    double _length;
};


#endif //EX3_SPECIALIZEDRECTANGLE_H
