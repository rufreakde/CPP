#include <iostream>
#include "producers_consumers.h"
#include <thread>

using namespace std;


int main() {

    int64_t N = 10;
    vector<double> a(N);
    a[0] = 3;


    thread t1 {producer1, ref(a)};
    thread t2 {consumer1, ref(a)};

    t2.join();
    t1.join();
    return 0;
}