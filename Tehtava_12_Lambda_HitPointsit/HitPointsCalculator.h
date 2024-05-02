#pragma once
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>


#pragma once

class HitPointsCalculator
{
public:
    int TakeDamage(int& hitPoints, const int damage);
    // Other member functions...
    void PrintVector(const std::vector<int>& Vector);


    //no const vector - because gets modified
    int TakeDamage(int& hitPoints, const int damage);


    void TakeHundredDamage(int& currentHealth);



    void CauseHundredDamageToAll(std::vector<int>& targetHealths);

    void CauseDamageToAll(std::vector<int>& targetHealths, int damage);


    //create vector of enemies' health points
    std::vector<int> CreateEnemies();

};



