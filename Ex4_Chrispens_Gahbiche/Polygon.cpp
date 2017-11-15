//
// Created by Rudolf Chrispens on 08.11.17.
//

#include <cmath>
#include <utility>
#include <iostream>
#include "Polygon.h"
#include <string>

//Constructors
template <int N>
Polygon<N>::Polygon(std::array<std::array<double,2>, N> _Corners) {
    _corners = std::move(_Corners);
    _name = std::to_string(N) + "-gon";
}

template <int N>
Polygon<N>::Polygon(){
    _name = std::to_string(N) + "-gon";
};

//functions~
template <int N>
double Polygon<N>::circumference() {
    /*auto a = _corners[0];
    auto b = _corners[1];
    auto c = _corners[2];
    auto d = _corners[3];

    double tCircumfence = distance(a, b) + distance(b, c) + distance(c, d) + distance(d, a);
*/
    std::cout << "NOT IMPLEMENTED YET! - circumference()" << std::endl;
    double tCircumfence = 0;
    return tCircumfence;
}

template <int N>
double Polygon<N>::area() {
    // we use Bretschneider's formula
    // wikipedia.org/wiki/Bretschneider%27s_formula
/*
    auto A = _corners[0];
    auto B = _corners[1];
    auto C = _corners[2];
    auto D = _corners[3];

    // edges
    double a = distance(A, B);
    double b = distance(B, C);
    double c = distance(C, D);
    double d = distance(D, A);

    // diagonals
    double e = distance(A, C);
    double f = distance(D, B);

    double area = 0.25 * std::sqrt(4*e*e*f*f -
                                  std::pow((b*b +d*d - a*a - c*c),2));*/

    std::cout << "NOT IMPLEMENTED YET! - area()" << std::endl;
    double area = 0;
    return area;

}
template <int N>
std::array<double,2> Polygon<N>::coord(int _Number) {
    if (_Number >= _corners.size() || _Number < 0) {
        throw std::out_of_range("Please choose a coordinate in the Range");
    }
    return _corners[_Number];
}

template <int N>
std::string Polygon<N>::name(){
    return _name;
}

template <int N>
void Polygon<N>::printNameCircumferenceArea(){
    std::cout << "############################" << std::endl;
    std::cout << "# Name:\t\t" << name() << std::endl;
    std::cout << "# Circumference:\t" << this->circumference() << std::endl;
    std::cout << "# Area:\t\t" << this->area() << std::endl;
    std::cout << "############################" << std::endl;
}

template <int N>
double Polygon<N>::distance(std::array<double, 2> x, std::array<double, 2> y) {
    return std::sqrt(pow( x[0] - y[0] ,2) + pow( x[1] - y[1] ,2));
}

template <int N>
Polygon<N>& Polygon<N>::operator=(std::initializer_list<int>& list) {
    return *this;
}
