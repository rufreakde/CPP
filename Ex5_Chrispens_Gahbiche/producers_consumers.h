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

std::queue<double> mqueue; // the queue of messages
std::condition_variable mcond; // the variable communicating events
std::mutex mmutex; // the locking mechanism

void producer1(std::vector<double> a) {
    while(true) {
        for(size_t n = 0; n<a.size(); n++){
            std::unique_lock<std::mutex> lck{mmutex};
            mqueue.push(fmod(a[n], 2) == 0 ? a[n] / 2 : 3 * a[n] + 1);
            std::cout << "n= " << n << std::endl;
            std::cout << "a[n] = " << a[n] << std::endl;
            mcond.notify_one(); //notify
        }
    }
}


void consumer1(std::vector<double> a) {
    while(true) {
        std::unique_lock<std::mutex> lck{mmutex};
        mcond.wait(lck) /* do nothing */;
        int64_t m = mqueue.front();
        mqueue.pop();
        lck.unlock();

        a.push_back(m);
        std::cout << "consumed value for a" << std::endl;
    }
}

#endif //EX5_CHRISPENS_GAHBICHE_PRODUCERS_CONSUMERS_H
