#pragma once
#include "GameObject.h"
#include "PlayerState.h"
#include "Gun.h"

#define UNTOUCHABLE_TIME 3000

class Player : public GameObject
{
private:

	static Player* instance;
	PlayerState* currentState;
	Gun* gun;

	int GunUpHeightAdjust = 8;
	bool isOnGround = false;
	bool isShooting = false;
	bool untouchable = false;

	int untouchableStartTime = -1;

public:
	Player()	
	{
		baseType = PLAYER;
		currentState = new PlayerFallState(RIGHT);
		gun = new Gun();
	};
	static Player* GetInstance();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void SetCurrentState(PlayerState* newState);
	PlayerState* GetCurrentState() { return currentState; }
	bool IsOnGround() { return isOnGround; }

	void Render();
	void Update(DWORD dt);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void UntouchableStart();

	void OnCollisionWithEnenmy(LPCOLLISIONEVENT e);
};
typedef Player* LPPLAYER;