#pragma once
#include "GameObject.h"
#include "ObjectConfig.h"

class Buff : public GameObject
{
public:
	bool inDieAnimation = false, afterBreak = false;
	ULONGLONG dieAnimationStart = -1;
	int preState = 0, openDelay = 0, hp = 10, buffStat;

	Buff()
	{
		baseType = OTHER;
		width = BUFF_WIDTH;
		height = BUFF_HEIGHT;
		buffStat = rand() % 2;
	};
	void Render();
	void Update(DWORD dt);

	bool IsCollidable() { return !inDieAnimation; }
	bool IsBlocking() { return baseType !=ITEM; }

	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnNoCollision(DWORD dt);
	void OnColllisionWithBullet(LPCOLLISIONEVENT e);
};

