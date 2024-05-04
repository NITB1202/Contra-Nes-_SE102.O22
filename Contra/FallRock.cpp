#include "FallRock.h"
#include "Player.h"
#include "ObjectConfig.h"
#include "Game.h"

void FallRock::Update(DWORD dt)
{
	if (!falling && y - height - Player::GetInstance()->GetY() < trackDistance)
		falling = true;

	vector<LPGAMEOBJECT> collidableObject = Game::GetInstance()->GetCurrentScene()->GetCollidableObject(this);
	for (int i = 0; i < collidableObject.size(); i++)
	{
		if (collidableObject[i]->GetBaseType() == GROUND && collidableObject[i] != blockObject)
		{
			LPCOLLISIONEVENT e = Collision::GetInstance()->SweptAABB(this, collidableObject[i],dt);
			if (e != NULL)
			{
				blockObject = collidableObject[i];
				vy = REFLECT_SPD;
				break;
			}
		}
	}


	if (falling)
	{
		vy += -0.5 * GRAVITY * dt;
		y += vy * dt;
	}
}

void FallRock::Render()
{
	AniHandler->Render(ROCK_ANIMATION, x, y);
}

void FallRock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	LPPLAYER player = Player::GetInstance();

	if (e->srcObject->GetBaseType() == PLAYER && e->ny == 1)
		player->SetCurrentState(new PlayerDieState(player->GetCurrentState()->GetDirection()));
}