#pragma once
#include "GameObject.h"

class FlyRock : public GameObject
{
private:
	float desDistance = 192;
	float distance;
public:

	FlyRock()
	{
		baseType = OTHER;
		vx = 0.05f;
		distance = desDistance;
	}
	void Update(DWORD dt);
	void Render();
};
