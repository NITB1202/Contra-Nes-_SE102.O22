#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
public:
	Ground(){ baseType = GROUND;}
	bool IsBlocking();
};

class Water :public GameObject
{
public:
	Water() { baseType = WATER; }
};