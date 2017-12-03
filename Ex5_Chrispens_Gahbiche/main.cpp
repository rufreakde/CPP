
#include <future>
#include "MulticastMutextTransport.h"

void producerConsumerQueue(int startValue, const std::size_t nMax) {
    // set up transportP1, add source for ourselves
    auto transportP1 = std::make_shared<MulticastMutexTransport<int>>();
    auto sourceIdP1 = transportP1->addSource();

    //auto transportP2 = std::make_shared<MulticastMutexTransport<int>>();
    auto transportP2 = std::make_shared<MulticastMutexTransport<std::array<int, 3>>>(); // stores a_n, max_n, min_n
    auto sourceIdP2 = transportP2->addSource();

    auto transportP3 = std::make_shared<MulticastMutexTransport<std::tuple<std::set<int>, std::set<int> >>>();
    auto sourceIdP3 = transportP3->addSource();

    // start producer 1
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP1 alive)
    std::thread([=] {

        std::vector<int> collatzValues {startValue};
        transportP1->push(static_cast<int>(collatzValues[0]), 1);

        for (std::size_t n = 1; n <= nMax; ++n) { //run through the count we set in start
            if (collatzValues[n - 1] % 2 == 0) {
                collatzValues.push_back(collatzValues[n - 1] / 2);
            } else {
                collatzValues.push_back((collatzValues[n - 1] * 3) + 1);
            }

            transportP1->push(static_cast<int>(collatzValues[n]),
                              1); //push the value you want to push calculate it beforehand!
        }
        transportP1->signifyCompletion();
    }).detach();

    // start producer 2
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP2 alive)
    std::thread([=] {

        size_t lastSize = 0;
        std::set<int> collatzValues = {};
        std::set<int> ArrayOfSubstractions;
        // consume produced elements
        while (auto next = transportP1->tryPull(sourceIdP1,
                                                "Producer [2] consuming: sourceIdP1")) { //wait for producer 1

            collatzValues.insert(*next);

            if(lastSize != collatzValues.size()){
                lastSize = collatzValues.size();

                if (collatzValues.size() > 1) {

                    for (size_t i = 0; i < collatzValues.size(); i++) {
                        for (size_t j = 0; j < collatzValues.size(); j++) {
                            if (i != j) {
                                ArrayOfSubstractions.insert(abs(*collatzValues.find(i) - *collatzValues.find(j)));
                            }
                        }
                    }
                }
                transportP2->push({*next,
                                   static_cast<int>(*ArrayOfSubstractions.begin()),
                                   static_cast<int>(*ArrayOfSubstractions.end())},
                                  2);
            }

            //std::cout << "production 2 MIN: " << *ArrayOfSubstractions.begin() << std::endl;
            //std::cout << "production 2 Max: " << *ArrayOfSubstractions.end() << std::endl;
        }
        transportP2->signifyCompletion();

    }).detach();

    // start producer 3
    std::thread([=] {
        // consume produced elements
        std::set<int> M0;
        std::set<int> M1;
        int counter_n = 0;

        while (auto next = transportP2->tryPull(sourceIdP2,
                                                "Producer [3] consuming: sourceIdP2")) { //again wait for Producer 2
            ++counter_n;
            auto a_n =   std::get<0>(*next);
            auto min_n = std::get<1>(*next);
            auto max_n = std::get<2>(*next);


            if(min_n == 0){
                M0.insert(a_n);
            };
            if(max_n > std::pow(1.5, counter_n)){
                M1.insert(a_n);
            };

        }

        transportP3->push({M0, M1},3);
        transportP3->signifyCompletion();

    }).detach();

    //wait for final consume after process is finished:
    // consume produced elements
    //alternatively just joun() producer 3 instead of detach!
    while (auto next = transportP3->tryPull(sourceIdP3, "MainThread consuming: sourceIdP3")) {
        for(auto m0 : std::get<0>(*next)){
            std::cout << "Final Result m0: " << m0 << std::endl;
        }
        for(auto m1 : std::get<1>(*next)){
            std::cout << "Final Result m1: " << m1 << std::endl;
        }
    }
}


