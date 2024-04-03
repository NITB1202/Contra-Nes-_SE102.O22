#include "Collision.h"
#include "MyUtility.h"
#include <Windows.h>
#include <cmath>

Collision* Collision::instance = NULL;

Collision* Collision::GetInstance()
{
	if (instance == NULL)	instance = new Collision();
	return instance;
}

RECT getSweptBroadphaseRect(LPGAMEOBJECT object, float dx, float dy)
{
	float left = dx > 0 ? object->GetX() : object->GetX() + dx;
	float top = dy > 0 ? object->GetY() + dy : object->GetY();
	float right = left + object->GetWidth() + abs(dx);
	float bottom = top - (object->GetHeight() + abs(dy));

	RECT rect = { left, top, right, bottom };

	return rect;
}

LPCOLLISIONEVENT Collision::SweptAABB(LPGAMEOBJECT srcObject, LPGAMEOBJECT desObject, DWORD dt)
{
	float mvx, mvy;
	srcObject->GetSpeed(mvx, mvy);
	float mdx = mvx*dt;
	float mdy = mvy*dt;

	float svx, svy;
 	desObject->GetSpeed(svx, svy);
	float sdx = svx*dt;
	float sdy = svy*dt;
	//
	// NOTE: new m speed = original m speed - collide object speed
	// 
	float dx = mdx - sdx;
	float dy = mdy - sdy;

	if (dx == 0 && dy == 0) return NULL;		// moving object is not moving > obvious no collision

	// Broad-phase test 
	RECT rect = getSweptBroadphaseRect(srcObject,dx,dy);
	if(!MyUtility::CheckIntersect(rect,desObject->GetCollisionBound()))
		return NULL;

	//Swept AABB
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	float nx = 0;
	float ny = 0;

	RECT srcRect = srcObject->GetCollisionBound();
	RECT desRect = desObject->GetCollisionBound();
	
	if (dx > 0.0f)
	{
		dx_entry = desRect.left - srcRect.right;
		dx_exit = desRect.right - srcRect.left;
	}
	else
	{
		dx_entry = desRect.right - srcRect.left;
		dx_exit = desRect.left - srcRect.right;
	}

	if (dy > 0.0f)
	{
		dy_entry = desRect.bottom - srcRect.top;
		dy_exit = desRect.top - srcRect.bottom;
	}
	else
	{
		dy_entry = desRect.top - srcRect.bottom;
		dy_exit = desRect.bottom - srcRect.top;
	}

	if (dx == 0.0f)
	{
		tx_entry = -9999999999.0f;
		tx_exit = 9999999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0.0f)
	{
		ty_entry = -9999999999.0f;
		ty_exit = 99999999999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit || (tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f)
		return NULL;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = 1.0f : ny = -1.0f;
	}

	return new CollisionEvent(desObject,t_entry,nx,ny);
}

vector<LPCOLLISIONEVENT> Collision::GetCollisionEvents(LPGAMEOBJECT srcObject, vector<LPGAMEOBJECT> collidableObjects, DWORD dt)
{
	vector<LPCOLLISIONEVENT> collisionEvents;
	for (int i = 0; i < collidableObjects.size(); i++)
	{
		LPCOLLISIONEVENT event = SweptAABB(srcObject, collidableObjects[i], dt);

		if (event != NULL)
			collisionEvents.push_back(event);
	}

	return collisionEvents;
}

void Collision::GetFirstColEvent(vector<LPCOLLISIONEVENT> colEvents, LPCOLLISIONEVENT& colX, LPCOLLISIONEVENT& colY, int filterBlock, int filterX, int filterY)
{
	float min_tx = 1.0f;
	float min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	for (int i = 0; i < colEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = colEvents[i];
		if (e->deleted) continue;

		// ignore collision event with object having IsBlocking = 0
		if (filterBlock == 1 && !e->object->IsBlocking()) continue;

		if (filterY == 1 && e->entryTime < min_ty && e->ny != 0)
		{
			min_ty = e->entryTime; min_iy = i;
			continue;
		}

		if (filterX == 1 && e->entryTime < min_tx && e->nx != 0)
		{
			min_tx = e->entryTime; min_ix = i;
			continue;
		}
	}

	if (min_ix >= 0) colX = colEvents[min_ix];
	if (min_iy >= 0) colY = colEvents[min_iy];
}

