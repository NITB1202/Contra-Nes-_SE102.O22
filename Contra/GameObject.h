#pragma once
#include "AnimationHandler.h"
#include <unordered_map>

using namespace std;

class GameObject
{
protected:

	float x;
	float y;

	float vx;
	float vy;

	int AnimationID = -1;
	AnimationHandler AniHandler;

public:

	GameObject(float x, float y, float vx = 0, float vy = 0)
	{
		this->x = x;
		this->y = y;
		this->vx = vx;
		this->vy = vy;
	}

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }

	virtual void SetState(int state) { AnimationID = state; }
	int GetState() { return this->AnimationID; }

	float GetX() { return x; }
	float GetY() { return y; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef GameObject* LPGAMEOBJECT;