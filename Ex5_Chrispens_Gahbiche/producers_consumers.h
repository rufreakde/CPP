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
#include <limits>

std::queue< std::vector<int64_t> > mqueue1;
std::queue< std::vector<int64_t> > mqueue2;
std::queue< std::array<std::vector<int64_t >,2> > mqueue3;// the queue of messages
std::queue< std::array<std::vector<int64_t >,2> > mqueue4;

std::condition_variable event1; // the variable communicating events
std::condition_variable event2; // the variable communicating events
std::condition_variable event3; // the variable communicating events
std::condition_variable event4;

std::mutex mmutex; // the locking mechanism
std::mutex mmutex2;
std::mutex mmutex3;
std::mutex mmutex4;

//a[n+1] = fmod(a[n], 2) == 0 ? a[n] / 2 : 3 * a[n] + 1;

void producer1(int64_t a0, size_t &N) {
    while(true) {

        if(mqueue1.size() <= 0) { //fix for stream output! cout
            std::unique_lock<std::mutex> lck{mmutex};


            std::vector<int64_t> a;
            a.push_back(a0);
            for (size_t n = 0; n < N; n++) {
                a.push_back((a[n] % 2) == 0 ? int64_t(double(a[n]) / 2) : 3 * a[n] + 1);
            }
            mqueue1.push(a);
            std::cout << "# finished producer 1" << std::endl;
        }
        event1.notify_one();
    }   // release lock (at end of scope)
}

void consumer1() {
    while(true) {
            std::unique_lock<std::mutex> lck2{mmutex2};

            std::unique_lock<std::mutex> lck{mmutex};
            event1.wait(lck) /* do nothing */;
            while (mqueue1.size() > 0) {
                auto a = mqueue1.front();

                std::string stringLog = "# Consumer1 = ";
                for (auto elm : a) {
                    stringLog += " " + std::to_string(elm);
                }
                std::cout << stringLog << std::endl;
                mqueue2.push(a);
                mqueue1.pop();
            }
            lck.unlock();
            event2.notify_one();
    }
}

int64_t min(std::vector<int64_t> a, size_t n){
    int64_t min = std::numeric_limits<int64_t>::max();
    for(size_t i=0; i<n; i++){
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
        if(mqueue3.size() <= 0) {  //fix for stream output! cout
            std::unique_lock<std::mutex> lck3{mmutex3};

            std::unique_lock<std::mutex> lck2{mmutex2};
            event2.wait(lck2) /* do nothing */;

            while (mqueue2.size() > 0) {
                auto a = mqueue2.front();
                std::vector<int64_t> min_n;
                std::vector<int64_t> max_n;
                for (size_t n = 2; n < N; n++) {
                    int64_t tMax = max(a, n);
                    int64_t tMin = min(a, n);

                    min_n.push_back(tMin);
                    max_n.push_back(tMax);
                }
                auto tempVector = std::array<std::vector<int64_t>, 2> {min_n, max_n};
                mqueue3.push(tempVector);
                mqueue2.pop();
            }
            std::cout << "# finished producer 2" << std::endl;
            lck2.unlock();
        }
        event3.notify_one(); //notify
    }   // release lock (at end of scope)
}

void consumer2() {
    while(true) {
        std::unique_lock<std::mutex> lck4{mmutex4};

        std::unique_lock<std::mutex> lck3{mmutex3};
        event3.wait(lck3) /* do nothing */;
        while(mqueue3.size()>0) {
            auto a = mqueue3.front();

            std::string stringLog = "# Consumer2 = ";
            //for(size_t j=0; j< a.size(); j++){
                for(size_t i=0; i< a[0].size(); i++) {
                    stringLog += " " + std::to_string(a[0][i]) + "|" + std::to_string(a[1][i]);
                }
            //}
            std::cout << stringLog << std::endl;

            mqueue4.push(a);
            mqueue3.pop();
        }
        lck3.unlock();
        event4.notify_one();
    }
}

#endif //EX5_CHRISPENS_GAHBICHE_PRODUCERS_CONSUMERS_H
