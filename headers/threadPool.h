#pragma once
#include <functional>
#include <future>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <condition_variable>

class ThreadPool
{
public:
    using Task = std::function<void()>;

    explicit ThreadPool(std::size_t numThreads)
    {
        start(numThreads);
    }

    ~ThreadPool()
    {
        stop();
    }

    int getPoolSize() const
    {
        return threads.size();
    }

    //im gonna be real honest, i barely know how this works
    template<class T>
    auto enqueue(T task) -> std::future<decltype(task())>
    {
        //something about wrapping the task to get a future value.
        auto wrapper = std::make_shared<std::packaged_task<decltype(task())()>>(std::move(task));
        {
            std::unique_lock<std::mutex> lock{eventMutex};
            tasks.emplace([=]
            {
                (*wrapper)();
            });
        }

        event.notify_one();
        return wrapper->get_future();
    }

private:
    // the "pool" of threads
    std::vector<std::thread> threads;
    /**
    synchronization primitive that allows threads to wait until a certain condition is satisfied.
    It enables "wait and notify" behavior between threads, where one or multiple
    threads can be blocked until another thread sends a notification.
     */
    std::condition_variable event;
    std::mutex eventMutex;
    bool stopping = false;

    std::queue<Task> tasks;

    // start will initialize the threads
    void start(std::size_t numThreads)
    {
        for (int i = 0; i < numThreads; i++)
        {
            threads.emplace_back([=]
                                 {
                while (true)
                {
                    Task task;
                    {
                        // locks the following block so only one thread can access the following code 
                        std::unique_lock<std::mutex> lock{eventMutex};

                        // blocks current thread from executing unless stopping or non-empty tasks
                        event.wait(lock, [=] { return stopping || !tasks.empty();});

                        // only stop if tasks are completed and notified to stop
                        if (stopping && tasks.empty())
                            break;
                        
                        //removes the first task and prepares it
                        task = std::move(tasks.front());
                        tasks.pop();
                    }

                    //performs the first task, this is out of scope because it should not be locked by the mutex during execution
                    task();

                } });
        }
    }

    void stop() noexcept
    {
        {
            std::unique_lock<std::mutex> lock{eventMutex};
            stopping = true;
        }
        event.notify_all();

        for (std::thread &thread : threads)
        {
            thread.join();
        }
    }
};
