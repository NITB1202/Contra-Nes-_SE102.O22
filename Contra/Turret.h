#pragma once
#include "GameObject.h"

#define T_CLOSE -1
#define T_INIT 0
#define T_OPEN 1

#define TURRET_SPRITE_HEIGHT 32
#define TURRET_SPRITE_WIDTH 32

class Turret : public GameObject
{
public:
	int preState=0, delay = 0;
	Turret(float x = 0, float y = 0) : GameObject(x, y) 
	{
		width = TURRET_SPRITE_WIDTH;
		height = TURRET_SPRITE_HEIGHT;
	};
	void Render() override;
	void Update(DWORD dt) override;
	int Angle(int x1, int y1, int x2, int y2);
};