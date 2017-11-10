//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_SQUARE_H
#define EX3_SQUARE_H


#include "Rectangle.h"

class Square: public Rectangle{
public:
    Square();
    Square(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Square();
};


#endif //EX3_SQUARE_H
