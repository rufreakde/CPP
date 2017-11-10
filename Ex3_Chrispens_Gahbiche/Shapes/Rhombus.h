//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_RHOMBUS_H
#define EX3_RHOMBUS_H


#include "Kite.h"

class Rhombus : public Kite {
public:
    Rhombus();
    Rhombus(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Rhombus();
};


#endif //EX3_RHOMBUS_H
