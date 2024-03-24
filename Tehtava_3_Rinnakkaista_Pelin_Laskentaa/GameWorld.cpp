#include "Game_Task.h"
#include "Class_A.h"
//#include "Class_B.h"
#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <memory>

//std::mutex mtx;
//std::condition_variable cv;

// TODO pit‰‰ viel‰ tehd‰ semaphore
int main() {

	std::vector<std::unique_ptr<Game_Task>> tasks;
	std::vector<std::thread> threads;

	unsigned int numThreads = std::thread::hardware_concurrency();
	unsigned int maxThreads = numThreads - 1;
	unsigned int usedThreads = 0;

	std::cout << "Using threads in machine: " << maxThreads << "\n";

	int timeDelay = 2;
	int amount_of_tasks = 24;

	for (int i = 0; i < amount_of_tasks; i++) {
		tasks.emplace_back(std::make_unique<Class_A>(i));
		/*Class_A* classA = new Class_A();
		classA->id = i;
		tasks.push_back(classA);*/
	}


	int number_of_tasks = tasks.size();

	//for (int i = 0; i < number_of_tasks; i++)
	//{
	//	/*tasks[i]->Perform(max);*/
	//	threads.emplace_back([&tasks, i,max]() {
	//		tasks[i]->Perform(max);
	//		});		
	//}
	for (auto& task : tasks)
	{
		threads.emplace_back([&task, timeDelay]() {
			task->Perform(timeDelay);
			});
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
	//continue only after all tasks are complete!

	std::cout << "Program finished.\n";

	return 0;
}