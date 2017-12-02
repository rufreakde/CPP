
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

        std::cout << consumerName << "  value: " << result << std::endl;

        return result;
    }
};

void testProducerConsumerQueue(int startValue, const std::size_t nMax) {
    // set up transportP1, add source for ourselves
    auto transportP1 = std::make_shared<MulticastMutexTransport<int>>();
    auto sourceIdP1 = transportP1->addSource();
    auto transportP1_copy = std::make_shared<MulticastMutexTransport<int>>();
    auto sourceIdP1_copy = std::make_shared<MulticastMutexTransport<int>>();

    auto transportP2 = std::make_shared<MulticastMutexTransport<int>>();
    auto sourceIdP2 = transportP2->addSource();

    auto transportP3 = std::make_shared<MulticastMutexTransport<int>>();
    auto sourceIdP3 = transportP3->addSource();

    // start producer 1
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP1 alive)
    std::thread([=] {

        std::vector<int> collatzValues = {startValue};
        transportP1     ->push(static_cast<int>(collatzValues[0]), 1);
        transportP1_copy->push(static_cast<int>(collatzValues[0]), 1);


        for (std::size_t n = 1; n <= nMax; ++n) { //run through the count we set in start
            if (collatzValues[n - 1] % 2 == 0) {
                collatzValues.push_back(collatzValues[n - 1] / 2);
            } else {
                collatzValues.push_back((collatzValues[n - 1] * 3) + 1);
            }

            transportP1->push(static_cast<int>(collatzValues[n]),
                              1); //push the value you want to push calculate it beforehand!
            std::cout << "production 1 " << collatzValues[n] << std::endl; //print the value you push to see results
        }
        transportP1->signifyCompletion();
    }).detach();

    // start producer 2
    // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
    // so the thread can keep the transportP2 alive)
    std::thread([=] {

        std::vector<int> collatzValues = {};
        std::set<int> ArrayOfSubstractions;
        // consume produced elements
        while (auto next = transportP1->tryPull(sourceIdP1,
                                                "Producer [2] consuming: sourceIdP1")) { //wait for producer 1

            collatzValues.push_back(*next);

            if (collatzValues.size() > 1) {

                for (size_t i = 0; i< collatzValues.size(); i++) {
                    for (size_t j = 0; j< collatzValues.size(); j++)
                    {
                        if(i != j){
                            ArrayOfSubstractions.insert( abs(collatzValues[i] - collatzValues[j]) );
                        }
                    }
                }
            }
        }

        // wir sollten eigentlich einen Tuple ausgeben.
        transportP2->push(static_cast<int>(*ArrayOfSubstractions.rbegin()), 2); // max
        transportP2->push(static_cast<int>(*ArrayOfSubstractions.rend()), 2); // min

        if (transportP2->size() != 2)
            throw std::logic_error("Production 2 unexpected result: " + transportP2->size() );

        std::cout << "production 2 MIN: " << *ArrayOfSubstractions.rbegin() << std::endl;
        std::cout << "production 2 Max: " << *ArrayOfSubstractions.rend() << std::endl;

        transportP2->signifyCompletion();

    }).detach();

    // start producer 3
    std::thread([=] {
        // consume produced elements
        std::size_t valProd3 = 0;
        while (auto next = transportP2->tryPull(sourceIdP2,
                                                "Producer [3] consuming: sourceIdP2")) { //again wait for Producer 2
            //TODO calculate and push right values
            valProd3 = *next; //do math
            transportP3->push(static_cast<int>(valProd3), 3); //push value of Producer 3
            std::cout << "production 3 " << valProd3 << std::endl;
        }

        if (valProd3 != (nMax * (nMax + 1)) / 2) //TODO checks have to be changed after the calculations are changed
            throw std::logic_error("Production 3 unexpected result");

        transportP3->signifyCompletion();

    }).detach();

    //wait for final consume after process is finished:
    // consume produced elements
    //alternatively just joun() producer 3 instead of detach!
    while (auto next = transportP3->tryPull(sourceIdP3, "MainThread consuming: sourceIdP3")) {
        std::cout << "Final Result: " << *next << std::endl;
    }

}

int main(int argc, char *argv[]) {
    try {
        testProducerConsumerQueue(3, 100); //10000000
        std::cout << "All tests ran successfully." << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}