#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_PLAYER_FACE_RIGHT_IDLE L"image\\Player\\bill_stand_right.png"
#define TEXTURE_PATH_PLAYER_RUN_RIGHT L"image\\Player\\bill_run_right.png"
#define TEXTURE_PATH_PLAYER_TOP_RIGHT L"image\\Player\\bill_topright.png"
#define TEXTURE_PATH_PLAYER_DOWN_RIGHT L"image\\Player\\bill_downright.png"
#define TEXURE_PATH_PLAYER_GUN_UP L"image\\Player\\bill_up.png"
#define TEXURE_PATH_PLAYER_LAY_DOWN L"image\\Player\\bill_lay_down.png"
#define TEXTURE_PATH_PLAYER_JUMP_UP L"image\\Player\\bill_jump.png"

#define PLAYER_SPRITE_WIDTH 28
#define PLAYER_SPRITE_HEIGHT 40
#define PLAYER_JUMP_WIDTH 22
#define PLAYER_JUMP_HEIGHT 20
#define PLAYER_GUN_UP_HEIGHT 46
#define PLAYER_LAY_DOWN_WIDTH 34

#define PLAYER_IDLE_RIGHT_ANIMATION 300
#define PLAYER_RUN_RIGHT_ANIMATION 301
#define PLAYER_TOP_RIGHT_ANIMATION 302
#define PLAYER_DOWN_RIGHT_ANIMATION 303
#define PLAYER_LAY_DOWN_ANIMATION 304

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
#define PLAYER_START_VY 0.2f

#define PLAYER_GRAVITY 0.16f

class Player : public GameObject
{
private:

	bool rightPressed = false;
	bool leftPressed = false;
	bool upPressed = false;
	bool downPressed = false;

	int face = 1;
	int maxJumpHeight = 60;

public:
	Player(float x, float y, float vx, float vy) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);

	void Press(int key);
	void Release(int keyCode);
	bool IsPressed(int keyCode);
	void ResetAction() { AniHandler.SetCurrentFrame(-1); }
	int GetFace() { return face; }
};