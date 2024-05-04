#include "FlyRock.h"
#include "ObjectConfig.h"
#include "Player.h"
#include "MyUtility.h"

void FlyRock::Update(DWORD dt)
{

	distance -= abs(vx) * dt;

	if (distance <= 0)
	{
		vx = -vx;
		distance = desDistance;
	}

	x += vx * dt;

	LPPLAYER player = Player::GetInstance();

	if (MyUtility::CheckIntersect(player->GetCollisionBound(), this->GetCollisionBound()) && player->GetY() - player->GetHeight() >= y)
		player->SetPosition(player->GetX() + vx * dt, player->GetY());
}

void FlyRock::Render()
{
	AniHandler->Render(FLYING_ROCK, x, y);
}