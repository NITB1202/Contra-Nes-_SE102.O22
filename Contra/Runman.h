#pragma once
#include "GameObject.h"

class Runman :public GameObject
{
public:
	Runman(float x, float y, float vx, float vy) : GameObject(x, y, vx, vy) {};
	void Render() override;
	void Update(DWORD dt) override;
};

#define TEXTURE_PATH_RUNMAN_LEFT L"image\\Enemy\\run_man_left.png"
#define TEXTURE_PATH_RUNMAN_RIGHT L"image\\Enemy\\run_man_right.png"

#define RUNMAN_SPRITE_WIDTH 24
#define RUNMAN_SPRITE_HEIGHT 36

#define RUNMAN_RUN_LEFT_ANIMATION 100
#define RUNMAN_RUN_RIGHT_ANIMATION 101

#define RUNMAN_START_VX 0.1f
#define RUNMAN_START_VY 0.1f