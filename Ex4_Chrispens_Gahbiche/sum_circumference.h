//
// Created by Habib Gahbiche on 16/11/2017.
//

#ifndef EX4_CHRISPENS_GAHBICHE_SUM_CIRCUMFERENCE_H
#define EX4_CHRISPENS_GAHBICHE_SUM_CIRCUMFERENCE_H

#include <initializer_list>

template <typename T>
double sum_circumference(T arg){
    return arg.circumference();
}

template <typename T, typename... Tail>
double sum_circumference(T head, Tail... tail){
    return head.circumference() + sum_circumference(tail...);
}


template <typename T>
double sum_circumference(std::initializer_list<T> lst){
    double sum = 0;
    for (auto elm : lst){
        sum += elm.circumference();
    }
    return sum;
}

#endif //EX4_CHRISPENS_GAHBICHE_SUM_CIRCUMFERENCE_H
