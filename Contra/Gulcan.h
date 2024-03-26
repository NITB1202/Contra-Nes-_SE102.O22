#pragma once
#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_GULCAN_RUN_RIGHT	L"image\\Enemy\\.png"
#define TEXTURE_PATH_GULCAN_RUN_LEFT	L"image\\Enemy\\.png"
#define TEXTURE_PATH_GULCAN_DEAD		L"image\\Enemy\\.png"

// define all information of GULCAN sprites
#define GULCAN_SPRITE_WIDTH		25
#define GULCAN_SPRITE_HEIGHT		46

#define GULCAN_RUN_RIGHT_ANIMATION	401
#define GULCAN_RUN_LEFT_ANIMATION	402
#define GULCAN_DEAD_ANIMATION		403

#define GULCAN_RUN_LEFT		500
#define GULCAN_RUN_RIGHT	501
#define GULCAN_RUN_DEAD		502

#define GULCAN_GRAVITY		0.16f

#define GULCAN_START_VX		0.2f
#define GULCAN_START_VY		0

class Gulcan : public GameObject
{
private:
	int face = 1;

public:
	Gulcan(float x, float y, float vx = GULCAN_START_VX, float vy = GULCAN_START_VY) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);
	int GetFace() { return face; }
};