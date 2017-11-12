//
// Created by Habib Gahbiche on 12/11/2017.
//

#ifndef EX3_SPECIALIZEDSQUARE_H
#define EX3_SPECIALIZEDSQUARE_H


#include "SpecializedRectangle.h"

class SpecializedSquare : public SpecializedRectangle {
public:
    SpecializedSquare(const std::array<double, 2> &_corner1, const std::array<double, 2> &_corner2);

    double circumference() override ;
    double area() override ;
    std::array<double, 2> coord(int i) override ;

private:
    std::array<std::array<double, 2>, 2> _corners;

};


#endif //EX3_SPECIALIZEDSQUARE_H
