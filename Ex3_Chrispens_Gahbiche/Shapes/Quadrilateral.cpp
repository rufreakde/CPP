//
// Created by Rudolf Chrispens on 08.11.17.
//

#include "Quadrilateral.h"

//Constructors
Quadrilateral::Quadrilateral(){}
Quadrilateral::Quadrilateral(std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4) {
    _corners = {_Corner1, _Corner2, _Corner3, _Corner4};
}

//functions
double Quadrilateral::circumference() {
    double tCircumfence = 0;

    return 0;
}

double Quadrilateral::area() {
    auto coord1 = _corners[0];
    auto coord2 = _corners[1];
    auto coord3 = _corners[2];
    auto coord4 = _corners[3];

    /*coords AC{(coord3.x - coord1.x), (coord3.y - coord1.y)};
    coords BD{(coord4.x - coord2.x), (coord4.y - coord2.y)};
    double crossResult = (AC.x * BD.y) - (AC.y * BD.x);
    return crossResult * 1/2;*/
}

std::array<double,2> Quadrilateral::coord(int _Number) {
    if (_Number > 3 || _Number < 0) {
        throw std::out_of_range("Please choose a coordinate in the Range 0 - 3");
    }
    return _corners[_Number];
}

std::string Quadrilateral::name(){
    return _name;
}

std::array<double, 2>  Quadrilateral::project_point_on_line(std::array<double, 2> point,
                                           std::array<double, 2> line_point1,
                                           std::array<double, 2> line_point2) {


    std::array<double, 2> proj_point;
}


void Quadrilateral::printNameCircumferenceArea(){
    std::cout << "#######################" << std::endl;
    std::cout << "# Name:  " << name() << std::endl;
    std::cout << "# Circumference: " << circumference() << std::endl;
    std::cout << "# Area: " << area() << std::endl;
    std::cout << "#######################" << std::endl;
}