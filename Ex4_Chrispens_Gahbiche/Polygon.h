//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_QUADRILATERAL_H
#define EX3_QUADRILATERAL_H

#include <array>

template<int T>
class Polygon {
protected:
    int N;
    std::array<std::array<double,2>,T> _corners;
    std::string _name;

public:
    Polygon() = delete;
    Polygon(std::string _Name,
                  std::array<std::array<double,2>,T>);
    ~Polygon();

    double circumference();
    double area();
    std::array<double,2> coord(int _Number);
    std::string name();

    void printNameCircumferenceArea();

    double distance(std::array<double, 2> x, std::array<double, 2> y);
};


#endif //EX3_QUADRILATERAL_H
