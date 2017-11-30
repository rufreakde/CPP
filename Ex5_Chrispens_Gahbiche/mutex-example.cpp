
#include <optional>
#include <deque>
#include <vector>
#include <type_traits>
#include <memory>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <iostream>


template <typename T>
    class MulticastMutexTransport
{
private:
    struct SourceData
    {
        std::deque<T> elements;
    };

    std::vector<SourceData> sources;
    std::mutex mutex;
    std::condition_variable cv;
    bool productionCompleted = false;

public:
    using SourceId = std::size_t;

    MulticastMutexTransport(void) = default;

    SourceId addSource(void)
    {
        std::unique_lock<std::mutex> lock(mutex);
        sources.push_back(SourceData());
        return sources.size() - 1;
    }

    void push(T value)
    {
        std::unique_lock<std::mutex> lock(mutex);
        for (auto& source : sources)
            source.elements.push_back(value);
        cv.notify_all();
    }
    void signifyCompletion(void)
    {
        std::unique_lock<std::mutex> lock(mutex);
        productionCompleted = true;
        cv.notify_all();
    }

    std::optional<T> tryPull(SourceId sourceId)
    {
        std::unique_lock<std::mutex> lock(mutex);
        auto& elements = sources.at(sourceId).elements;
        while (!productionCompleted && elements.empty())
            cv.wait(lock);
        
        if (elements.empty())
            return std::nullopt;

        T result = std::move(elements.front());
        elements.pop_front();
        return result;
    }
};

void testProducerConsumerQueue(std::size_t nMax)
{
        // set up transport, add source for ourselves
    auto transport = std::make_shared<MulticastMutexTransport<int>>();
    auto sourceId = transport->addSource();

        // start producer
        // (be sure to capture by value when detaching the thread and to use a shared_ptr<>
        // so the thread can keep the transport alive)
    std::thread([=]
    {
        for (std::size_t n = 1; n <= nMax; ++n)
            transport->push(static_cast<int>(n));
        transport->signifyCompletion();
    }).detach();
    
        // consume produced elements
    std::size_t sum = 0;
    while (auto next = transport->tryPull(sourceId))
        sum += *next;
    
        // verify result
    if (sum != (nMax * (nMax + 1)) / 2)
        throw std::logic_error("unexpected result");
}

int main(int argc, char* argv[])
{
    try
    {
        testProducerConsumerQueue(10000000);
        std::cout << "All tests ran successfully." << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
