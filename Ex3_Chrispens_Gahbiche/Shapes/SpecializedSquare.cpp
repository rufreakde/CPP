//
// Created by Habib Gahbiche on 12/11/2017.
//

#include <cmath>
#include "SpecializedSquare.h"

double SpecializedSquare::circumference() {
    return 4 * distance(_corners[0], _corners[1]);
}

double SpecializedSquare::area() {
    return pow(distance(_corners[0], _corners[1]), 2);
}

std::array<double, 2> SpecializedSquare::coord(int i) {
    if (i > 3 || i < 0) {
        throw std::out_of_range("Please choose a coordinate in the Range 0 - 3");
    } else if (i == 0 || i == 1){
        return _corners[i];
    } else if (i == 2){
        double ab = distance(_corners[0], _corners[1]);
        // unit vector
        std::array<double, 2> V {_corners[1][0]-_corners[0][0], _corners[1][1] - _corners[0][1]};
        double V_len = sqrt(V[0]*V[0] + V[1]*V[1]);
        //normalize
        V[0] /= V_len; V[1] /= V_len;
        // rotate by -90
        std::array<double, 2> U {(-V[1]), V[0]};
        return std::array<double, 2> {_corners[0][0] - ab * U[0], _corners[0][1] - ab * U[1]};
    } else if (i == 3){
        std::array<double, 2> D = coord(2);
        return std::array<double, 2> {D[0] + _corners[1][0] - _corners[0][0], D[1] + _corners[1][1] - _corners[0][1]};
    }
}

SpecializedSquare::SpecializedSquare(const std::array<double, 2> &_corner1, const std::array<double, 2> &_corner2){
    _corners = {_corner1, _corner2};
}
