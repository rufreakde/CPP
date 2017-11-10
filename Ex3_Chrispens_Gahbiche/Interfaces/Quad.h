//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_QUAD_H
#define EX3_QUAD_H

#include <iostream>
#include <array>

class Quad {
public:
    //constructors
    //Quad();
    //~Quad();

    //Functions
    virtual double circumference() = 0; //umfang
    virtual double area() = 0; //fläche
    virtual std::array<double,2> coord(int i) = 0; //i = winkel 0...3
    virtual std::string name() = 0; //typename
    //virtual void printNameCircumferenceArea();
};


#endif //EX3_QUAD_H
