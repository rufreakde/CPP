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

    double summe =0;
    double counter =0;
    double geom_mean = 1;

    auto sum = [&summe](T &elm) {
        summe += elm.circumference() ;
    };

    auto get_nb = [](T &elm, double threshold) {
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
        counter += get_nb(elm, 6.);
    }

    geom_mean = pow(geom_mean, 1./double(lst.size()));

    return std::array<double, 3> {summe, geom_mean, counter};

}


/*template <typename T>
double sum_circumference(T arg){
    return arg.circumference();
}

template <typename T, typename... Tail>
double sum_circumference(T head, Tail... tail){
    return head.circumference() + sum_circumference(tail...);
}

 */

template< std::size_t N >
std::array<double,N> operator+( const std::array<double,N> lhs, const std::array<double,N> rhs ){

    if(lhs.size() != rhs.size()){
        throw std::out_of_range ("The Two arrays you wanted to add up, have not the same size!");
    }

    std::array<double,N> sum = {0, 1, 0};

    //for(size_t i=0; i<sum.size(); i++){
    //    sum[i] += lhs[i] + rhs[i];
    //}
    sum[0] += lhs[0] + rhs[0];
    sum[1] =  lhs[1] * rhs[1];
    sum[2] += lhs[2] + rhs[2];

    return sum;
};

double nb_arg = 0;


template<typename T>
std::array<double, 3> transform_reduce(T polygon){

    auto get_sum = [](T &elm) {
        return elm.circumference();
    };

    auto get_nb = [](T &elm, double threshold) {
        int elm_counter=0;
        for (size_t i = 0; i < elm.size(); i++) {
            size_t j = (i+1) % elm.size();
            if (elm.coord(i).distance_to(elm.coord(j)) > threshold) { elm_counter++; }
        }
        return elm_counter;
    };

    auto get_geom_mean = [](T &elm) {
        return pow(elm.area(), 1./nb_arg);
    };

    double sidesBiggerThan = get_nb(polygon, 6.);
    double circumference = get_sum(polygon);
    double geom_mean_product = get_geom_mean(polygon);
    
    
    return std::array<double,3>{ circumference, geom_mean_product, sidesBiggerThan};
};



template <typename T, typename... Tail>
std::array<double, 3> transform_reduce(T head, Tail... tail){

    if (sizeof...(Tail) > nb_arg){nb_arg = sizeof...(Tail) + 1;}

    std::array<double,3> counterHead = transform_reduce(head);
    std::array<double,3> counterTail = transform_reduce(tail...);

    return counterHead + counterTail;
};


#endif //EX4_CHRISPENS_GAHBICHE_TRANSFORM_REDUCE_H
