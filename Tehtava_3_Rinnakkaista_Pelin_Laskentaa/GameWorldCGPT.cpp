#include "Game_Task.h"
#include "Class_A.h"
#include <iostream>
#include <vector>
#include <thread>
#include <memory>
//#include <semaphore>
#include <mutex>

std::mutex mtx;
std::condition_variable cv;

class Semaphore {
public:
    Semaphore(int count) : count_(count) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ == 0) {
            condition_.wait(lock);
        }
        count_--;
    }

    void release() {
        std::lock_guard<std::mutex> lock(mutex_);
        count_++;
        condition_.notify_one();
    }

private:
    std::mutex mutex_;
    std::condition_variable condition_;
    int count_;
};


int main2() {
    std::vector<std::unique_ptr<Game_Task>> tasks;
    std::vector<std::thread> threads;

    unsigned int numThreads = std::thread::hardware_concurrency();
    unsigned int maxThreads = numThreads - 1; // Keep one thread free
    unsigned int activeThreads = 0;
    Semaphore threadSemaphore(maxThreads);

    std::cout << "Using threads in machine: " << maxThreads << "\n";

    int timeDelay = 2;
    int amount_of_tasks = 25;

    for (int i = 0; i < amount_of_tasks; i++) {
        tasks.push_back(std::make_unique<Class_A>(i));
    }

    for (auto& task : tasks) {
        threadSemaphore.acquire(); // Acquire semaphore before creating thread
        threads.emplace_back([&task, timeDelay, &threadSemaphore, &activeThreads]() {
            task->Perform(timeDelay);
            threadSemaphore.release(); // Release semaphore after task is completed
            activeThreads--;
            });
        activeThreads++;
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Program finished.\n";

    return 0;
}
