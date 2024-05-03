#pragma once
#include "GameObject.h"

#define B_EATEN -2

#define B_CLOSE -1
#define B_INIT 0
#define B_OPEN 1

#define B_EATABLE 2
#define B_BIG 3
#define B_REGEN 4

#define BUFF_HEIGHT 64
#define BUFF_WIDTH 64
#define ITEM_HEIGHT 30
#define ITEM_WIDTH 48
#define DIE_ANIMATION_DURATION 300
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

