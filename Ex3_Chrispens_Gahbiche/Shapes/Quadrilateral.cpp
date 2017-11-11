//
// Created by Rudolf Chrispens on 08.11.17.
//

#include <cmath>
#include <utility>
#include "Quadrilateral.h"

//Constructors
Quadrilateral::Quadrilateral(): Quad(){}
Quadrilateral::Quadrilateral(std::string _Name,
                             std::array<double,2> _Corner1,
                             std::array<double,2> _Corner2,
                             std::array<double,2> _Corner3,
                             std::array<double,2> _Corner4) {
    _corners = {_Corner1, _Corner2, _Corner3, _Corner4};
    _name = std::move(_Name);
}
Quadrilateral::~Quadrilateral(){};
Quad::~Quad(){};

//functions~
double Quadrilateral::circumference() {
    auto a = _corners[0];
    auto b = _corners[1];
    auto c = _corners[2];
    auto d = _corners[3];

    double tCircumfence = distance(a, b) + distance(b, c) + distance(c, d) + distance(d, a);

    return tCircumfence;
}

double Quadrilateral::area() {
    // we use Bretschneider's formula
    // wikipedia.org/wiki/Bretschneider%27s_formula

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
                                  std::pow((b*b +d*d - a*a - c*c),2));

    return area;

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

std::array<double, 2>  Quadrilateral::project_point_on_line(std::array<double, 2> x,
                                           std::array<double, 2> a,
                                           std::array<double, 2> b) {


    std::array<double, 2> proj_point{0,0};

    // Geradengleichung:
    // y = a*x +b
    double l = x[0]*(b[0]-a[0]) +x[1]*(b[1] - a[1]);
    double s = (b[1] - a[1]) / (b[0] - a[0]);

    proj_point[1] = l/(b[0] - a[0]) + b[1] - (b[0]*l)/(b[0] - a[0]);
    proj_point[0] = - proj_point[1] * s + l / (b[0] -a[0]);

    return proj_point;
    
}



void Quadrilateral::printNameCircumferenceArea(){
    std::cout << "############################" << std::endl;
    std::cout << "# Name:\t\t" << name() << std::endl;
    std::cout << "# Circumference:\t" << circumference() << std::endl;
    std::cout << "# Area:\t\t" << area() << std::endl;
    std::cout << "############################" << std::endl;
}

double Quadrilateral::distance(std::array<double, 2> x, std::array<double, 2> y) {
    return std::sqrt(pow( x[0] - y[0] ,2) + pow( x[1] - y[1] ,2));
}

double Quadrilateral::area_right_triangle(std::array<double, 2> a, std::array<double, 2> b_right, std::array<double, 2> c){
    // 90 grad winkel liegt bei b_right
    double dist = 0;
    dist = (distance(a, b_right) * distance(a, c))/2;
    return dist;
}
