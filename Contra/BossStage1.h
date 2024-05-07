#pragma once
#include "GameObject.h"
#include "Gun.h"

#define BOSS1_EFFECT_DURATION 1500

class BossGun :public GameObject
{
private:
	bool isDestroy = false;
	bool inExplodeAnimation = false;
	ULONGLONG explodeStart = -1;

	Gun* gun;
public:
	BossGun()
	{
		baseType = OTHER;
		width = 32;
		height = 12;
		hp = 5;
		gun = new Gun();
		gun->SetSpeed(0.1);
		gun->SetChargeTime(1000);
	}
	void SetSpeed(float spd) { gun->SetSpeed(spd); }
	void SetDirection(int direction) { this->direction = direction; }

	void Update(DWORD dt);
	void Render();

	void OnCollisionWith(LPCOLLISIONEVENT e);
	~BossGun() { delete gun; }
};

class BossDoor :public GameObject
{
private:

	int explodeState = 0;
	bool inExplodeAnimation = false;
	ULONGLONG explodeStart = -1;
public:
	BossDoor()
	{
		baseType = OTHER;
		width = 52;
		height = 62;
		hp = 15;
	}
	void Update(DWORD dt);
	void Render();

	void OnCollisionWith(LPCOLLISIONEVENT e);
};

class BossStage1 :public GameObject
{
private:
	BossGun* gunLeft;
	BossGun* gunRight;
	BossDoor* door;
	bool update;
	bool openPortal;
public:
	BossStage1();
	RECT GetCollisionBound();

	void SetPosition(float x, float y);
	void Update(DWORD dt);
	void Render();

	void OnCollisionWith(LPCOLLISIONEVENT e);

	~BossStage1()
	{
		delete gunLeft;
		delete gunRight;
		delete door;
	}
};
