#pragma once
#include "GameObject.h"

class Fire : public GameObject
{
private:
	float desDistance = 200;
	float distance;
public:
	Fire()
	{
		baseType = ENEMY;
		vx = 0.15f;
		distance = desDistance;
	}
	bool IsBlocking() { return false; }
	void Update(DWORD dt);
	void Render();
};