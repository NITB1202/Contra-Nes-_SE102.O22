#include "Sniper.h"
#include "Player.h"
#include "ObjectConfig.h"
#include <math.h>

int Sniper::Angle(int x1, int y1, int x2, int y2) {
	int angle = 0;
	double MinDistance = (x1 - x2) * (x1 - x2) + (y1 - 21 - y2) * (y1 - 21 - y2);
	if (abs(y1 - y2) < 50 && x1 > x2)
	{
		return 180;
	}
	if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < MinDistance)
	{
		angle = 150; MinDistance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	}
	if ((x1  - x2) * (x1  - x2) + (y1 - 42 - y2) * (y1 - 42 - y2) < MinDistance)
	{
		angle = -150; MinDistance = (x1 - x2) * (x1 - x2) + (y1 - 42 - y2) * (y1 - 42 - y2);
	}
	return angle;
}

void Sniper::Render()
{
	if (inDieAnimation)
		AnimationID = DIE_EFFECT_ANIMATION;

	AniHandler->Render(AnimationID, x, y);
	Sgun->Render();
}

void Sniper::Update(DWORD dt)
{
	if (dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > DIE_ANIMATION_DURATION)
	{
		Delete();
		return;
	}

	if (inDieAnimation)
		return;

	Player* player = Player::GetInstance();
	int px = player->GetX();
	int py = player->GetY();

	if (getState() == HIDDENOFF || getState() == HIDDENON) // Hidden Sniper
	{
		if (abs(px - this->x) <= 200)
		{
			if (getState() == HIDDENOFF)
			{
				setState(HIDDENON);
			}
			else
			{
				this->AnimationID = SNIPER_HIDDEN_END_ANIMATION;
				if (Angle(this->x, this->y, px, py)==180) {
					Sgun->Charge(GetX(), GetY() - 8, SHOOT_LEFT, 2);
					Sgun->Update(dt);
				}
			}
		}
		else
		{
			this->AnimationID = SNIPER_HIDDEN_START_ANIMATION;

		}
	}
	else { // Non-hidden Sniper *TODO: code cho con sniper xoay huong khac

		this->AnimationID = SNIPER_LEFT_LOW_ANIMATION;
		int angle = Angle(this->x, this->y, px, py);

		switch (angle)
		{
		case 180:
			this->AnimationID = SNIPER_LEFT_BASE_ANIMATION;
			Sgun->Charge(GetX(), GetY() - 12, SHOOT_LEFT, 2);
			break;
		case 150:
			this->AnimationID = SNIPER_LEFT_HIGH_ANIMATION;
			Sgun->Charge(GetX()+10, GetY(), SHOOT_TOPLEFT, 2);
			break;
		case -150:
			this->AnimationID = SNIPER_LEFT_LOW_ANIMATION;
			Sgun->Charge(GetX(), GetY()-30, SHOOT_DOWNLEFT2, 2);
			break;
		}
		Sgun->Update(dt);
	}
}

void Sniper::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->object->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);
}

void Sniper::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	if (!inDieAnimation)
	{
		inDieAnimation = true;
		AniHandler->Reset();
		dieAnimationStart = GetTickCount64();
	}
}