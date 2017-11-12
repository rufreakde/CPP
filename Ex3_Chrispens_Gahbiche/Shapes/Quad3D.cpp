//
// Created by Rudolf Chrispens on 11.11.17.
//


#include "Quad3D.h"

//functions
double Quad3D::surface() {
    double extra_surface = 0;

    for(int i=0; i<4; i++){
        int j = i%4;
        extra_surface += _thickness * distance(_quad.coord(i), _quad.coord(j));
    }
    double surface = extra_surface + 2 * _quad.area();

    return surface;
}
double Quad3D::volume() {
    return _thickness * _quad.area();
}
double Quad3D::distance(std::array<double, 2> x, std::array<double, 2> y) {
    return std::sqrt(pow( x[0] - y[0] ,2) + pow( x[1] - y[1] ,2));
}
void Quad3D::setThickness(double _Thickness) {
    _thickness = _Thickness;
}


// constructors
Quad3D::Quad3D(const Quadrilateral &_quad, double _thickness) :
        _quad(_quad), _thickness(_thickness) {
    std::cout << "used constructor with thickness" << std::endl;
}
Quad3D::Quad3D(const Quadrilateral &_quad) :
        _quad(_quad) {
    std::cout << "used constructor without thickness" << std::endl;
}

//operators QUAD2D
Quad3D::Quad3D(const Quad &_Quad2D) {
    std::cout << "ERROR NOT IMPLEMENTED YET!" << std::endl;
    //_quad = dynamic_cast<Quadrilateral&>(_Quad2D);
}
Quad3D &Quad3D::operator=(const Quad &_Quad2D) {
    std::cout << "ERROR NOT IMPLEMENTED YET!" << std::endl;
    //_quad = dynamic_cast<Quadrilateral&>(_Quad2D);
    return *this;
}
Quad3D &Quad3D::operator=(Quad &&_Quad2D) {
    std::cout << "ERROR NOT IMPLEMENTED YET!" << std::endl;
    //_quad = dynamic_cast<Quadrilateral&>(std::move(_Quad2D));
    return *this;
}
Quad3D::Quad3D(Quad &&_Quad2D) {
    std::cout << "ERROR NOT IMPLEMENTED YET!" << std::endl;
    //_quad = dynamic_cast<Quadrilateral&>(std::move(_Quad2D));
}

//operators QUAD3D
// copy constructor
Quad3D::Quad3D(const Quad3D &_Quad3D) {
    _thickness = _Quad3D._thickness;
    _quad = _Quad3D._quad;
    std::cout << "used copy constructor" << std::endl;
}
Quad3D &Quad3D::operator=(const Quad3D &_Quad3D) {
    _thickness = _Quad3D._thickness;
    _quad = _Quad3D._quad;
    std::cout << "used copy assignment " << std::endl;
    return *this;
}
Quad3D &Quad3D::operator=(Quad3D &&_Quad3D) {
    _thickness = std::move(_Quad3D._thickness);
    _quad = std::move(_Quad3D._quad);
    std::cout << "used move assignment " << std::endl;
    return *this;
}
Quad3D::Quad3D(Quad3D &&_Quad3D) : _thickness{_Quad3D._thickness}, _quad{_Quad3D._quad} {
    //_thickness = std::move(_Quad3D._thickness);
    //_quad = std::move(_Quad3D._quad);
    std::cout << "used move constructor" << std::endl;
}