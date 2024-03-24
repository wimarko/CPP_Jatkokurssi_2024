#include "Class_A.h"
#include <iostream>
#include <chrono>


Class_A::Class_A(int given_id)
{
	id = given_id;
}

void Class_A::Perform(const int waitingTime)
{
	std::cout << id << " started\n";
	

	auto start = std::chrono::high_resolution_clock::now();
	while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(waitingTime)) {
		
	}
	std::cout << id << ": " << this << " " << "Finished\n";
}
