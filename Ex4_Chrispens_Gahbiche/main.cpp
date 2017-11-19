#include <iostream>
#include <vector>
#include "Polygon.h"
#include "sum_circumference.h"
#include "transform_reduce.h"

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
        Point b;
        Point c;
        triangles[i] = Polygon<3>{std::array<Point, 3> {a, b, c}};

        Point ab = a.midsegment_to(b);
        Point bc = b.midsegment_to(c);
        Point ca = c.midsegment_to(a);
        hexagons[i] =  Polygon<6>{std::array<Point, 6> {a, ab, b, bc, c, ca}};
    }

    std::cout << "sum_circ of triangles using init_list: " << std::endl <<
              sum_circumference({triangles[0], triangles[1], triangles[2], triangles[3]}) << std::endl;
    std::cout << "sum_circ of hexagons using init_list: " << std::endl <<
              sum_circumference({hexagons[0], hexagons[1], hexagons[2], hexagons[3]}) << std::endl;

    std::cout << "sum_circ of first two triangles and last two hexagons using variadic templates" << std::endl <<
              sum_circumference(triangles[0], triangles[1], hexagons[2], hexagons[3]) << std::endl;


    std::cout << std::endl << std::endl;
    // 4.3
    std::cout << "<----------- 4.3 ----------->" << std::endl;
    std::cout << "FORMAT:    Circumference / Geometric Mean / Count of sides that are bicker than Threshold" << std::endl;
    std::array<double, 3> result_trafo_red = transform_reduce({triangles[0], triangles[1], triangles[2], triangles[3]});
    std::cout << "transform_reduce using init_list: " << std::endl <<
          result_trafo_red[0] << "\t" << result_trafo_red[1] << "\t" << result_trafo_red[2] << std::endl;

    std::array<double, 3> result_trafo_red_hexagons = transform_reduce({hexagons[0], hexagons[1], hexagons[2], hexagons[3]});
    std::cout << "transform_reduce using init_list: " << std::endl <<
          result_trafo_red_hexagons[0] << "\t" << result_trafo_red_hexagons[1] << "\t" << result_trafo_red_hexagons[2] << std::endl;


    std::array<double, 3> result_trafo_variadic = transform_reduce(triangles[0], triangles[1], triangles[2], triangles[3]);
    std::cout << "transform_reduce using variadic templates: " << std::endl <<
            result_trafo_variadic[0] << "\t" << result_trafo_variadic[1] << "\t" << result_trafo_variadic[2] << std::endl;


    return 0;
}