#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
protected:
	int shootingDirection;
	float spd;
public:
	Bullet(float x, float y, int direction,float spd)
	{
		baseType = BULLET;
		this->x = x;
		this->y = y;
		this->spd = spd;
		shootingDirection = direction;
		width = 0;
		height = 0;
	}
	bool OutOfScreen();
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};

class NormalBullet : public Bullet
{
public:
	NormalBullet(float x, float y, int direction, float spd) : Bullet(x,y,direction,spd)
	{
		width = 8;
		height = 8;
	}
	void Update(DWORD dt);
	void Render();
};

class TurretBullet : public Bullet
{
public:
	TurretBullet(float x, float y, int direction,float spd) : Bullet(x, y, direction,spd)
	{
		baseType = ENEMY;
		width = 6;
		height = 6;
	}
	void Update(DWORD dt);
	void Render();
};