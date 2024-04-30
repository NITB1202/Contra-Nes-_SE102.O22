#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "ObjectConfig.h"
#include "Gun.h"

#define UNTOUCHABLE_TIME 3000

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

	int untouchableStartTime = -1;

public:
	Player()	
	{
		baseType = PLAYER;
		hp = 3;
		currentState = new PlayerFallState(RIGHT);
		gun = new Gun();
	};
	static Player* GetInstance();

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void SetCurrentState(PlayerState* newState);
	PlayerState* GetCurrentState() { return currentState; }

	bool IsOnGround() { return isOnGround; }
	bool IsShooting() { return isShooting; }
	bool IsUnderWater() { return isUnderWater; }

	void Render();
	void Update(DWORD dt);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void UntouchableStart();
	void GetRespawnPoint(float& xRespawn, float& yRespawn);

	void OnCollisionWithEnenmy(LPCOLLISIONEVENT e);
};
typedef Player* LPPLAYER;