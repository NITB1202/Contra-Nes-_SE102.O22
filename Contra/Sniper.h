#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_SNIPER_RUN_RIGHT	L"image\\Enemy\\enemy_sniper_right.png"
#define TEXTURE_PATH_SNIPER_RUN_LEFT	L"image\\Enemy\\enemy_sniper_left.png"
#define TEXTURE_PATH_SNIPER_DEAD		L"image\\Enemy\\run_man_die.png"

// define all information of Sniper sprites
#define SNIPER_SPRITE_WIDTH		25
#define SNIPER_SPRITE_HEIGHT		46

#define SNIPER_RUN_RIGHT_ANIMATION	401
#define SNIPER_RUN_LEFT_ANIMATION	402
#define SNIPER_DEAD_ANIMATION		403

#define SNIPER_RUN_LEFT		500
#define SNIPER_RUN_RIGHT	501
#define SNIPER_RUN_DEAD		502

#define SNIPER_GRAVITY		0.16f

#define SNIPER_START_VX		0.2f
#define SNIPER_START_VY		0

class Sniper : public GameObject
{
private:
	int face = 1;

public:
	Sniper(float x, float y, float vx = SNIPER_START_VX, float vy = SNIPER_START_VY) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);
	int GetFace() { return face; }
};