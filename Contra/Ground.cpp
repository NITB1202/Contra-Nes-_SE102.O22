#include "Ground.h"
#include "Player.h"

bool Ground::IsBlocking()
{
	bool isBlocking = blocking;
	blocking = true;
	return isBlocking;
}

void Ground::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->srcObject->GetY() - e->srcObject->GetHeight() < y)
		blocking = false;
}