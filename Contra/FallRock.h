#pragma once
#include "GameObject.h"

#define REFLECT_SPD 0.05f

class FallRock : public GameObject
{
private:
	bool falling = false;
	float trackDistance = 80;
	LPGAMEOBJECT blockObject = NULL;
public:
	FallRock()
	{
		baseType = OTHER;
		vy = -0.15;
	}
	void Update(DWORD dt);
	void Render();

	void OnCollisionWith(LPCOLLISIONEVENT e);
};