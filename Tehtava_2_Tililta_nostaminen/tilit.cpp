#include <iostream>
#include <thread>
#include <mutex>


int account = 0;

std::mutex mute;

void put_money(int amount, int times)
{	
	for (int i = 0; i < times; i++)
	{
		std::unique_lock<std::mutex>lck(mute);

		account += amount;
	}
	
}

void take_money( int amount, int times)
{
	for (int i = 0; i < times; i++)
	{
		std::unique_lock<std::mutex>lck(mute);

		account -= amount;
	}
}


int main() 
{
	std::thread put(put_money, 2,10000);
	std::thread take(take_money,2, 10000);

	put.join();
	take.join();

	std::cout << "Account: " << account << "\n"; //should be 0
	std::cout << "Account should be: 0! - equal puts and takes\n";

	return 0;
}