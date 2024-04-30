#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
private:
	bool blocking = true;
public:
	Ground(){ baseType = GROUND;}
	bool IsBlocking();
	void OnCollisionWith(LPCOLLISIONEVENT e);
};

class Water :public GameObject
{
public:
	Water() { baseType = WATER; }
};