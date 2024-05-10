#include "Transition.h"

Transition::Transition(float xStart, float yStart, float xEnd, float yEnd, float vx, float vy, int ID)
{
	baseType = OTHER;

	this->xStart = xStart;
	this->yStart = yStart;
	this->xEnd = xEnd;
	this->yEnd = yEnd;

	this->vx = vx;
	this->vy = vy;
	AnimationID = ID;

	finish = false;
}

void Transition::Begin()
{
	finish = false;
	x = xStart;
	y = yStart;
}

void Transition::Update(DWORD dt)
{
	if (x == xEnd && y == yEnd)
	{
		finish = true;
		return;
	}

	x += vx * dt;
	y += vy * dt;

	if ((vx < 0 && x < xEnd) || (vx > 0 && x > xEnd ))
		x = xEnd;

	if ((vy < 0 && y < yEnd) || (vy > 0 && y > yEnd))
		y = yEnd;
}

void Transition::Render()
{
	AniHandler->DrawAsset(AnimationID, x, y);
}