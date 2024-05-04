#include "Fire.h"
#include "ObjectConfig.h"

void Fire::Update(DWORD dt)
{
	if (state == 1)
		vx = -vx;

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

