//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_ISOSCELESTRAPEZOID_H
#define EX3_ISOSCELESTRAPEZOID_H


#include "Trapezoid.h"

class IsoscelesTrapezoid : public Trapezoid
{
public:
    IsoscelesTrapezoid();
    IsoscelesTrapezoid(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~IsoscelesTrapezoid();

};


#endif //EX3_ISOSCELESTRAPEZOID_H
