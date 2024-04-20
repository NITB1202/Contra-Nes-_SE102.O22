#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
protected:
	int shootingDirection;
public:
	Bullet(float x, float y, int direction)
	{
		baseType = BULLET;
		this->x = x;
		this->y = y;
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
	NormalBullet(float x, float y, int direction) : Bullet(x,y,direction)
	{
		width = 8;
		height = 8;
	}
	void Update(DWORD dt);
	void Render();
};

#define BULLET_SPEED 0.3f