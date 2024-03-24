#include "Class_A.h"
#include <iostream>
#include <chrono>


Class_A::Class_A(int given_id)
{
	id = given_id;
}

void Class_A::Perform(const int max)
{
	std::cout << id << " started\n";
	int sum = 0;
	/*long own_max = 9999999 * max;
	std::cout << id<<" A Performing!\n";

	for (int i = 0; i < own_max; i++) {
		sum += 1;
	}*/
	auto start = std::chrono::high_resolution_clock::now();
	while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(max)) {
		/*std::cout << id <<" " <<this<< " A Finished! " << sum << "\n";*/
		
	}
	std::cout << id << ": " << this << " " << "Finished\n";
}
