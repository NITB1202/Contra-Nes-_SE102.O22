#pragma once
#include "GameObject.h"
#include "PlayerState.h"

#define PLAYER_SPRITE_WIDTH 28
#define PLAYER_SPRITE_HEIGHT 40

class Player : public GameObject
{
private:

	static Player* instance;
	PlayerState* currentState;

	int GunUpHeightAdjust = 8;
	int groundLevel;

public:
	Player(float x = 0, float y = 0) :GameObject(x, y) 
	{
		width = PLAYER_SPRITE_WIDTH;
		height = PLAYER_SPRITE_HEIGHT;
		currentState = new PlayerStandingState(RIGHT);
	};
	void SetPosition(float x, float y);
	static Player* GetInstance();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	PlayerState* GetCurrentState() { return currentState; }
	void SetCurrentState(PlayerState* newState);
	int GetGroundLevel() { return groundLevel; }
	void Render();
	void Update(DWORD dt);
};
typedef Player* LPPLAYER;