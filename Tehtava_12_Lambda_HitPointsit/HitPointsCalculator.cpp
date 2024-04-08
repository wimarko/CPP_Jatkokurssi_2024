#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>

//print values (healthpoints) 
void PrintVector(const std::vector<int>& Vector)
{
	for (int i = 0; i < Vector.size(); i++)
	{
		std::cout << Vector[i] << " ";
	}
	std::cout << "\n\n";
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

//create vector of enemies' health points
std::vector<int> CreateEnemies()
{
	std::vector<int> Enemies{ 55,121,222,323,424, 525, 626, 727 };

	std::default_random_engine rng;

	std::shuffle(Enemies.begin(), Enemies.end(), rng);

	return Enemies;
}

int main()
{
	

	int lightningBoltDamage = 100; //damage caused as parameter
	std::vector<int> EnemyHitpoints = CreateEnemies();

	PrintVector(EnemyHitpoints);

	CauseHundredDamageToAll(EnemyHitpoints);
	std::cout << "Hitpoints:\n";
	PrintVector(EnemyHitpoints);

	CauseDamageToAll(EnemyHitpoints, lightningBoltDamage);
	//EnemyHitpoints[0] =TakeDamage(EnemyHitpoints[0],100);

	/*std::for_each(EnemyHitpoints.begin(),EnemyHitpoints.end(),TakeDamage(100);*/


	std::cout << "Hitpoints:\n";
	PrintVector(EnemyHitpoints);


	//lambdaa
	/*std::cout << "lambda for take damage for_each\n";
	std::for_each(EnemyHitpoints.begin(), EnemyHitpoints.end(),
		[](int& hitPoints)
		{TakeDamage(hitPoints, 100);});
	std::cout << "Hitpoints:\n";*/

	//the proper lambda..
	//int&hitPoints references is used to reference EnemyHitpoints-int
	std::for_each(EnemyHitpoints.begin(), EnemyHitpoints.end(),
		[&lightningBoltDamage](int& hitPoints)
		{ 
			hitPoints = std::max(0, hitPoints - lightningBoltDamage);
		});
	std::cout << "Hitpoints after lambda:\n";
	PrintVector(EnemyHitpoints);


	std::cout << "Named Lambda damage\n";
	auto lamda_cause_damage = [&lightningBoltDamage](int& hp)
		{
			hp = std::max(0, hp - lightningBoltDamage);
		};

	std::for_each(EnemyHitpoints.begin(), EnemyHitpoints.end(), lamda_cause_damage);

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