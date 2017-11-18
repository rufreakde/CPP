//
// Created by Habib Gahbiche on 18/11/2017.
//

/*
Let us generalize the function sum_circumference() to transform_reduce(), which oper-
 ates on an unspecified type (given as a template parameter) and applies a unary function
 to each object (e.g. call of circumference()) and then combines these results with a binary
 function (e.g. summation) to obtain the final result. Start with an implementation which
 takes an initializer list of objects.
*/

#ifndef EX4_CHRISPENS_GAHBICHE_TRANSFORM_REDUCE_H
#define EX4_CHRISPENS_GAHBICHE_TRANSFORM_REDUCE_H

#include <initializer_list>
#include <cmath>
#include <array>
#include <iostream>


template<typename T>
std::array<double, 3> transform_reduce(std::initializer_list<T> lst){

    auto add = [=](double &a, const double &b){return a+b;};
    double summe =0;
    double counter =0;
    double geom_mean = 1;

    auto sum = [&summe](T &elm) {
        summe += elm.circumference() ;
    };

    auto get_nb = [&counter](T &elm, double threshold) {
        int elm_counter=0;
        for (size_t i = 0; i < elm.size(); i++) {
            size_t j = (i+1) % elm.size();
            if (elm.coord(i).distance_to(elm.coord(j)) > threshold) { elm_counter++; }
        }
        return elm_counter;
    };

    auto get_geom_mean = [&geom_mean](T &elm) {
        geom_mean *= elm.area();
    };


    for(auto elm: lst) {
        sum(elm);
        get_geom_mean(elm);
        counter += get_nb(elm, 6);
    }

    geom_mean = pow(geom_mean, 1./double(lst.size()));

    return std::array<double, 3> {summe, geom_mean, counter};

}

#endif //EX4_CHRISPENS_GAHBICHE_TRANSFORM_REDUCE_H
