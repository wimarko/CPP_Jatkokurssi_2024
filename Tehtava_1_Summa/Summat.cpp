#include <random>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>



int calculated_sum = 0;
//std::mutex g_i_mutex;

//count sum of certain part of Vector
void count_sum(std::vector<int> &Vector,const int start, const int end)
{
	int sum = 0;
	for (int i = start; i < end;i++) {
		sum += Vector[i];
	}

	//this printed line gets mixed by racing threads sometimes
	std::cout << start << "-" << end << " sum: " << sum << "\n";
	calculated_sum += sum;
}


int main() {
	// Seed for random number generation, thanks chatgpt
	std::srand(static_cast<int>(std::time(nullptr)));

	std::vector<int> NumbersVector;

	int realSum = 0;
	
	int maxSize = 3450; //size of vector

	//Create vector  containing  random numbers (1-50)
	for (int i = 0; i < maxSize;i++) {
		int nro = rand() % 50 +1;
		realSum += nro;
		NumbersVector.push_back(nro);
	}

	
	//"division" to chunks
	int chunk_size = NumbersVector.size() / 4;

	std::cout << "vector size: " << NumbersVector.size() << " ,chunk main size: " << chunk_size << "\n";
	int start = 0;
	int chunk_2_start = chunk_size;
	int chunk_3_start = chunk_size * 2;
	int chunk_4_start = chunk_size * 3;
#pragma region futures



	
	/*std::cout << "Creating Futures\n";

	std::future<int> first = std::async([&NumbersVector, start, chunk_1_end]() {
		return count_sum(NumbersVector, start, chunk_1_end);
		});
	
	std::future<int> second = std::async([&NumbersVector, chunk_1_end, chunk_2_end]() {
		return count_sum(NumbersVector, chunk_1_end, chunk_2_end);
		});


	std::future<int> third = std::async([&NumbersVector, chunk_2_end, chunk_3_end]() {
		return count_sum(NumbersVector, chunk_2_end, chunk_3_end);
		});

	std::future<int> fourth= std::async([&NumbersVector, chunk_3_end]() {
		return count_sum(NumbersVector, chunk_3_end, NumbersVector.size());
		});*/

	/*std::cout << "getting future sums\n";*/

	/*int sum1 = first.get();
	int sum2 = second.get();
	int sum3 = third.get();
	int sum4 = fourth.get();*/
#pragma endregion

	//thread for each chunk-sum
	//apparently need that std::ref to work (thanks chatgpt)
	std::thread first(count_sum,std::ref(NumbersVector), start, chunk_2_start);
	std::thread second(count_sum ,std::ref(NumbersVector), chunk_2_start, chunk_3_start);
	std::thread third(count_sum, std::ref(NumbersVector), chunk_3_start, chunk_4_start);
	std::thread fourth(count_sum,std::ref(NumbersVector), chunk_4_start, NumbersVector.size());


	first.join();
	second.join();
	third.join();
	fourth.join();

	std::cout << "==================\n";
	std::cout << "Real Sum: " << realSum << "\n";
	std::cout << "Threads' Sum: " << calculated_sum << "\n";

	return 0;
}
