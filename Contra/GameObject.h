#pragma once
#include "AnimationHandler.h"

class GameObject
{
protected:

	int width;
	int height;

	float x;
	float y;

	float vx;
	float vy;

	int state = -1;
	int AnimationID = -1;
	AnimationHandler AniHandler;

public:

	GameObject(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	virtual void SetState(int state) { this->state = state; }

	int GetState() { return state; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	AnimationHandler GetAnimationHandler() { return AniHandler; }
	RECT GetCollisionBound() {
		RECT rect;
		rect.top = y;
		rect.left = x;
		rect.right = x + width;
		rect.bottom = y - height;
		return rect;
	}

	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef GameObject* LPGAMEOBJECT;