//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_QUADRILATERAL_H
#define EX3_QUADRILATERAL_H

#include <array>

template<int N>
class Polygon {
protected:
    std::array<std::array<double,2>,N> _corners;
    std::string _name;

public:
    Polygon();

    Polygon(std::array<std::array<double,2>,N> _Corners);

    ~Polygon() = default;

    double circumference();
    double area();
    std::array<double,2> coord(int _Number);
    std::string name();

    void printNameCircumferenceArea();

    double distance(std::array<double, 2> x, std::array<double, 2> y);

    Polygon<N>& operator=(std::initializer_list<int>& list);
};


#endif //EX3_QUADRILATERAL_H
