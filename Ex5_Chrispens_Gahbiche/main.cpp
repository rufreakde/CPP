#include <iostream>
#include "producers_consumers.h"
#include <thread>

using namespace std;


int main() {

    size_t P = 10;
    int64_t a0 = 3;


    thread t1 {producer1, a0, ref(P)};
    thread t2 {consumer1};
    thread t3 {producer2, ref(P)};
    thread t4 {consumer2};
    thread t5 {producer3, ref(P)};
    thread t6 {consumer3};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    return 0;
}