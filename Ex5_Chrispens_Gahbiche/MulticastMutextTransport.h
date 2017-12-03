//
// Created by Habib Gahbiche on 03/12/2017.
//

#ifndef EX5_CHRISPENS_GAHBICHE_MULTICASTMUTEXTTRANSPORT_H
#define EX5_CHRISPENS_GAHBICHE_MULTICASTMUTEXTTRANSPORT_H

#include <optional>
#include <deque>
#include <vector>
#include <type_traits>
#include <memory>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>
#include <set>
#include <cmath>




template<typename T>
class MulticastMutexTransport {
private:
    struct SourceData {
        std::deque<T> elements;
    };

    std::vector<SourceData> sources = {};
    std::mutex mutex;
    std::condition_variable cv;
    bool productionCompleted = false;

public:
    using SourceId = std::size_t;

    MulticastMutexTransport(void) = default;

    SourceId addSource(void) {
        std::unique_lock<std::mutex> lock(mutex);
        sources.push_back(SourceData());
        return sources.size() - 1;
    }

    std::size_t size(){
        //TODO Buggy
        std::unique_lock<std::mutex> lock(mutex);
        return sources.size();
    }

    void push(T value, std::size_t id) {
        std::unique_lock<std::mutex> lock(mutex);
        for (auto &source : sources) {
            source.elements.push_back(value);
            //std::cout << "push from: " << id << " val: " << value << std::endl;
        }
        cv.notify_all();
    }

    void signifyCompletion(void) {
        std::unique_lock<std::mutex> lock(mutex);
        productionCompleted = true;
        cv.notify_all();
    }

    std::optional<T> tryPull(SourceId sourceId, const std::string &consumerName) {
        std::unique_lock<std::mutex> lock(mutex);
        auto &elements = sources.at(sourceId).elements;
        while (!productionCompleted && elements.size() <= 0) {
            cv.wait(lock);
        }

        if (elements.empty())
            return std::nullopt;

        T result = std::move(elements.front());
        elements.pop_front();

        //std::cout << consumerName << "  value: " << result << std::endl;

        return result;
    }
};


#endif //EX5_CHRISPENS_GAHBICHE_MULTICASTMUTEXTTRANSPORT_H
