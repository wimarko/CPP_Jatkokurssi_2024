#pragma once
#include "Game_Task.h"
class Class_A : public  Game_Task
{
public: 
	Class_A(int id);

	virtual void Perform(const int max) override;
	int id;
};

