#pragma once
#include <vector>
#include <Windows.h>
using namespace std;

class GameObject;
typedef GameObject* LPGAMEOBJECT;

class CollisionEvent
{
public:

	LPGAMEOBJECT object;

	float entryTime;
	float nx, ny;
	bool deleted;

	CollisionEvent(LPGAMEOBJECT obj, float t, float nx, float ny)
	{
		object = obj;
		entryTime = t;
		this->nx = nx;
		this->ny = ny;
		deleted = false;
	}
	void Delete() { deleted = true; }
};
typedef CollisionEvent* LPCOLLISIONEVENT;

class Collision
{
	static Collision* instance;
public:
	static Collision* GetInstance();
	LPCOLLISIONEVENT SweptAABB(LPGAMEOBJECT scrObject, LPGAMEOBJECT desObject, DWORD dt);
	vector<LPCOLLISIONEVENT> GetCollisionEvents(LPGAMEOBJECT srcObject, vector<LPGAMEOBJECT> collidableObjects, DWORD dt);
	void GetFirstColEvent(vector<LPCOLLISIONEVENT> colEvents, LPCOLLISIONEVENT& colX, LPCOLLISIONEVENT& colY, int filterBlock = 1, int filterX = 1, int filterY = 1);
	void Process(LPGAMEOBJECT srcObject, DWORD dt, vector<LPGAMEOBJECT>& collidableObjects);

};