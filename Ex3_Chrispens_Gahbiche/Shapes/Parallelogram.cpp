//
// Created by Rudolf Chrispens on 08.11.17.
//

#include "Parallelogram.h"

Parallelogram::Parallelogram() {}

Parallelogram::~Parallelogram() = default;

Parallelogram::Parallelogram(std::string _Name,std::array<double,2> _Corner1, std::array<double,2> _Corner2, std::array<double,2> _Corner3, std::array<double,2> _Corner4) {
    _corners = {_Corner1, _Corner2, _Corner3, _Corner4};
    _name = _Name;
}

void Parallelogram::subdivide() {
    std::array<double,2> mid = midPoint(coord(0),coord(2));

    auto left = midPoint(coord(0),coord(3));
    auto top = midPoint(coord(0),coord(1));
    auto right = midPoint(coord(1),coord(2));
    auto bottom = midPoint(coord(2),coord(3));

    //we tag the subdivisions with the position of the sub div
    //if we subdivide a subdivision you can see on the name what kind of depth it has!
    _subdivisions.push_back( Parallelogram{_name + "<TL>",coord(0),top,mid,left} );
    _subdivisions.push_back( Parallelogram{_name + "<TR>",top,coord(1),right,mid} );
    _subdivisions.push_back( Parallelogram{_name + "<BR>",mid,right,coord(2),bottom} );
    _subdivisions.push_back( Parallelogram{_name + "<BL>",left,mid,bottom,coord(3)} );
}

std::array<double,2> Parallelogram::midPoint(std::array<double, 2> p1, std::array<double, 2> p2) {
     return { (p1[0] + p2[0])*0.5, (p1[1] + p2[1])*0.5 };

}

void Parallelogram::printSubdivisions(){
    for (auto shape : _subdivisions) {
        std::cout << "# <Subdivisions " << _subdivisions.size() << ">" << std::endl;
        shape.printNameCircumferenceArea();
    }
}