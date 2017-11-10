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
    Quadrilateral(std::array<double,2> _Corner1, std::array<double,2> _Corner2,std::array<double,2> _Corner3,std::array<double,2> _Corner4);
    ~Quadrilateral() = default;

    double circumference();
    double area();
    std::array<double,2> coord(int _Number);
    std::string name();

    std::array<double, 2> project_point_on_line(std::array<double, 2> point, std::array<double, 2> line_point1, std::array<double, 2> line_point2);

    void printNameCircumferenceArea();


};


#endif //EX3_QUADRILATERAL_H
