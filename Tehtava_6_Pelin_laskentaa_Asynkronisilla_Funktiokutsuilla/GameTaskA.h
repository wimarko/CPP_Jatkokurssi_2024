#pragma once
#include "GameTaskSuper.h"

class GameTaskA : public  GameTaskSuper
{
public:
	GameTaskA(int id);

	virtual void Perform(const int max) override;
	int id;
};

