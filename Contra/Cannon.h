#pragma once
#include "GameObject.h"
#include "Gun.h"

#define C_CLOSE -1
#define C_INIT 0
#define C_OPEN 1

#define CANNON_HEIGHT 64
#define CANNON_WIDTH 64
#define DIE_ANIMATION_DURATION 300

class Cannon : public GameObject
{
public:
	bool inDieAnimation = false;
	int dieAnimationStart = -1;
	int preState = 0, openDelay = 0, hp = 20;
	bool IsCollidable() { return !inDieAnimation; }
	Gun* Cgun;
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnColllisionWithBullet(LPCOLLISIONEVENT e);
	Cannon()
	{
		baseType = ENEMY;
		width = CANNON_WIDTH;
		height = CANNON_HEIGHT;
		Cgun = new Gun(0.2);
		Cgun->SetChargeTime(1000);
	};
	void Render() override;
	void Update(DWORD dt) override;
	int Angle(int x1, int y1, int x2, int y2);
};

