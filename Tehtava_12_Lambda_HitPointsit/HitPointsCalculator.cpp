#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>


void PrintVector(const std::vector<int>& Vector)
{
	for (int i = 0; i < Vector.size(); i++)
	{
		std::cout << Vector[i] << " ";
	}
	std::cout << "\n";
}

//no const vector - because gets modified
int TakeDamage(int &hitPoints,const int damage)
{
		hitPoints = std::max(0, hitPoints-damage);
		return hitPoints;
}

void TakeHundredDamage(int& currentHealth)
{
	currentHealth = TakeDamage(currentHealth, 100);
}

void CauseHundredDamageToAll(std::vector<int>& targetHealths)
{
	std::cout << "Causing 100 damage to all\n";
	std::for_each(targetHealths.begin(), targetHealths.end()
		, TakeHundredDamage);
}


//a function object apparently
void CauseDamageToAll(std::vector<int>& targetHealths, int damage)
{
	std::cout << "Cause given amount (100) of damage to all\n";
	std::for_each(targetHealths.begin(), targetHealths.end(),
		std::bind
		(TakeDamage,
			std::placeholders::_1,
			damage));
}

std::vector<int> CreateEnemies()
{
	std::vector<int> Enemies{ 55,121,222,323,424, 525, 626, 727 };

	//for (int i = 90; i < 111; i++)
	//{
	//	Enemies.push_back(i);
	//}

	std::default_random_engine rng;

	std::shuffle(Enemies.begin(), Enemies.end(), rng);

	return Enemies;
}

int main()
{
	
	std::vector<int> EnemyHitpoints = CreateEnemies();

	PrintVector(EnemyHitpoints);

	CauseHundredDamageToAll(EnemyHitpoints);
	std::cout << "Hitpoints:\n";
	PrintVector(EnemyHitpoints);

	CauseDamageToAll(EnemyHitpoints, 100);
	//EnemyHitpoints[0] =TakeDamage(EnemyHitpoints[0],100);

	/*std::for_each(EnemyHitpoints.begin(),EnemyHitpoints.end(),TakeDamage(100);*/


	std::cout << "Hitpoints:\n";
	PrintVector(EnemyHitpoints);

	return 0;
}



/*
Sinulla on roolipeliss� kokonaislukuvektori (std::vector) kokonaislukuja,
jotka kuvaavat vihollistenhitpointseja (HP). Onnistuneen loitsusi ansiosta
jokaista HP:ta tulisi v�hent�� 100:lla (tai asettaa 0:aan,jos HP 
on t�ll� hetkell� 100 tai alempi).K�yt� v�hennyksen toteutukseen 
std::for_each -algoritmia. 

for_each haluaa saada alkioille teht�v�n
operaation parametrina; toteuta se seuraavilla eri tavoilla:

a. erillisen� funktiona
b. funktio-objektina (tutustu tarvittaessa)
c. lambda-funktiona
d. nimettyn� lambda-funktiona

J�rjest� lopuksi vektori suurimmasta pienimp��n k�ytt�en 
std::sort-funktiota. Anna j�rjestyskriteeri
(laskeva j�rjestys) sort:lle lambda-funktiona.
*/