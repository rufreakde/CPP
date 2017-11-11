//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_QUADRILATERAL_H
#define EX3_QUADRILATERAL_H

#include "../Interfaces/Quad.h"

class Quadrilateral : virtual public Quad{
protected:
    std::array<std::array<double,2>,4> _corners;
    std::string _name;

public:
    Quadrilateral();
    Quadrilateral(std::string _Name,
                  std::array<double,2> _Corner1, std::array<double,2> _Corner2,
                  std::array<double,2> _Corner3,std::array<double,2> _Corner4);

    ~Quadrilateral();

    double circumference();
    double area();
    std::array<double,2> coord(int _Number);
    std::string name();

    void printNameCircumferenceArea();

    double distance(std::array<double, 2> x, std::array<double, 2> y);
};


#endif //EX3_QUADRILATERAL_H
