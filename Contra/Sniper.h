#pragma once
#include "GameObject.h"
#include "Gun.h"

#define SNIPER_WIDTH 48
#define SNIPER_HEIGHT 72
#define DIE_ANIMATION_DURATION 300
#define AMBUSH_ANIMATION_DURATION 300
#define SNIPER_DEFLECT_SPD 0.1f

#define HIDDENOFF 0
#define HIDDENON 1

#define NOHIDDENOFF 2
#define NOHIDDENON 3
#define NOHIDDENACT 4

#define WHIDDENOFF 5
#define WHIDDENON 6

class Sniper:public GameObject
{
private:
	int destination = 200;
	int distance;
	int dieAnimationStart = -1;
	bool inDieAnimation = false;
public:
	Gun* Sgun;
	Sniper()
	{
		hp = 2;
		baseType = ENEMY;
		distance = destination;
		Sgun = new Gun(0.2);
		Sgun->SetChargeTime(2000);
	}
	int getState() { return state; }
	int setState(int i) { state = i; return state; }
	void Render() override;
	void Update(DWORD dt) override;
	bool IsCollidable() { return !inDieAnimation; }
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnColllisionWithBullet(LPCOLLISIONEVENT e);
	int Angle(int x1, int y1, int x2, int y2);
};

