//
// Created by Rudolf Chrispens on 11.11.17.
//
/*
 * Create a class Quad3D which stores a quad and a thickness,
 * thus extending any Quad into a 3D shape.
 * It should support the functions surface() and volume().
 * If Quad3D is constructed with an rvalue,
 * then Quad3D should take ownership of it, otherwise
 * it should create a copy. Quad3D itself should be copyable and movable.
 * Test this with initializations using rvalue and
 * lvalue and assignments using rvalue and lvalue.
 */

#ifndef EX3_QUAD3D_H
#define EX3_QUAD3D_H


#include "../shapes/Quadrilateral.h"

class Quad3D {
protected:
    Quadrilateral _quad;
    double _thickness;

public:
    double surface();
    double volume();
    void setThickness(double _Thickness);

    Quad3D(const Quad &_Quad2D);
    Quad3D &operator=(const Quad &_Quad2D);
    Quad3D &operator=(Quad &&_Quad2D);
    Quad3D(Quad &&_Quad2D);

    Quad3D(const Quad3D &_Quad3D);
    Quad3D &operator=(const Quad3D &_Quad3D);
    Quad3D &operator=(Quad3D &&_Quad3D);
    Quad3D(Quad3D &&_Quad3D);

};


#endif //EX3_QUAD3D_H
