#pragma once
#include "GameObject.h"
class Player : public GameObject
{
private:
	bool rightPressed = false;
	bool leftPressed = false;
	bool upPressed = false;
	bool downPressed = false;
public:
	Player(float x, float y, float vx, float vy) :GameObject(x, y, vx, vy) {}
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);

	void Press(int key);
	void Release(int key);
	bool IsPressed(int key);
};

#define TEXTURE_PATH_PLAYER_RUN_LEFT L"image\\Player\\bill_run_left.png"
#define TEXTURE_PATH_PLAYER_RUN_RIGHT L"image\\Player\\bill_run_right.png"
#define TEXTURE_PATH_PLAYER_TOP_RIGHT L"image\\Player\\bill_topright.png"

#define PLAYER_SPRITE_WIDTH 28
#define PLAYER_SPRITE_HEIGHT 40

#define PLAYER_RUN_LEFT_ANIMATION 200
#define PLAYER_RUN_RIGHT_ANIMATION 201
#define PLAYER_NOT_CHANGE_STATE 202
#define PLAYER_JUMP_UP_ANIMATION 203
#define PLAYER_LAY_DOWN_ANIMATION 204
#define PLAYER_JUMP_RIGHT_ANIMATION 205
#define PLAYER_JUMP_LEFT_ANIMATION 206
#define PLAYER_TOP_RIGHT 207 

#define PLAYER_START_VX 0.1f
#define PLAYER_START_VY 0.1f