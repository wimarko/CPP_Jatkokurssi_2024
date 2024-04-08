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

void CauseDamageToAll(std::vector<int>& targetHealths, int damage)
{
	std::for_each(targetHealths.begin(), targetHealths.end(),
		std::bind(TakeDamage,
			std::placeholders::_1,
			damage));
}

std::vector<int> CreateEnemies()
{
	std::vector<int> Enemies{ };

	for (int i = 90; i < 111; i++)
	{
		Enemies.push_back(i);
	}

	std::default_random_engine rng;

	std::shuffle(Enemies.begin(), Enemies.end(), rng);

	return Enemies;
}

int main()
{
	
	std::vector<int> EnemyHitpoints = CreateEnemies();

	PrintVector(EnemyHitpoints);

	CauseDamageToAll(EnemyHitpoints, 100);
	//EnemyHitpoints[0] =TakeDamage(EnemyHitpoints[0],100);

	/*std::for_each(EnemyHitpoints.begin(),EnemyHitpoints.end(),TakeDamage(100);*/


	std::cout << "Hitpoints:\n";
	PrintVector(EnemyHitpoints);

	return 0;
}



/*
Sinulla on roolipelissä kokonaislukuvektori (std::vector) kokonaislukuja,
jotka kuvaavat vihollistenhitpointseja (HP). Onnistuneen loitsusi ansiosta
jokaista HP:ta tulisi vähentää 100:lla (tai asettaa 0:aan,jos HP 
on tällä hetkellä 100 tai alempi).Käytä vähennyksen toteutukseen 
std::for_each -algoritmia. 

for_each haluaa saada alkioille tehtävän
operaation parametrina; toteuta se seuraavilla eri tavoilla:

a. erillisenä funktiona
b. funktio-objektina (tutustu tarvittaessa)
c. lambda-funktiona
d. nimettynä lambda-funktiona

Järjestä lopuksi vektori suurimmasta pienimpään käyttäen 
std::sort-funktiota. Anna järjestyskriteeri
(laskeva järjestys) sort:lle lambda-funktiona.
*/