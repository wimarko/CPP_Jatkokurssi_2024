#include <random>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>



int calculated_sum = 0;
//std::mutex g_i_mutex;

//count sum of certain part of Vector
int count_sum(std::vector<int>& Vector, const int start, const int end)
{
	int sum = 0;
	for (int i = start; i < end;i++) {
		sum += Vector[i];
	}

	//this printed line gets mixed by racing threads sometimes
	std::cout << start << "-" << end << " sum: " << sum << "\n";
	calculated_sum += sum;
	return sum;
}


int main() {
	// Seed for random number generation, thanks chatgpt
	std::srand(static_cast<int>(std::time(nullptr)));

	std::vector<int> NumbersVector;

	int realSum = 0;

	int maxSize = 3450; //size of vector

	//Create vector  containing  random numbers (1-50)
	for (int i = 0; i < maxSize;i++) {
		int nro = rand() % 50 + 1;
		realSum += nro;
		NumbersVector.push_back(nro);
	}


	//"division" to chunks
	int chunk_size = NumbersVector.size() / 4;

	std::cout << "vector size: " << NumbersVector.size() <<
		" ,chunk main size: " << chunk_size << "\n";
	int start = 0;
	int chunk_2_start = chunk_size;
	int chunk_3_start = chunk_size * 2;
	int chunk_4_start = chunk_size * 3;




	std::cout << "Creating Futures\n";

	std::future<int> first = std::async([&NumbersVector, start, chunk_2_start]() {
		return count_sum(NumbersVector, start, chunk_2_start);
		});

	std::future<int> second = std::async([&NumbersVector, chunk_2_start, chunk_3_start]() {
		return count_sum(NumbersVector, chunk_2_start, chunk_3_start);
		});


	std::future<int> third = std::async([&NumbersVector, chunk_3_start, chunk_4_start]() {
		return count_sum(NumbersVector, chunk_3_start, chunk_4_start);
		});

	std::future<int> fourth= std::async([&NumbersVector, chunk_4_start]() {
		return count_sum(NumbersVector, chunk_4_start, NumbersVector.size());
		});

		std::cout << "getting future sums\n";
		int sum1 = first.get();
		int sum2 = second.get();
		int sum3 = third.get();
		int sum4 = fourth.get();



	std::cout << "==================\n";
	std::cout << "Real Sum: " << realSum << "\n";
	std::cout << "Threads' Sum: " << calculated_sum << "\n";

	return 0;
}