void Collision::Process(LPGAMEOBJECT srcObject, DWORD dt, vector<LPGAMEOBJECT>& collidableObjects)
{
	vector<LPCOLLISIONEVENT> colEvents;
	LPCOLLISIONEVENT colX = NULL;
	LPCOLLISIONEVENT colY = NULL;

	if (srcObject->IsCollidable())
		colEvents = GetCollisionEvents(srcObject,collidableObjects, dt);

	// No collision detected
	if (colEvents.size() == 0)
		srcObject->OnNoCollision(dt);
	else
	{
		GetFirstColEvent(colEvents, colX, colY);

		float x = srcObject->GetX();
		float y = srcObject->GetY();
		float vx = srcObject->GetVx();
		float vy = srcObject->GetVy();

		if (colX != NULL && colY != NULL)
		{
			if (colY->entryTime < colX->entryTime)	// was collision on Y first ?
			{
				y += colY->entryTime * vy*dt;
				srcObject->SetPosition(x, y);
				srcObject->OnCollisionWith(colY);
				// see if after correction on Y, is there still a collision on X ? 
				LPCOLLISIONEVENT colX_other = NULL;
				// remove current collision event on X
				colX->deleted = true;		
				// replace with a new collision event using corrected location 
				LPCOLLISIONEVENT event = SweptAABB(srcObject,colX->object,dt);
				if (event != NULL)
					colEvents.push_back(event);
				//get first event on X after replace
				GetFirstColEvent(colEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);

				if (colX_other != NULL)
				{
					x += colX_other->entryTime * vx;
					srcObject->OnCollisionWith(colX_other);
				}
				else
					x += vx*dt;
			}
			else // collision on X first
			{
				x += colX->entryTime * vx;
				srcObject->SetPosition(x, y);

				srcObject->OnCollisionWith(colX);
				// see if after correction on X, is there still a collision on Y ? 
				LPCOLLISIONEVENT colY_other = NULL;
				// check again if there is true collision on Y
				colY->deleted = true;		// remove current collision event on Y
				// replace with a new collision event using corrected location 
				LPCOLLISIONEVENT event = SweptAABB(srcObject, colY->object, dt);
				if (event != NULL)
					colEvents.push_back(event);
				// re-filter on Y only
				GetFirstColEvent(colEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);

				if (colY_other != NULL)
				{
					y += colY_other->entryTime * vy * dt;
					srcObject->OnCollisionWith(colY_other);
				}
				else
					y += vy*dt;
			}
		}
		else
		{
			if (colX != NULL)
			{
				x += colX->entryTime * vx * dt;
				y += vy*dt;
				srcObject->OnCollisionWith(colX);
			}
			else
			{
				if (colY != NULL)
				{
					x += vx*dt;
					y += colY->entryTime * vy * dt;
					srcObject->OnCollisionWith(colY);
				}
				else // both colX & colY are NULL 
				{
					x += vx*dt;
					y += vy*dt;
				}
			}
		}
		srcObject->SetPosition(x, y);
	}
	//
	// Scan all non-blocking collisions for further collision logic
	//
	for (int i = 0; i < colEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = colEvents[i];
		if (e->deleted) continue;
		if (e->object->IsBlocking() > 0) continue;  // blocking collisions were handled already, skip them

		srcObject->OnCollisionWith(e);
	}

	for (UINT i = 0; i < colEvents.size(); i++) delete colEvents[i];

	colEvents.clear();
}