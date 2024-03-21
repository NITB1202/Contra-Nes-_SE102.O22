#pragma once
#include "GameObject.h"

#define RUNMAN_SPRITE_WIDTH 24
#define RUNMAN_SPRITE_HEIGHT 36

#define RUNMAN_START_VX 0.1f
#define RUNMAN_START_VY 0.1f

class Runman :public GameObject
{
public:
	Runman(float x = 0, float y = 0) : GameObject(x, y) 
	{
		vx = RUNMAN_START_VX;
		vy = RUNMAN_START_VY;
		width = RUNMAN_SPRITE_WIDTH;
		height = RUNMAN_SPRITE_HEIGHT;
	}
	void Render() override;
	void Update(DWORD dt) override;
};