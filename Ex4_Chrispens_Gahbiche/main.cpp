#include <iostream>
#include <vector>
#include "Polygon.h"
#include "sum_circumference.h"

int main() {
    /*
     * Create an 8-gon from the coordinates
        { {0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2} } and check if
        circumference(), area(), coord(int i) return the correct values, since this is actually a
        square { {0,0}, {4,-2}, {6,2}, {2,4} }.
     */

    // 4.1
    std::cout << "<----------- 4.1 ----------->" << std::endl;

    Polygon<4> polygon2 {std::array<Point ,4>{{{0,0}, {4,-2}, {6,2}, {2,4}}}};
    polygon2.printNameCircumferenceArea();

    Polygon<8> polygon {std::array<Point ,8>{{{0,0}, {2,-1}, {4,-2}, {5,0}, {6,2}, {4,3}, {2,4}, {1,2}}}};
    polygon.printNameCircumferenceArea();


    std::cout << std::endl << std::endl;
    // 4.2
    std::cout << "<----------- 4.2 ----------->" << std::endl;
    srand(time(NULL));


    std::array<Polygon<3>, 4> triangles;
    std::array<Polygon<6>, 4> hexagons;


    for(size_t i=0; i<triangles.size(); i++) {
        Point a;
        Point c;
        Point e;
        triangles[i] = Polygon<3>{std::array<Point, 3> {a, c, e}};

        Point b = a.midsegment_to(c);
        Point d = c.midsegment_to(e);
        Point f = e.midsegment_to(a);
        hexagons[i] =  Polygon<6>{std::array<Point, 6> {a, b, c, d, e, f}};
    }

    std::cout << "sum_circ of hexagons:  using init_list: " << std::endl <<
              sum_circumference_lst({triangles[0], triangles[1], triangles[2], triangles[3]}) << std::endl;
    std::cout << "sum_circ of hexagons:  using init_list: " << std::endl <<
              sum_circumference_lst({hexagons[0], hexagons[1], hexagons[2], hexagons[3]}) << std::endl;

    std::cout << "sum_circ of first two triangles and last two hexagons using variadic templates" << std::endl <<
              sum_circumference(triangles[0], triangles[1], hexagons[2], hexagons[3]) << std::endl;





    return 0;
}