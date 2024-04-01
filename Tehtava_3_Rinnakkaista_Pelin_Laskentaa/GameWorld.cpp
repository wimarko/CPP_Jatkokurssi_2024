#include "Game_Task.h"
#include "Class_A.h"
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <chrono>

using namespace std::chrono;


class Semaphore {
public: Semaphore (int allowed_threads) : thread_count_(allowed_threads) {}

	  void acquire() 
	  {
		  //unique lock: when going to wait, release mutex-lock..or smthing
		  std::unique_lock<std::mutex> lock(mute_);
		  while (thread_count_ == 0) {
			  condition_.wait(lock);  
		  }
		  thread_count_--;
	  }

	  void release() 
	  {
		  std::lock_guard<std::mutex> lock(mute_);
		  thread_count_++;
		  condition_.notify_one();
	  }

private:
	std::mutex mute_;
	std::condition_variable condition_;
	int thread_count_;
};


int main() {

	std::vector<std::unique_ptr<Game_Task>> tasks;
	std::vector<std::thread> threadsVector;

	unsigned int numThreads = std::thread::hardware_concurrency();
	unsigned int maxThreads = numThreads - 1;
	unsigned int usedThreads = 0;
	Semaphore threadSemaphore(maxThreads);

	std::cout << "Using threads in machine: " << maxThreads << "\n";

	int timeDelay = 3;
	int amount_of_tasks = 30;

	//create "Tasks"-Class_As, give each an id  int(i)
	for (int i = 0; i < amount_of_tasks; i++) {
		tasks.emplace_back(std::make_unique<Class_A>(i));
	}


	int number_of_tasks = tasks.size();
	//auto ~ std::chrono.... k::time_point makes it shorter
	auto start = high_resolution_clock::now();

	//Add each task to threads-vector
	for (auto& task : tasks)
	{
		threadSemaphore.acquire();
		threadsVector.emplace_back([&task, timeDelay,
		&threadSemaphore, &usedThreads]() 
			{
			task->Perform(timeDelay);
			threadSemaphore.release();
			});
		usedThreads++;
	}

	for (auto& thread : threadsVector)
	{
		thread.join();
	}
	//continue only after all tasks are complete!

	std::cout << "Program finished.\n";
	auto stop = high_resolution_clock::now();

	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	auto microseconds = duration.count();
	auto seconds = microseconds / 1000000;
	microseconds %= 1000000;
	/*auto milliseconds = microseconds / 1000;
	microseconds %= 1000;*/

	std::cout <<"Tasks' duration: "<< seconds <<"."<<microseconds << " seconds\n";

	return 0;
}