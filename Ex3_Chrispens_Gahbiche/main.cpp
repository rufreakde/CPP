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
            std::unique_ptr<Quad>{new Quadrilateral{"Quadrilateral", {0,0}, {1,2}, {2,-3}, {-2,-1}}},
            std::unique_ptr<Quad>{new Kite{"Kite", {0,0}, {1,-1}, {0,-4}, {-1,-1}}},
            std::unique_ptr<Quad>{new Rhombus{"Rhombus", {0,0}, {1,-1}, {0,-2}, {-1,-1}}},
            std::unique_ptr<Quad>{new Rectangle{"Rectangle", {2,2}, {5,2}, {5,0}, {2,0}}},
            std::unique_ptr<Quad>{new Square{"Square", {0,2}, {2,2}, {2,0}, {0,0}}},
            std::unique_ptr<Quad>{new Trapezoid{"Trapezoid", {0,3}, {1,3}, {6,0}, {2,0}}},
            std::unique_ptr<Quad>{new Parallelogram{"Parallelogram", {-2,2}, {2,2}, {4,0}, {0,0}}},
            std::unique_ptr<Quad>{new IsoscelesTrapezoid{"IsoscelesTrapezoid", {-2,2}, {2,2}, {4,0}, {-4,0}}}
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
    Quad3D quadrilateral3D {Quadrilateral{{"Quadrilateral"}, {0,0}, {1,2}, {2,-3}, {-2,-1}}};
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


    Quad3D parallelogram3D_org = Quad3D{Parallelogram{"Parallelogram", {-2,2}, {2,2}, {4,0}, {0,0}}, 5};
    Quad3D parallelogram3D_move {Parallelogram{"Parallelogram", {-2,2}, {2,2}, {4,0}, {0,0}}, 7};
    Quad3D parallelogram3D_copy {Parallelogram{"Parallelogram", {-2,2}, {2,2}, {4,0}, {0,0}}, 7};
    // try to use copy assignment
    parallelogram3D_copy = parallelogram3D_org;
    // try to use move assignment
    parallelogram3D_move = std::move(parallelogram3D_org);
    cout << "# Quad3D (moved): " << &parallelogram3D_move << endl;
    cout << "# Surface: " << parallelogram3D_move.surface() << endl;
    cout << "# Volume: " << parallelogram3D_move.volume() << endl;


    //3.5
    cout << "<!-- 3.5 --!>" << endl;

    std::array<std::unique_ptr<Quad>, 8> specialShapeVector{
            std::unique_ptr<Quad>{new Quadrilateral{"Quadrilateral", {0,0}, {1,2}, {2,-3}, {-2,-1}}},
            std::unique_ptr<Quad>{new Kite{"Kite", {0,0}, {1,-1}, {0,-4}, {-1,-1}}},
            std::unique_ptr<Quad>{new Rhombus{"Rhombus", {0,0}, {1,-1}, {0,-2}, {-1,-1}}},
            std::unique_ptr<Quad>{new SpecializedRectangle{{2,2}, {5,2}, 2}},
            std::unique_ptr<Quad>{new SpecializedSquare{{0,2}, {2,2}}},
            std::unique_ptr<Quad>{new Trapezoid{"Trapezoid", {0,3}, {1,3}, {6,0}, {2,0}}},
            std::unique_ptr<Quad>{new Parallelogram{"Parallelogram", {-2,2}, {2,2}, {4,0}, {0,0}}},
            std::unique_ptr<Quad>{new IsoscelesTrapezoid{"IsoscelesTrapezoid", {-2,2}, {2,2}, {4,0}, {-4,0}}}
    };

    for (auto &shape : specialShapeVector) {
        auto QuadInterfaceIteration = shape.get();
        QuadInterfaceIteration->printNameCircumferenceArea();
    }

    return 0;
}