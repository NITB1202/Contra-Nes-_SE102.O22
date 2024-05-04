#pragma once
#include "GameObject.h"
#include "ObjectConfig.h"

class Buff : public GameObject
{
public:
	bool inDieAnimation = false, afterBreak = false;
	int dieAnimationStart = -1;
	int preState = 0, openDelay = 0, hp = 10, buffStat;
	bool IsCollidable() { return !inDieAnimation; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnColllisionWithBullet(LPCOLLISIONEVENT e);

	Buff()
	{
		baseType = ENEMY;
		width = BUFF_WIDTH;
		height = BUFF_HEIGHT;
		buffStat = rand() % 2;
	};
	void Render() override;
	void Update(DWORD dt) override;
};

