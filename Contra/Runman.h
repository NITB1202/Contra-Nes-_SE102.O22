#pragma once
#include "GameObject.h"

#define RUNMAN_WIDTH 48
#define RUNMAN_HEIGHT 72

#define RUNMAN_START_VX 0.1f
#define RUNMAN_START_VY 0.1f
#define DIE_ANIMATION_DURATION 300

class Runman :public GameObject
{
private:
	int destination = 200;
	int distance;
	int dieAnimationStart = -1;
	bool inDieAnimation = false;
public:
	Runman()
	{
		vx = RUNMAN_START_VX;
		vy = 0;
		baseType = ENEMY;
		distance = destination;
	}
	void Render() override;
	void Update(DWORD dt) override;
	bool IsCollidable() { return !inDieAnimation; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnColllisionWithBullet(LPCOLLISIONEVENT e);
};