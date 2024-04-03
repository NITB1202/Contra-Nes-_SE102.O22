#include "Runman.h"
#include "Game.h"
#include "ObjectConfig.h"

//Runman state define(temp)
#define RUNMAN_RUN_RIGHT 101
#define RUNMAN_RUN_LEFT 102

void Runman::Update(DWORD dt)
{
	if (state == RUNMAN_RUN_RIGHT)
		vx = RUNMAN_START_VX;
	else
		vx = -RUNMAN_START_VX;

	x += vx * dt;
}

void Runman::Render()
{
	if (vx >= 0)
	{
		AnimationID = RUNMAN_RUN_RIGHT_ANIMATION;
	}
	else
	{
		AnimationID = RUNMAN_RUN_LEFT_ANIMATION;
	}

	AniHandler.Render(AnimationID, x, y);
}
