#include <iostream>
#include <ios>
#include <algorithm>
#include <execution>

//pass by reference
void IncreaseByOne(int& nro)
{
	nro++;
}

void IncreaseEach(int array[], int size)
{
	std::for_each(array, array+size,IncreaseByOne);
}

void IncreaseEachSeq(int array[], int size)
{
	std::for_each(std::execution::seq, array, array + size, IncreaseByOne);
}
/*
∑ kokeile algoritmille erilaisia suorism‰‰reit‰:
o std::execution::seq
o std::execution::par
o std::execution::par_unseq*/

int GetSum(int array[], int size)
{
	int totalSum = 0;
	/*std::cout << "SUM: " << totalSum << "\n";*/
	for ( int i = 0; i < size; i++)
	{
		int value = array[i];
		totalSum = totalSum +  value;
		/*std::cout << "SUM: " << totalSum << "\n";*/
	}
	return totalSum;
}



void PrintArray(int array[],int  size)
{
	for (int i = 0; i < size;i++)
	{
		std::cout << array[i] << "\n";
	}
}


int main()
{
	const int taulukon_koko = 200;

	int taulukko[taulukon_koko];

	

	/*std::cout << "taulukon koko alussa: " << sizeof(taulukko) << "\n";*/
	for (int i = 0; i < taulukon_koko;i++)
	{
		taulukko[i] = i;
	}
	std::cout << "Taulukon arvo alussa:" << 
		GetSum(taulukko,sizeof(taulukko) / sizeof(int)) << "\n";

	/*for (int nro : taulukko) {
		std::cout << nro << "\n";
	}*/
	std::cout << "Increasing each in array" << "\n";
	IncreaseEachSeq(taulukko, taulukon_koko);

	std::cout << "total sum, after each inreased by one:"
		<< GetSum(taulukko, sizeof(taulukko)/sizeof(int)) << "\n";

	return 0;
}
/*
Luo N alkion kokoinen (suuri) taulukko, johon on talletettu 
luvut 0ÖN-1. Kirjoita ohjelma, joka k‰y
kasvattamassa jokaisen alkion arvoa yhdell‰:

∑ k‰yt‰ std::for_each-algoritmia

∑ kokeile algoritmille erilaisia suorism‰‰reit‰:
o std::execution::seq
o std::execution::par
o std::execution::par_unseq

Havaitsetko n‰in yksinkertaisessa teht‰v‰ss‰ suorituskykyeroja
eri suoritusm‰‰reiden v‰lill‰?

Mit‰ erisuoritusm‰‰reet tarkoittavat?

Huomaa, ett‰ teht‰v‰ vaatii v‰hint‰‰n C++17-version.
*/