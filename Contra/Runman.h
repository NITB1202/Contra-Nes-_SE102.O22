#pragma once
#include "GameObject.h"
#include "RunmanState.h"

#define RUNMAN_WIDTH 32
#define RUNMAN_HEIGHT 56

class Runman :public GameObject
{
private:

	bool inDieAnimation = false;
	bool isOnGround = false;
	bool isUnderWater = false;

	RunmanState* currentState;

public:
	Runman(int direction)
	{
		width = RUNMAN_WIDTH;
		height = RUNMAN_HEIGHT;
		baseType = ENEMY;
		currentState = new RunmanRunning(direction);
	}
	void Render();
	void Update(DWORD dt);

	bool IsCollidable() { return !inDieAnimation; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnColllisionWithBullet(LPCOLLISIONEVENT e);

	void SetCurrentState(RunmanState* runmanState);
};