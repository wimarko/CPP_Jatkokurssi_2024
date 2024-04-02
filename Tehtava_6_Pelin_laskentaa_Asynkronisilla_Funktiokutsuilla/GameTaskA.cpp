#include "GameTaskA.h"
#include <iostream>
#include <chrono>


GameTaskA::GameTaskA(int given_id)
{
	id = given_id;
}

void GameTaskA::Perform(const int waitingTime)
{
	std::cout << id << " started\n";


	auto start = std::chrono::high_resolution_clock::now();
	while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(waitingTime)) {

	}
	std::cout << id << ": " << this << " " << "Finished\n";
}
