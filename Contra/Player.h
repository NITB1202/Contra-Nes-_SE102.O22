#pragma once
#include "GameObject.h"
#include "PlayerState.h"

#define PLAYER_WIDTH 28
#define PLAYER_HEIGHT 70
#define WATER 10

class Player : public GameObject
{
private:

	static Player* instance;
	PlayerState* currentState;

	int GunUpHeightAdjust = 8;
	bool isOnGround = false;

public:
	Player()	
	{
		baseType = PLAYER;
		width = PLAYER_WIDTH;
		height = PLAYER_HEIGHT;
		currentState = new PlayerFallState(RIGHT);
	};
	static Player* GetInstance();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	PlayerState* GetCurrentState() { return currentState; }
	void SetCurrentState(PlayerState* newState);
	bool IsOnGround() { return isOnGround; }

	void Render();
	void Update(DWORD dt);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
};
typedef Player* LPPLAYER;