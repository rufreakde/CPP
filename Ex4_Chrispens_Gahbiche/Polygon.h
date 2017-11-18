#ifndef EX4_POLYGON_H
#define EX4_POLYGON_H

#include <array>
#include <cmath>
#include <iostream>
#include "Point.h"

template<int N>
class Polygon {

public:
    Polygon() {}

    explicit Polygon(std::array<Point, N> _Corners) : _corners(_Corners) {
            _name = std::to_string(N) + "-gon";
    }

    ~Polygon() = default;

    double circumference(){

        double tCircumfence = 0;
        for (std::size_t i = 0; i != _corners.size() - 1; ++i) {
            tCircumfence += _corners[i].distance_to(_corners[i+1]);
        }
        tCircumfence += _corners[_corners.size() -1].distance_to( _corners[0]);
        return tCircumfence;

    };
    double area(){
        double area = 0.0f;
        for (int i = 0; i < _corners.size() - 1; ++i)
            area += (_corners[i].x * _corners[i+1].y) - (_corners[i+1].x * _corners[i].y);

        //area += _corners[_corners.size()-1].x * _corners[0].y - _corners[0].x * _corners[_corners.size()-1].y;

        area = fabs(area) * 0.5f;
        return area;
    };
    Point coord(int _Number){
        if (_Number >= _corners.size() || _Number < 0) {
            throw std::out_of_range("Please choose a coordinate in the Range");
        } else {
            return _corners[_Number];
        }
    };
    std::string name(){
        return _name;
    };

    int size(){
        return N;
    }

    void printNameCircumferenceArea(){
        std::cout << "############################" << std::endl;
        std::cout << "# Name:\t\t" << name() << std::endl;
        std::cout << "# Circumference:\t" << this->circumference() << std::endl;
        std::cout << "# Area:\t\t" << this->area() << std::endl;
        std::cout << "############################" << std::endl;
    };

    Polygon<N>& operator=(std::initializer_list<int>& list){
        return *this;
    };

protected:
    std::array<Point, N> _corners;
    std::string _name;
};


#endif //EX4_POLYGON_H
