#pragma once
#include "GameObject.h"

#define T_CLOSE -1
#define T_INIT 0
#define T_OPEN 1

#define TURRET_HEIGHT 48
#define TURRET_WIDTH 48

class Turret : public GameObject
{
public:
	int preState = 0, delay = 0;
	Turret()
	{
		baseType = ENEMY;
		width = TURRET_WIDTH;
		height = TURRET_HEIGHT;
	};
	void Render() override;
	void Update(DWORD dt) override;
	int Angle(int x1, int y1, int x2, int y2);
};