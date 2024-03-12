#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_SHOOTER_RUN_RIGHT	L"image\\Enemy\\enemy_shooter_right.png"
#define TEXTURE_PATH_SHOOTER_RUN_LEFT	L"image\\Enemy\\enemy_shooter_left.png"
#define TEXTURE_PATH_SHOOTER_DEAD		L"image\\Enemy\\run_man_die.png"

// define all information of Shooter sprites
#define SHOOTER_SPRITE_WIDTH		35
#define SHOOTER_SPRITE_HEIGHT		35

#define SHOOTER_RUN_RIGHT_ANIMATION	401
#define SHOOTER_RUN_LEFT_ANIMATION	402
#define SHOOTER_DEAD_ANIMATION		403

#define SHOOTER_RUN_LEFT		500
#define SHOOTER_RUN_RIGHT	501
#define SHOOTER_RUN_DEAD		502

#define SHOOTER_GRAVITY		0.16f

#define SHOOTER_START_VX		0.2f
#define SHOOTER_START_VY		0

class Shooter : public GameObject
{
private:
	int face = 1;

public:
	Shooter(float x, float y, float vx = SHOOTER_START_VX, float vy = SHOOTER_START_VY) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);
	int GetFace() { return face; }
};