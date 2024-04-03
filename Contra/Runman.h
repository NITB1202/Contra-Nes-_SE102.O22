#pragma once
#include "GameObject.h"

#define RUNMAN_WIDTH 48
#define RUNMAN_HEIGHT 72

#define RUNMAN_START_VX 0.1f
#define RUNMAN_START_VY 0.1f

class Runman :public GameObject
{
public:
	Runman()
	{
		baseType = ENEMY;
		vx = RUNMAN_START_VX;
		vy = RUNMAN_START_VY;
		width = RUNMAN_WIDTH;
		height = RUNMAN_HEIGHT;
	}
	void Render() override;
	void Update(DWORD dt) override;
};