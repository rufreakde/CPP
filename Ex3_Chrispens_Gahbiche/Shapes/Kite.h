//
// Created by Rudolf Chrispens on 08.11.17.
//

#ifndef EX3_KITE_H
#define EX3_KITE_H


#include "Quadrilateral.h"

class Kite : public Quadrilateral {
public:
    Kite();
    Kite(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4);
    ~Kite();
};


#endif //EX3_KITE_H
