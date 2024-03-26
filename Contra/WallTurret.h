#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_WALLTURRET_RUN_RIGHT	L"image\\Enemy\\.png"
#define TEXTURE_PATH_WALLTURRET_RUN_LEFT	L"image\\Enemy\\.png"
#define TEXTURE_PATH_WALLTURRET_DEAD		L"image\\Enemy\\.png"

// define all information of WALLTURRET sprites
#define WALLTURRET_SPRITE_WIDTH		25
#define WALLTURRET_SPRITE_HEIGHT		46

#define WALLTURRET_RUN_RIGHT_ANIMATION	401
#define WALLTURRET_RUN_LEFT_ANIMATION	402
#define WALLTURRET_DEAD_ANIMATION		403

#define WALLTURRET_RUN_LEFT		500
#define WALLTURRET_RUN_RIGHT	501
#define WALLTURRET_RUN_DEAD		502

#define WALLTURRET_GRAVITY		0.16f

#define WALLTURRET_START_VX		0.2f
#define WALLTURRET_START_VY		0

class WallTurret : public GameObject
{
private:
	int face = 1;

public:
	WallTurret(float x, float y, float vx = WALLTURRET_START_VX, float vy = WALLTURRET_START_VY) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);
	int GetFace() { return face; }
};