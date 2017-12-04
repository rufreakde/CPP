
#include <future>
#include <unordered_set>
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

        std::vector<int> collatzValues = {startValue};
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
        std::vector<int> collatzValues = {};
        std::set<int> ArrayOfSubstractions;
        // consume produced elements
        while (auto next = transportP1->tryPull(sourceIdP1,
                                                "Producer [2] consuming: sourceIdP1")) { //wait for producer 1

            collatzValues.push_back(*next);

            if(lastSize != collatzValues.size()){
                lastSize = collatzValues.size();


                if (collatzValues.size() >= 1) {

                    for (size_t i = 0; i < collatzValues.size(); i++) {
                        for (size_t j = 0; j < collatzValues.size(); j++) {
                            if (i != j) {
                                ArrayOfSubstractions.insert(abs(collatzValues[i] - collatzValues[j]));

                            }
                        }
                    }

                    transportP2->push({*next,
                                       static_cast<int>(*ArrayOfSubstractions.begin()),
                                       static_cast<int>(*ArrayOfSubstractions.end())},
                                      2);
                }

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


void futurePormise(const int startValue, const std::size_t nMax) {
    // set up transportP1, add source for ourselves
    //auto transportP1 = std::make_shared<MulticastMutexTransport<int>>();
    //auto sourceIdP1 = transportP1->addSource();

    std::vector<std::promise<int>> promiseP1(nMax); // assumes granularity 1
    std::vector<std::future<int>> futureP1(nMax);
    for(size_t i=0; i<promiseP1.size(); i++){
        futureP1[i] = promiseP1[i].get_future();
    }
    std::vector<std::promise<std::array<int, 3>>> promiseP2(nMax);
    std::vector<std::future<std::array<int, 3>>> futureP2(nMax);
    for(size_t i=0; i<promiseP2.size(); i++){
        futureP2[i] = promiseP2[i].get_future();
    }

    //auto transportP3 = std::make_shared<MulticastMutexTransport<std::tuple<std::set<int>, std::set<int> >>>();
    //auto sourceIdP3 = transportP3->addSource();
    std::vector<std::promise<std::tuple<std::set<int>, std::set<int> >>> promiseP3 (nMax);
    std::vector<std::future<std::tuple<std::set<int>, std::set<int> >>> futureP3 (nMax);

    // start producer 1
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP1 alive)
    std::thread([&] {

        int prevCollatzValue = startValue;
        int nextCollatzValue = 0;

        promiseP1[0].set_value(startValue);

        for (std::size_t n = 1; n < nMax; ++n) { //run through the count we set in start
            if (prevCollatzValue % 2 == 0) {
                nextCollatzValue = prevCollatzValue / 2;
                promiseP1[n].set_value(nextCollatzValue);
            } else {
                nextCollatzValue = ((prevCollatzValue * 3) + 1);
                promiseP1[n].set_value(nextCollatzValue);
            }

        }
        //transportP1->signifyCompletion();
    }).detach();


    // start producer 2
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP2 alive)
    std::thread([&] {

        size_t lastSize =0;
        std::vector<int> collatzValues = {};
        std::set<int> ArrayOfSubstractions;
        // consume produced elements
        size_t n = 0;
        while( n<futureP1.size() && futureP1[n].valid()){
            auto next = futureP1[n].get();

            collatzValues.push_back(next);

            if(lastSize != collatzValues.size()) {
                lastSize = collatzValues.size();
                if (collatzValues.size() >= 1) {

                    for (size_t i = 0; i < collatzValues.size(); i++) {
                        for (size_t j = 0; j < collatzValues.size(); j++) {
                            if (i != j) {
                                ArrayOfSubstractions.insert(abs(collatzValues[i] - collatzValues[j]));
                            }
                        }
                    }
                    promiseP2[n].set_value({next,
                                            static_cast<int>(*ArrayOfSubstractions.begin()),
                                            static_cast<int>(*ArrayOfSubstractions.end())});
                }
            }


            //std::cout << "production 2 MIN: " << *ArrayOfSubstractions.begin() << std::endl;
            //std::cout << "production 2 Max: " << *ArrayOfSubstractions.end() << std::endl;
            n++;
        }


    }).detach();



    // start producer 3
    std::thread([&] {
        // consume produced elements
        std::set<int> M0;
        std::set<int> M1;
        int counter_n = 0;

        size_t n =0;
        while(n<futureP2.size() && futureP2[n].valid()){

            auto next = futureP2[n].get();
            ++counter_n;
            auto a_n =   next[0];
            auto min_n = next[1];
            auto max_n = next[2];

            if(min_n == 0){
                M0.insert(a_n);
            };
            if(max_n > std::pow(1.5, counter_n)){
                M1.insert(a_n);
            };
            promiseP3[n].set_value({M0, M1});
            n++;

        }

    }).detach();


    size_t n = 0;
    while(n<futureP3.size() && futureP3[n].valid()){
        // wird nicht richtig ausgeführt.

        std::cout << "n: " << n << std::endl;
        auto next = futureP3[n].get();
        for (auto m0 : std::get<0>(next)) {
            std::cout << "Final Result using future/promise  m0: " << m0 << std::endl;
        }
        for (auto m1 : std::get<1>(next)) {
            std::cout << "Final Result using future/promise m1: " << m1 << std::endl;
        }
        n++;
    }


}


int main(int argc, char *argv[]) {
    try {
        producerConsumerQueue(9, 10000000); //10000000
        std::cout << "All tests ran successfully." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    try {
        futurePormise(9, 10000000); //10000000
        std::cout << "All tests ran successfully." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}