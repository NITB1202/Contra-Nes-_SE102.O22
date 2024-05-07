#pragma once
#include "GameObject.h"
#include "BossState.h"
#include "Gun.h"

class BossHandBall : public GameObject
{
private:
	bool top;
	bool damaged;
	float r;
	float centerX, centerY;
	float alpha;
public:
	BossHandBall();

	void SetTop() { top = true; }
	void SetCircleMovement(float centerX, float centerY, float r);
	void SetAlpha(float a) { alpha = a; }
	void SetDirection(int dir) { direction = dir; }

	float GetAlpha() { return alpha; }
	bool IsDamaged() { return damaged; }

	void Update(DWORD dt);
	void Render();

	void OnCollisionWith(LPCOLLISIONEVENT e);
};

class BossHand : public GameObject
{
private:
	ULONGLONG insertTime = -1;
	ULONGLONG explodeAnimationStart = -1;
	bool isDestroy = false;

	float maxAlpha;
	float minAlpha;
	float vr;

	vector<BossHandBall*> balls;
	Gun* gun;

public:
	BossHand();

	void Insert();
	void SetDirection(int dir) { direction = dir; }
	void SetMaxAlpha(float a) { maxAlpha = a; }
	void SetMinAlpha(float a) { minAlpha = a; }
	void SetVr(float v) { vr = v; }
	void Damage() { hp--; }
	void Destroy() { hp = 0; }

	void Update(DWORD dt);
	void Render();

	~BossHand();
};

class BossStage3 : public GameObject
{
private:

	bool appear;
	ULONGLONG arriveTime;

	BossState* currentState;
	BossHand* leftHand;
	BossHand* rightHand;
	Gun* gun;

	bool inExplodeAnimation;
	ULONGLONG explodeStart;
	int explodeState;
	bool destroy;

	AnimationHandler* effectHandler;

public:
	BossStage3();

	void Update(DWORD dt);
	void Render();

	void SetPosition(float x, float y);
	bool IsCollidable() { return currentState == dynamic_cast<BossOpen*>(currentState); }
	void OnCollisionWith(LPCOLLISIONEVENT e);

	~BossStage3();
};