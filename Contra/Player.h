#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "ObjectConfig.h"
#include "Gun.h"

#define UNTOUCHABLE_TIME 3000
#define MAX_HP 3

class Player : public GameObject
{
private:

	static Player* instance;
	PlayerState* currentState;
	Gun* gun;

	bool isOnGround = false;
	bool isShooting = false;
	bool untouchable = false;
	bool isUnderWater = false;

	int untouchableStart = -1;

public:
	Player()
	{
		baseType = PLAYER;
		hp = MAX_HP;
		currentState = new PlayerStandingState(RIGHT);
		gun = new Gun(0.3);
	};
	static Player* GetInstance();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void SetGunDMG(int dmg) { gun->SetDMG(dmg); }
	int GetGunDMG(){ return gun->GetDMG(); }
	void SetBulletType(int bulletType){ gun->SetBulletType(bulletType); }
	void GainHP();


	void SetBeginState(int stage);
	void SetCurrentState(PlayerState* newState);
	PlayerState* GetCurrentState() { return currentState; }

	bool IsOnGround() { return isOnGround; }
	bool IsShooting() { return isShooting; }
	bool IsUnderWater() { return isUnderWater; }
	bool IsUntouchable() { return untouchable; }
	bool IsDying() { return currentState == dynamic_cast<PlayerDieState*>(currentState); }

	void Render();
	void Update(DWORD dt);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithEnenmy(LPCOLLISIONEVENT e);
	void OnCollisionWithItem(LPCOLLISIONEVENT e);

	void UntouchableStart();
	void GetRespawnPoint(float& xRespawn, float& yRespawn);
	void Reset();
};
typedef Player* LPPLAYER;