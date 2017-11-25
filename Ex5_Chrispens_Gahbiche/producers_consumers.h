//
// Created by Habib Gahbiche on 25/11/2017.
//

#ifndef EX5_CHRISPENS_GAHBICHE_PRODUCERS_CONSUMERS_H
#define EX5_CHRISPENS_GAHBICHE_PRODUCERS_CONSUMERS_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <cassert>
#include <cmath>
#include <chrono>
#include <thread>
#include <array>

std::queue< std::vector<int64_t> > mqueue1;
std::queue< std::vector<int64_t> > mqueue2;
std::queue< std::vector<int64_t> > mqueue3;// the queue of messages

std::condition_variable event1; // the variable communicating events
std::condition_variable event2; // the variable communicating events
std::condition_variable event3; // the variable communicating events
std::mutex mmutex; // the locking mechanism

//a[n+1] = fmod(a[n], 2) == 0 ? a[n] / 2 : 3 * a[n] + 1;

void producer1(int64_t a0, size_t &N) {
    while(true) {
        std::vector<int64_t> a;
        a.push_back(a0);
        for(size_t n=0; n<N; n++){
            a.push_back((a[n] % 2) == 0 ? int64_t(double(a[n]) / 2) : 3 * a[n] + 1);
        }
        std::unique_lock<std::mutex> lck {mmutex};
        mqueue1.push(a);
        event1.notify_one(); //notify
    }   // release lock (at end of scope)
}

void consumer1() {
    while(true) {
        std::unique_lock<std::mutex> lck{mmutex};
        event1.wait(lck) /* do nothing */;
        while(mqueue1.size()>0) {
            auto a = mqueue1.front();

            std::cout << "# elm = " << std::endl;
            for(auto elm : a){
                std::cout << " " <<  elm;
            }
            std::cout << std::endl;

            mqueue1.pop();
        }
        lck.unlock();
    }
}

int64_t min(std::vector<int64_t> a, size_t n){
    int64_t min = std::numeric_limits::infinity();
    for(size_t i=0; i<a.size(); i++){
        for(size_t j=0; j<n; j++){
            if(abs(a[i] - a[j]) < min && i!=j){
                min = abs(a[i] - a[j]);
            };
        }
    }
    return min;
}
int64_t max(std::vector<int64_t> a, size_t n){
    int64_t max = 0;
    for(size_t i=0; i<n; i++){
        for(size_t j=0; j<n; j++){
            if(abs(a[i] - a[j]) > max && i!=j){
                max = abs(a[i] - a[j]);
            };
        }
    }
    return max;
}

void producer2(size_t &N) {
    while(true) {

        std::unique_lock<std::mutex> lck2 {mmutex};

        while(mqueue2.size()>0) {

            auto a = mqueue2.front();
            std::vector<int64_t> min_n;
            for (size_t n = 0; n < N; n++) {
                min_n.push_back(min(a, n));
            }
        }


        event2.notify_one(); //notify
    }   // release lock (at end of scope)
}

void consumer2() {
    while(true) {
        std::unique_lock<std::mutex> lck2{mmutex};
        event2.wait(lck2) /* do nothing */;
        while(mqueue1.size()>0) {
            auto a = mqueue1.front();

            std::cout << "# elm = " << std::endl;
            for(auto elm : a){
                std::cout << " " <<  elm;
            }
            std::cout << std::endl;

            mqueue1.pop();
        }
        lck.unlock();
// ... process m ...
    }
}

#endif //EX5_CHRISPENS_GAHBICHE_PRODUCERS_CONSUMERS_H
