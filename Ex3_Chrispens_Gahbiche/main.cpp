#include <iostream>
#include <memory>
#include <vector>
#include <array>

#include "./Interfaces/Quad.h"
#include "./shapes/IsoscelesTrapezoid.h"
#include "./shapes/Kite.h"
#include "./shapes/Parallelogram.h"
#include "./Shapes/Quadrilateral.h"
#include "./shapes/Rectangle.h"
#include "./shapes/Rhombus.h"
#include "./shapes/Square.h"
#include "./shapes/Trapezoid.h"

#include "./shapes/Quad3D.h"
#include "Shapes/SpecializedRectangle.h"
#include "Shapes/SpecializedSquare.h"

using namespace std;



int main() {

    //COULD NOT MAKE THIS WORK WITH VECTOR WHY????
    std::array<std::unique_ptr<Quad>, 8> shapeVector{
            std::unique_ptr<Quad>{new Quadrilateral{"Quadrilateral", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new Kite{"Kite", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new Rhombus{"Rhombus", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new Rectangle{"Rectangle", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new Square{"Square", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new Trapezoid{"Trapezoid", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new Parallelogram{"Parallelogram", {1,1}, {1,2}, {2,2}, {2,1}}},
            std::unique_ptr<Quad>{new IsoscelesTrapezoid{"IsoscelesTrapezoid", {1,1}, {1,2}, {2,2}, {2,1}}}
    };

    //3.1
    cout << "<!-- 3.1 --!>" << endl;
    for (auto &shape : shapeVector) {
        auto QuadInterfaceIteration = shape.get();
        QuadInterfaceIteration->printNameCircumferenceArea();
    }

    //3.2
    cout << "<!-- 3.2 --!>" << endl;
    for (auto &shape : shapeVector) {
        auto QuadInterfaceIteration = shape.get();
        auto ParallelogramIteration = dynamic_cast<Parallelogram*>(QuadInterfaceIteration);
        if(ParallelogramIteration != nullptr) {
            ParallelogramIteration->subdivide();
            ParallelogramIteration->printSubdivisions();
        }else{
            cout << "no subdivide() : "<< QuadInterfaceIteration->name() <<" is not a Parallelogram" << endl;
        }
    }

    //3.3
    cout << "<!-- 3.3 --!>" << endl;
    Quad3D quadrilateral3D {Quadrilateral{{"Quadrilateral"}, {0,2}, {2,2}, {2,0}, {0,0}}};
    cout << "# Quad3D: "  << &quadrilateral3D << endl;
    quadrilateral3D.setThickness(5);
    cout << "# Surface: " << quadrilateral3D.surface() << endl;
    cout << "# Volume: " << quadrilateral3D.volume() << endl;

    Quad3D copyShape = quadrilateral3D;
    cout << "# Quad3D (Copy): " << &copyShape << endl;
    cout << "# Surface: " << copyShape.surface() << endl;
    cout << "# Volume: " << copyShape.volume() << endl;

    Quad3D moveShape = std::move(quadrilateral3D);
    cout << "# Quad3D (moved): " << &moveShape << endl;
    cout << "# Surface: " << moveShape.surface() << endl;
    cout << "# Volume: " << moveShape.volume() << endl;

    // assign quad2D to quad3D ?? These are two different types
    // why should we try this?
    Quad3D Square3D = *std::move( shapeVector[4].get() );
    Square3D.setThickness(10);
    cout << "# Square3D (= operator, move): " << &Square3D << endl;
    cout << "# Surface: " << Square3D.surface() << endl;
    cout << "# Volume: " << Square3D.volume() << endl;

    Quad3D Parallelogram3D = *shapeVector[6].get();
    Parallelogram3D.setThickness(15);
    cout << "# Quad3D (moved): " << &Parallelogram3D << endl;
    cout << "# Surface: " << Parallelogram3D.surface() << endl;
    cout << "# Volume: " << Parallelogram3D.volume() << endl;

    // I suggest following for move assignments:
    Quad3D parallelogram3D_org = Quad3D{Parallelogram{"Parallelogram", {0,2}, {2,2}, {2,0}, {0,0}}, 5};
    Quad3D parallelogram3D_move {Parallelogram{"Parallelogram", {0,7}, {7,7}, {7,0}, {0,0}}, 7};
    Quad3D parallelogram3D_copy {Parallelogram{"Parallelogram", {0,7}, {7,7}, {7,0}, {0,0}}, 7};
    // try to use copy assignment
    parallelogram3D_copy = parallelogram3D_org;
    // try to use move assignment
    parallelogram3D_move = std::move(parallelogram3D_org);
    cout << "# Quad3D (moved): " << &parallelogram3D_move << endl;
    cout << "# Surface: " << parallelogram3D_move.surface() << endl;
    cout << "# Volume: " << parallelogram3D_move.volume() << endl;


    //3.5
    cout << "<!-- 3.5 --!>" << endl;
    SpecializedRectangle specRectangle{{3,3}, {8,3}, 2};
    specRectangle.printNameCircumferenceArea();
    std::cout << specRectangle.coord(2)[0] << "\t"  << specRectangle.coord(2)[1] << std::endl;
    std::cout << specRectangle.coord(3)[0] << "\t"  << specRectangle.coord(3)[1] << std::endl;

    SpecializedSquare specSquare{{3,3}, {6,3}};
    specSquare.printNameCircumferenceArea();
    //std::cout << specSquare.coord(2)[0] << "\t"  << specSquare.coord(2)[1] << std::endl;
    //std::cout << specSquare.coord(3)[0] << "\t"  << specSquare.coord(3)[1] << std::endl;



    return 0;
}