//
// Created by Habib Gahbiche on 15/11/2017.
//

#ifndef EX4_CHRISPENS_GAHBICHE_POINT_H
#define EX4_CHRISPENS_GAHBICHE_POINT_H


class Point {
public:
    Point(double x, double y);
    Point();

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    double x = 0;
    double y = 0;
};


#endif //EX4_CHRISPENS_GAHBICHE_POINT_H
