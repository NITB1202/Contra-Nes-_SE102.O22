#pragma once
#include "GameObject.h"

#define PLAYER_SPRITE_WIDTH 28
#define PLAYER_SPRITE_HEIGHT 40

#define PLAYER_RUN_LEFT 200
#define PLAYER_RUN_RIGHT 201
#define PLAYER_IDLE_LEFT 202
#define PLAYER_IDLE_RIGHT 203
#define PLAYER_TOP_RIGHT 204
#define PLAYER_TOP_LEFT 205
#define PLAYER_DOWN_RIGHT 206
#define PLAYER_DOWN_LEFT 207
#define PLAYER_GUN_UP 208
#define PLAYER_LAY_DOWN 209
#define PLAYER_JUMP_UP 210

#define PLAYER_START_VX 0.2f
#define PLAYER_START_VY 0.25f

#define PLAYER_GRAVITY 0.16f

class Player : public GameObject
{
private:
	static Player* instance;
	bool rightPressed = false;
	bool leftPressed = false;
	bool upPressed = false;
	bool downPressed = false;

	int face = 1;
	int maxJumpHeight = 60;

public:
	Player(float x = 0, float y = 0) :GameObject(x, y) 
	{
		vx = PLAYER_START_VX;
		vy = PLAYER_START_VY;
		width = PLAYER_SPRITE_WIDTH;
		height = PLAYER_SPRITE_HEIGHT;
	};
	static Player* GetInstance();

	void SetState(int ID);
	void Render();
	void Update(DWORD dt);

	void Press(int key);
	void Release(int keyCode);
	bool IsPressed(int keyCode);
	void ResetAction() { AniHandler.SetCurrentFrame(-1); }
	int GetFace() { return face; }
};
typedef Player* LPPLAYER;