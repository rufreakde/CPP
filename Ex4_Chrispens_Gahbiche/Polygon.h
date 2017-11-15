#ifndef EX4_POLYGON_H
#define EX4_POLYGON_H

#include <array>
#include <cmath>
#include <iostream>

template<int N>
class Polygon {
protected:
    std::array<std::array<double,2>, N> _corners;
    std::string _name;

public:
    Polygon();

    explicit Polygon(std::array<std::array<double,2>, N> _Corners) : _corners(_Corners) {
            _name = std::to_string(N) + "-gon";
        std::cout << std::to_string(N) << std::endl;
    }

    ~Polygon() = default;

    double circumference(){

        double tCircumfence = 0;
        for (std::size_t i = 0; i+1 != _corners.size(); ++i) {
            tCircumfence += distance(_corners[i], _corners[i+1]);
        }
        tCircumfence += distance(_corners[_corners.size() -1], _corners[0]);

        //double tCircumfence = distance(a, b) + distance(b, c) + distance(c, d) + distance(d, a);

        return tCircumfence;
    };
    double area(){

        double area = 0.0f;
        for (int i = 0; i < _corners.size() - 1; ++i)
            area += _corners[i][0] * _corners[i+1][1] - _corners[i+1][0] * _corners[i][1];

        area += _corners[_corners.size()-1][0] * _corners[0][1] - _corners[0][0] * _corners[_corners.size()-1][1];

        area = abs(area) / 2.0f;
        return area;

        /*double area = 0.0f;
        for (int i = 0; i < _corners.size() - 1; ++i)
            area += _corners[i].x * _corners[i+1].y - _corners[i+1].x * _corners[i].y;

        area += _corners[_corners.size()-1].x * _corners[0].y - _corners[0].x * _corners[_corners.size()-1].y;

        area = abs(area) / 2.0f;
        return area;*/
    };
    std::array<double,2> coord(int _Number){
        if (_Number >= _corners.size() || _Number < 0) {
            throw std::out_of_range("Please choose a coordinate in the Range");
        }
    };
    std::string name(){
        return _name;
    };

    void printNameCircumferenceArea(){
        std::cout << "############################" << std::endl;
        std::cout << "# Name:\t\t" << name() << std::endl;
        std::cout << "# Circumference:\t" << this->circumference() << std::endl;
        std::cout << "# Area:\t\t" << this->area() << std::endl;
        std::cout << "############################" << std::endl;
    };

    double distance(std::array<double, 2> x, std::array<double, 2> y){
        return std::sqrt(pow( x[0] - y[0] ,2) + pow( x[1] - y[1] ,2));
    };

    Polygon<N>& operator=(std::initializer_list<int>& list){
        return *this;
    };
};


#endif //EX4_POLYGON_H
