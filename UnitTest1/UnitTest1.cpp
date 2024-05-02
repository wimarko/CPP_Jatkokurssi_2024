

#include "HitPointsCalculator.h"
#include <HitPointsCalculator.cpp>
#include "pch.h"
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <functional>

#include "CppUnitTest.h"
#include <HitPointsCalculator.cpp>


//pit‰‰ saada joku headeri??

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_50_damage)
		{
			int expected_1 = 50;
			int CurrentHitpoints = 100;
			int damage = 50;

			int actual = TakeDamage(CurrentHitpoints, damage);

			
			Assert::AreEqual(expected_1, actual);
		}

		TEST_METHOD(Test_NegativeHealthReturnsZero)
		{
			int expected_1 = 0;
			int CurrentHitpoints = 100;
			int damage = 150;

			int actual = TakeDamage(CurrentHitpoints, damage);

			Assert::AreEqual(expected_1, actual);
		}
	};
}
