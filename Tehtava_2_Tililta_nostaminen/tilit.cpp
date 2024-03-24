#include <iostream>
#include <thread>
#include <mutex>

//Kirjoita ohjelma, jossa on kaksi s‰iett‰, ja jotka k‰sittelev‰t yhteist‰ pankkitili‰.K‰yt‰ s‰ikeiden
//luomiseen std::thread - luokkaa.Ensimm‰inen s‰ie tallettaa rahaa tilille, kun taas toinen nostaa sit‰.
//Nosto - ja talletustapahtumia tulisi olla paljon(tuhansia).P‰‰ohjelma luo s‰ikeet ja odottaa niiden
//p‰‰ttymist‰.
//Tarkista tapahtumien j‰lkeen, ett‰ tilin saldo on korrekti.Jos / kun saldo on v‰‰r‰, k‰yt‰ mutexia
//tapahtumien suojaamiseen.Muokkaa ratkaisua lopuksi niin, ett‰ mutexia k‰ytet‰‰n std::lock_guard:n
//avulla, eksplisiittisten lock() - ja unlock() - kutsujen sijasta.


int account = 0;

std::mutex mute;

void put_money(int amount, int times)
{	
	for (int i = 0; i < times; i++)
	{
		std::unique_lock<std::mutex>lck(mute);
		/*mute.lock();*/
		account += amount;
		/*mute.unlock();*/
	}
	
}

void take_money( int amount, int times)
{
	for (int i = 0; i < times; i++)
	{
		std::unique_lock<std::mutex>lck(mute);
		/*mute.lock();*/
		account -= amount;
		//mute.unlock();
	}
}


int main() 
{
	std::thread put(put_money, 2,10000);
	std::thread take(take_money,2, 10000);

	put.join();
	take.join();

	std::cout << "Account: " << account << "\n";

	return 0;
}