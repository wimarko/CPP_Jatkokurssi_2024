#include "Game_Task.h"
#include "Class_A.h"
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <chrono>
#include <future>

using namespace std::chrono;


class Semaphore {


private:
	std::mutex mute_;
	std::condition_variable condition_;
};


int main() {

	std::vector<std::unique_ptr<Class_A>> tasks;
	std::vector<std::future<void>> futuresVector;

	int timeDelay = 3;
	int amount_of_tasks = 30;

	

	int number_of_tasks = tasks.size();

	//create "Tasks"-Class_As, give each an id  int(i)
	for (int i = 0; i < amount_of_tasks; i++) {
		tasks.emplace_back(std::make_unique<Class_A>(i));
	}

	//auto ~ std::chrono.... k::time_point makes it shorter
	auto start = high_resolution_clock::now();

	//Add each task to threads-vector
	for (auto& task : tasks)
	{
		futuresVector.emplace_back(std::async(std::launch::async, [&task, timeDelay]() {
			task->Perform(timeDelay);
			}));
	}

	for (auto& future : futuresVector)
	{
		future.get();
	}
	//continue only after all tasks are complete!

	std::cout << "Program  async gameworld finished.\n";
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