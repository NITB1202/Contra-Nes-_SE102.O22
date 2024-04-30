#include "RunmanState.h"
#include "ObjectConfig.h"
#include <Windows.h>

void RunmanRunning::UpdateStatus(float& vx, float& vy, bool& isDeleted)
{
	vx = RUNMAN_START_VX * direction;
	vy = 0;
}

int RunmanRunning::GetAnimationID()
{
	if (direction == RIGHT)
		return RUNMAN_RUN_RIGHT_ANIMATION;

	return RUNMAN_RUN_LEFT_ANIMATION;
}

void RunmanFalling::UpdateStatus(float& vx, float& vy, bool& isDeleted)
{
	vx = RUNMAN_START_VX * direction;
	vy = -RUNMAN_START_VY;
}

int RunmanFalling::GetAnimationID() 
{
	if (direction == RIGHT)
		return RUNMAN_JUMP_RIGHT_ANIMATION;

	return RUNMAN_JUMP_LEFT_ANIMATION;
}

void RunmanJumping::UpdateStatus(float& vx, float &vy, bool& isDeleted)
{
	vx = RUNMAN_START_VX * direction;
	vy = RUNMAN_START_VY;
}

int RunmanJumping::GetAnimationID()
{
	if (direction == RIGHT)
		return RUNMAN_JUMP_RIGHT_ANIMATION;

	return RUNMAN_JUMP_LEFT_ANIMATION;
}

void RunmanDieByShooting::UpdateStatus(float& vx, float& vy, bool& isDeleted)
{
	if (GetTickCount64() - dieAnimationStart > RUNMAN_DIE_BY_GUN_DURATION)
	{
		isDeleted = true;
		return;
	}

	vx = -RUNMAN_DIE_DEFLECT_SPEED * direction;
	vy = RUNMAN_DIE_DEFLECT_SPEED;
}

int RunmanDieByShooting::GetAnimationID()
{
	return DIE_EFFECT_ANIMATION;
}

void RunmanDieByDrown::UpdateStatus(float& vx, float& vy, bool& isDeleted)
{
	if (GetTickCount64() - dieAnimationStart > RUNMAN_DIE_BY_WATER_DURATION)
	{
		isDeleted = true;
		return;
	}

	vx = 0;
	vy = 0;
}

int RunmanDieByDrown::GetAnimationID()
{
	return RUNMAN_IN_WATER_ANIMATION;
}