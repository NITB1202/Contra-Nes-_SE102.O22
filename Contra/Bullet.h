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

class BossStage1Bullet : public Bullet
{
private:
	bool inExplodeAnimation = false;
	DWORD explodeStart = -1;
public:
	BossStage1Bullet(float x, float y, int direction, float spd) : Bullet(x, y, direction, spd)
	{
		baseType = ENEMY;
		width = 16;
		height = 16;
		vx = -spd;
		vy = 0.2;
	}
	void Update(DWORD dt);
	void Render();
};

class BigBullet : public Bullet
{
public:
	BigBullet(float x, float y, int direction, float spd) : Bullet(x, y, direction, spd)
	{
		width = 16;
		height = 16;
	}
	void Update(DWORD dt);
	void Render();
};
