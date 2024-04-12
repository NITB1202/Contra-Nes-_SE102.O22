#pragma once
#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_GULCAN	L"image\\Enemy\\Gulcan.png"

// define all information of GULCAN sprites
#define GULCAN_SPRITE_WIDTH			32
#define GULCAN_SPRITE_HEIGHT		32
#define GULCAN_DEAD_ANIMATION		6001

class Gulcan : public GameObject
{
private:
	int face = 1;

public:
	Gulcan(float x, float y, float vx = 0, float vy = 0) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);
	int GetFace() { return face; }
};