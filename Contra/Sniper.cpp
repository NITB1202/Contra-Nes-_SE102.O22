#include "Sniper.h"
#include "Player.h"
#include "ObjectConfig.h"
#include <math.h>

int Sniper::Angle(int x1, int y1, int x2, int y2) {
	int angle = 0;
	double MinDistance = (x1 - x2) * (x1 - x2) + (y1 - 21 - y2) * (y1 - 21 - y2);
	if (abs(y1 - y2) < 50 && x1 < x2)
	{
		return angle;
	}
	if (abs(y1 - y2) < 50 && x1 > x2)
	{
		return 180;
	}
	if ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) < MinDistance)
	{
		angle = 150; MinDistance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	}
	if ((x1 + 42 - x2) * (x1 + 42 - x2) + (y1 - y2) * (y1 - y2) < MinDistance)
	{
		angle = 30; MinDistance = (x1 + 42 - x2) * (x1 + 42 - x2) + (y1 - y2) * (y1 - y2);
	}
	if ((x1 + 42 - x2) * (x1 + 42 - x2) + (y1 - 42 - y2) * (y1 - 42 - y2) < MinDistance)
	{
		angle = -30; MinDistance = (x1 + 42 - x2) * (x1 + 42 - x2) + (y1 - 42 - y2) * (y1 - 42 - y2);
	}
	if ((x1 - x2) * (x1 - x2) + (y1 - 42 - y2) * (y1 - 42 - y2) < MinDistance)
	{
		angle = -150; MinDistance = (x1 - x2) * (x1 - x2) + (y1 - 42 - y2) * (y1 - 42 - y2);
	}
	return angle;
}

void Sniper::Render()
{
	Sgun->Render();

	if (inDieAnimation)
		AnimationID = DIE_EFFECT_ANIMATION;

	AniHandler->Render(AnimationID, x, y);
}

void Sniper::Update(DWORD dt)
{
	Sgun->Update(dt);

	if (dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > DIE_EFFECT_DURATION)
	{
		Delete();
		return;
	}

	if (inDieAnimation)
	{
		x += vx * dt;
		y += vy * dt;
		return;
	}

	Player* player = Player::GetInstance();
	int px = player->GetX();
	int py = player->GetY();

	if (getState() == HIDDENOFF || getState() == HIDDENON) // Hidden Sniper
	{
		if (this->x - px <= 200 && this->x - px > 0)
		{
			if (getState() == HIDDENOFF)
			{
				setState(HIDDENON);
			}
			else
			{
				this->AnimationID = SNIPER_HIDDEN_END_ANIMATION;
				if (Angle(this->x, this->y, px, py) == 180) {
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
	else if (getState() == NOHIDDENOFF) { // Non-hidden Sniper *TODO: code cho con sniper xoay huong khac

		this->AnimationID = SNIPER_LEFT_LOW_ANIMATION;
		int angle = Angle(this->x, this->y, px, py);

		if (abs(this->x - px) > 350)
		{
			setState(NOHIDDENOFF);
			return;
		}
		switch (angle)
		{
		case 180:
			this->AnimationID = SNIPER_LEFT_BASE_ANIMATION;
			Sgun->Charge(GetX(), GetY() - 12, SHOOT_LEFT, 2);
			break;
		case 150:
			this->AnimationID = SNIPER_LEFT_HIGH_ANIMATION;
			Sgun->Charge(GetX() + 10, GetY(), SHOOT_SNIPER_UP_LEFT, 2);
			break;
		case -150:
			this->AnimationID = SNIPER_LEFT_LOW_ANIMATION;
			Sgun->Charge(GetX() - 5, GetY() - 30, SHOOT_SNIPER_DOWN_LEFT, 2);
			break;
		case 0:
			this->AnimationID = SNIPER_RIGHT_BASE_ANIMATION;
			Sgun->Charge(GetX() + 42, GetY() - 12, SHOOT_RIGHT, 2);
			break;
		case 30:
			this->AnimationID = SNIPER_RIGHT_HIGH_ANIMATION;
			Sgun->Charge(GetX() + 19, GetY() + 10, SHOOT_SNIPER_UP_RIGHT, 2);
			break;
		case -30:
			this->AnimationID = SNIPER_RIGHT_LOW_ANIMATION;
			Sgun->Charge(GetX() + 38, GetY() - 38, SHOOT_SNIPER_DOWN_RIGHT, 2);
			break;
		}
	}
	else { // Water ambush
		this->AnimationID = SNIPER_WATER_OFF;
		if ((this->y > py && this->y - py < 300) || abs(this->x - py) < 32)
		{
			return;
		}
		this->AnimationID = SNIPER_WATER_ON;
		Sgun->Charge(GetX() + 16, GetY(), SHOOT_TOP, 2);
	}
}

void Sniper::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);
}

void Sniper::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	Player* player = Player::GetInstance();
	int dmg = player->GetGunDMG();
	hp = hp - dmg;

	if (hp <= 0 && !inDieAnimation)
	{
		inDieAnimation = true;
		vx = -e->nx*SNIPER_DEFLECT_SPD;
		vy = SNIPER_DEFLECT_SPD;
		dieAnimationStart = GetTickCount64();
	}
}