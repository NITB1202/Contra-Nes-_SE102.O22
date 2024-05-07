#include "Fire.h"
#include "ObjectConfig.h"

void Fire::SetState(int state)
{
	GameObject::SetState(state);
	if (state == 1) vx = -0.15;
}

void Fire::Update(DWORD dt)
{
	distance -= abs(vx) * dt;

	if (distance <= 0)
	{
		vx = -vx;
		distance = desDistance;
	}

	x += vx * dt;
}

void Fire::Render()
{
	AniHandler->Render(FIRE_ANIMATION, x, y);
}

