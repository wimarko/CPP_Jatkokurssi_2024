
#include "GameTaskA.h"
#include "GameTaskSuper.h"
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <chrono>
#include <future>

using namespace std::chrono;




int main() {

	std::vector<std::unique_ptr<GameTaskSuper>> tasks;
	std::vector<std::future<void>> futuresVector;

	int timeDelay = 3;
	int amount_of_tasks = 30;


	//create "Tasks", give each an id  int(i)
	for (int i = 0; i < amount_of_tasks; i++) {
		tasks.emplace_back(std::make_unique<GameTaskA>(i));
	}

	//auto ~ std::chrono.... k::time_point makes it shorter
	auto start = high_resolution_clock::now();

	//Add each task to async vector
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

	std::cout << "Tasks' duration: " << seconds << "." << microseconds << " seconds\n";

	return 0;
}