void futurePormise(int startValue, const std::size_t nMax) {
    // set up transportP1, add source for ourselves
    //auto transportP1 = std::make_shared<MulticastMutexTransport<int>>();
    //auto sourceIdP1 = transportP1->addSource();

    std::promise<int> transportP1;
    //std::future<int> transportP1;

    //auto transportP2 = std::make_shared<MulticastMutexTransport<int>>();
    auto transportP2 = std::make_shared<MulticastMutexTransport<std::array<int, 3>>>(); // stores a_n, max_n, min_n
    auto sourceIdP2 = transportP2->addSource();

    auto transportP3 = std::make_shared<MulticastMutexTransport<std::tuple<std::set<int>, std::set<int> >>>();
    auto sourceIdP3 = transportP3->addSource();

    // start producer 1
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP1 alive)
    std::thread([=] {

        std::vector<int> collatzValues {startValue};
        transportP1.set_value(collatzValues[0]);
        //transportP1->push(static_cast<int>(collatzValues[0]), 1);


        for (std::size_t n = 1; n <= nMax; ++n) { //run through the count we set in start
            if (collatzValues[n - 1] % 2 == 0) {
                collatzValues.push_back(collatzValues[n - 1] / 2);
            } else {
                collatzValues.push_back((collatzValues[n - 1] * 3) + 1);
            }

            transportP1.set_value(collatzValues[n]);
            //transportP1->push(static_cast<int>(collatzValues[n]),
            //                  1); //push the value you want to push calculate it beforehand!
        }
        //transportP1->signifyCompletion();
    }).detach();

    // start producer 2
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP2 alive)
    std::thread([=] {

        size_t lastSize = 0;
        std::set<int> collatzValues = {};
        std::set<int> ArrayOfSubstractions;
        // consume produced elements
        while (auto next = transportP1.get_future().get()){ //wait for producer 1

            collatzValues.insert(next);

            if(lastSize != collatzValues.size()){
                lastSize = collatzValues.size();

                if (collatzValues.size() > 1) {

                    for (size_t i = 0; i < collatzValues.size(); i++) {
                        for (size_t j = 0; j < collatzValues.size(); j++) {
                            if (i != j) {
                                ArrayOfSubstractions.insert(abs(*collatzValues.find(i) - *collatzValues.find(j)));
                            }
                        }
                    }
                }
                transportP2->push({next,
                                   static_cast<int>(*ArrayOfSubstractions.begin()),
                                   static_cast<int>(*ArrayOfSubstractions.end())},
                                  2);
            }

            //std::cout << "production 2 MIN: " << *ArrayOfSubstractions.begin() << std::endl;
            //std::cout << "production 2 Max: " << *ArrayOfSubstractions.end() << std::endl;
        }
        transportP2->signifyCompletion();

    }).detach();

    // start producer 3
    std::thread([=] {
        // consume produced elements
        std::set<int> M0;
        std::set<int> M1;
        int counter_n = 0;

        while (auto next = transportP2->tryPull(sourceIdP2,
                                                "Producer [3] consuming: sourceIdP2")) { //again wait for Producer 2
            ++counter_n;
            auto a_n =   std::get<0>(*next);
            auto min_n = std::get<1>(*next);
            auto max_n = std::get<2>(*next);


            if(min_n == 0){
                M0.insert(a_n);
            };
            if(max_n > std::pow(1.5, counter_n)){
                M1.insert(a_n);
            };

        }

        transportP3->push({M0, M1},3);
        transportP3->signifyCompletion();

    }).detach();

    //wait for final consume after process is finished:
    // consume produced elements
    //alternatively just joun() producer 3 instead of detach!
    while (auto next = transportP3->tryPull(sourceIdP3, "MainThread consuming: sourceIdP3")) {
        for(auto m0 : std::get<0>(*next)){
            std::cout << "Final Result m0: " << m0 << std::endl;
        }
        for(auto m1 : std::get<1>(*next)){
            std::cout << "Final Result m1: " << m1 << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    try {
        producerConsumerQueue(3, 10000); //10000000
        std::cout << "All tests ran successfully." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}