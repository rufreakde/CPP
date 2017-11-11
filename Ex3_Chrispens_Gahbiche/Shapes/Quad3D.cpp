//
// Created by Rudolf Chrispens on 11.11.17.
//

#include "Quad3D.h"

//functions
double Quad3D::surface() {

    std::cout << "ERROR NOT IMPLEMENTED YET!" << std::endl;
    return 0;
}
double Quad3D::volume() {
    return _thickness * _quad.area();
}
void Quad3D::setThickness(double _Thickness) {
    _thickness = _Thickness;
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
Quad3D::Quad3D(const Quad3D &_Quad3D) {
    _thickness = _Quad3D._thickness;
    _quad = _Quad3D._quad;
}
Quad3D &Quad3D::operator=(const Quad3D &_Quad3D) {
    _thickness = _Quad3D._thickness;
    _quad = _Quad3D._quad;
    return *this;
}
Quad3D &Quad3D::operator=(Quad3D &&_Quad3D) {
    _thickness = std::move(_Quad3D._thickness);
    _quad = std::move(_Quad3D._quad);
    return *this;
}
Quad3D::Quad3D(Quad3D &&_Quad3D) {
    _thickness = std::move(_Quad3D._thickness);
    _quad = std::move(_Quad3D._quad);
}