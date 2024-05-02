#pragma once
#include "AnimationHandler.h"
#include "Collision.h"

enum objectClass {
	PLAYER,
	ENEMY,
	GROUND,
	BULLET,
	WATER,
	OTHER
};

class GameObject
{

protected:

	objectClass baseType;
	int hp;

	int width;
	int height;

	float x;
	float y;

	float vx = 0;
	float vy = 0;

	int direction = 1;

	int state = -1;
	int AnimationID = -1;
	AnimationHandler* AniHandler;

	bool isDeleted;
		
public:
	GameObject()
	{
		hp = 1;
		AniHandler = new AnimationHandler();
	}
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void SetWidthHeight(int w, int h) { width = w; height = h; }
	void SetState(int state) { this->state = state; }

	float GetX() { return x; }
	float GetY() { return y; }
	float GetVx() { return vx; }
	float GetVy() { return vy; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int GetBaseType() { return baseType; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	int GetHp() { return hp; }

	AnimationHandler* GetAnimationHandler() { return AniHandler; }
	virtual RECT GetCollisionBound() {
		RECT rect;
		rect.top = y;
		rect.left = x;
		rect.right = x + width;
		rect.bottom = y - height;
		return rect;
	}

	virtual void Update(DWORD dt) {}
	virtual void Render() {}

	void Delete() { isDeleted = true; }
	void Restore() { isDeleted = false; }
	bool IsDeleted() { return isDeleted; }
	virtual bool IsCollidable() { return true; };

	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	virtual bool IsBlocking() { return true; }

	~GameObject()
	{
		delete AniHandler;
	}
};
typedef GameObject* LPGAMEOBJECT;