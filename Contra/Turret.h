#pragma once
#include "GameObject.h"
#include "Gun.h"

#define T_CLOSE -1
#define T_INIT 0
#define T_OPEN 1

#define TURRET_HEIGHT 64
#define TURRET_WIDTH 64
#define DIE_ANIMATION_DURATION 300

class Turret : public GameObject
{
public:
	bool inDieAnimation = false;
	int dieAnimationStart = -1;
	int preState = 0, openDelay = 0, hp = 10;
	bool IsCollidable() { return !inDieAnimation; }
	Gun* Tgun;
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnColllisionWithBullet(LPCOLLISIONEVENT e);

	Turret()
	{
		baseType = ENEMY;
		width = TURRET_WIDTH;
		height = TURRET_HEIGHT;
		Tgun = new Gun();
		Tgun->SetChargeTime(2000);
	};
	void Render() override;
	void Update(DWORD dt) override;
	int Angle(int x1, int y1, int x2, int y2);
};