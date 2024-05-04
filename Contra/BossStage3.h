#pragma once
#include "GameObject.h"
#include "BossState.h"
#include "Gun.h"

class BossHandBall : public GameObject
{
public:
	void Update(DWORD dt);
	void Render();
};

class BossHand : public GameObject
{
private:
	vector<BossHandBall*> balls;
	Gun* gun;
public:
	BossHand();
	void SetDirection(int dir) { direction = dir; }
	void Update(DWORD dt);
	void Render();
	~BossHand();
};

class BossStage3 : public GameObject
{
private:
	BossState* currentState;
	BossHand* leftHand;
	BossHand* rightHand;
public:
	BossStage3();
	void Update(DWORD dt);
	void Render();
	bool IsBlocking() { return false; }
	~BossStage3();
};