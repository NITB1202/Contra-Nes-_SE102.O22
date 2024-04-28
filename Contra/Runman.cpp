#include "Runman.h"
#include "Game.h"
#include "ObjectConfig.h"

//Runman state define(temp)
#define RUNMAN_RUN_RIGHT 101
#define RUNMAN_RUN_LEFT 102

void Runman::Update(DWORD dt)
{
	if (dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > DIE_ANIMATION_DURATION)
	{
		Delete();
		return;
	}

	x += vx * dt;
	y += vy * dt;

	if (inDieAnimation)
		return;

	distance -= abs(vx) * dt;

	if (distance <= 0)
	{
		distance = destination;
		vx = -vx;
	}
}

void Runman::Render()
{
	if (inDieAnimation)
		AnimationID = DIE_EFFECT_ANIMATION;
	else
	{
		if (vx >= 0)
			AnimationID = RUNMAN_RUN_RIGHT_ANIMATION;
		else
			AnimationID = RUNMAN_RUN_LEFT_ANIMATION;
	}

	AniHandler->Render(AnimationID, x, y);
}

void Runman::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->object->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);
}

void Runman::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	if (!inDieAnimation)
	{
		inDieAnimation = true;
		dieAnimationStart = GetTickCount64();
		vx = e->nx * -RUNMAN_START_VX;
		vy = RUNMAN_START_VY;
	}
}