//
// Created by Rudolf Chrispens on 08.11.17.
//

#include "Parallelogram.h"

#include <utility>

Parallelogram::Parallelogram() {}

Parallelogram::~Parallelogram() = default;

Parallelogram::Parallelogram(std::string _Name,
                             std::array<double,2> _Corner1, std::array<double,2> _Corner2,
                             std::array<double,2> _Corner3, std::array<double,2> _Corner4) {
    _corners = {_Corner1, _Corner2, _Corner3, _Corner4};
    _name = std::move(_Name);
}

std::array<double, 2> Parallelogram::midsegment(const std::array<double, 2> &A, const std::array<double, 2> &B) {
    return std::array<double, 2> {(A[0] + A[1])/2, (B[0] + B[1]/2)};
}

//template <typename Shape>
std::array<Parallelogram, 4> Parallelogram::subdivide() {
    std::array<double, 2> A = _corners[0];
    std::array<double, 2> B = _corners[1];
    std::array<double, 2> C = _corners[2];
    std::array<double, 2> D = _corners[3];

    std::array<double, 2> E = midsegment(A, B);
    std::array<double, 2> F = midsegment(B, C);
    std::array<double, 2> G = midsegment(C, D);
    std::array<double, 2> H = midsegment(D, A);
    std::array<double, 2> I = midsegment(A, C);

    std::array<std::string, 4> names {"par1, par2, par3, par4"};

    return std::array<Parallelogram, 4> {
            Parallelogram{names[0], A, E, I, H},
            Parallelogram{names[1], E, B, F, I},
            Parallelogram{names[2], H, I, G, D},
            Parallelogram{names[3], I, F, C, G}
    };

}
