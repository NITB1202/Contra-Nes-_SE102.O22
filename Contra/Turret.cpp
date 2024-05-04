#include "Turret.h"
#include "Player.h"
#include "ObjectConfig.h"
#include <cmath>

int Turret::Angle(int x1, int y1, int x2, int y2)
{
	int angle = 0;
	double MinDistance = (x1 + 18 - x2) * (x1 + 18 - x2) + (y1 - 16 - y2) * (y1 - 16 - y2);
	if (abs(y1 - y2) < 20 && x1 < x2)
		return angle;
	if ((x1 + 18 - x2) * (x1 + 18 - x2) + (y1 - 15 - y2) * (y1 - 15 - y2) < MinDistance)
	{
		angle = 30; MinDistance = (x1 + 18 - x2) * (x1 + 18 - x2) + (y1 - 15 - y2) * (y1 - 15 - y2);
	}
	if ((x1 + 17 - x2) * (x1 + 17 - x2) + (y1 - 14 - y2) * (y1 - 14 - y2) < MinDistance)
	{
		angle = 60; MinDistance = (x1 + 17 - x2) * (x1 + 17 - x2) + (y1 - 14 - y2) * (y1 - 14 - y2);
	}
	if (abs(x1 - x2) < 20 && y1 < y2)
	{
		angle = 90;
		return angle;
	}
	if ((x1 + 15 - x2) * (x1 + 15 - x2) + (y1 - 14 - y2) * (y1 - 14 - y2) < MinDistance)
	{
		angle = 120; MinDistance = (x1 + 15 - x2) * (x1 + 15 - x2) + (y1 - 14 - y2) * (y1 - 14 - y2);
	}
	if ((x1 + 14 - x2) * (x1 + 14 - x2) + (y1 - 15 - y2) * (y1 - 15 - y2) < MinDistance)
	{
		angle = 150; MinDistance = (x1 + 14 - x2) * (x1 + 14 - x2) + (y1 - 15 - y2) * (y1 - 15 - y2);
	}
	if (abs(y1 - y2) < 20 && x1 > x2)
	{
		angle = 180; return angle;
	}
	if ((x1 + 14 - x2) * (x1 + 14 - x2) + (y1 - 17 - y2) * (y1 - 17 - y2) < MinDistance)
	{
		angle = -150; MinDistance = (x1 + 14 - x2) * (x1 + 14 - x2) + (y1 - 17 - y2) * (y1 - 17 - y2);
	}
	if ((x1 + 15 - x2) * (x1 + 15 - x2) + (y1 - 18 - y2) * (y1 - 18 - y2) < MinDistance)
	{
		angle = -120; MinDistance = (x1 + 15 - x2) * (x1 + 15 - x2) + (y1 - 18 - y2) * (y1 - 18 - y2);
	}
	if (abs(x1 - x2) < 20 && y1 > y2)
	{
		angle = -90; return angle;
	}
	if ((x1 + 17 - x2) * (x1 + 17 - x2) + (y1 - 18 - y2) * (y1 - 18 - y2) < MinDistance)
	{
		angle = -60; MinDistance = (x1 + 17 - x2) * (x1 + 17 - x2) + (y1 - 18 - y2) * (y1 - 18 - y2);
	}
	if ((x1 + 18 - x2) * (x1 + 18 - x2) + (y1 - 17 - y2) * (y1 - 17 - y2) < MinDistance)
	{
		angle = -30; MinDistance = (x1 + 18 - x2) * (x1 + 18 - x2) + (y1 - 17 - y2) * (y1 - 17 - y2);
	}

	return angle;
}
void Turret::Update(DWORD dt)
{
	Tgun->Update(dt);

	Player* player = Player::GetInstance();
	int px = player->GetX();
	int py = player->GetY();

	if (dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > EXPLODE_EFFECT_DURATION)
	{
		Delete();
		return;
	}
	else
	{
		if (abs(px - this->x) <= 250)
		{
			if (this->state == T_CLOSE)
			{
				this->state = T_OPEN;
				this->preState = T_OPEN;
				this->AnimationID = TURRET_OPENING_ANIMATION;
			}
			if (this->state == T_OPEN)
			{
				if (this->preState = T_OPEN)
				{
					openDelay++;
					if (openDelay < 20)
						return;
					else
					{
						this->preState = T_CLOSE;
					}
				}

				int angle = Angle(this->x, this->y, px, py);

				switch (angle)
				{
				case 0:
					this->AnimationID = TURRET_0_ANIMATION;
					Tgun->Charge(GetX() + 31, GetY() - 15, SHOOT_RIGHT, 2);
					break;
				case 30:
					this->AnimationID = TURRET_30_ANIMATION;
					Tgun->Charge(GetX() + 31, GetY() - 7, SHOOT_TOPRIGHT2, 2);
					break;
				case 60:
					this->AnimationID = TURRET_60_ANIMATION;
					Tgun->Charge(GetX() + 23, GetY(), SHOOT_TOPRIGHT, 2);
					break;
				case 90:
					this->AnimationID = TURRET_90_ANIMATION;
					Tgun->Charge(GetX() + 15, GetY(), SHOOT_TOP, 2);
					break;
				case 120:
					this->AnimationID = TURRET_120_ANIMATION;
					Tgun->Charge(GetX() + 7, GetY(), SHOOT_TOPLEFT2, 2);
					break;
				case 150:
					this->AnimationID = TURRET_150_ANIMATION;
					Tgun->Charge(GetX(), GetY() - 7, SHOOT_TOPLEFT, 2);
					break;
				case 180:
					this->AnimationID = TURRET_180_ANIMATION;
					Tgun->Charge(GetX(), GetY() - 15, SHOOT_LEFT, 2);
					break;
				case -150:
					this->AnimationID = TURRET_n150_ANIMATION;
					Tgun->Charge(GetX(), GetY() - 23, SHOOT_DOWNLEFT2, 2);
					break;
				case -120:
					this->AnimationID = TURRET_n120_ANIMATION;
					Tgun->Charge(GetX() + 7, GetY() - 31, SHOOT_DOWNLEFT, 2);
					break;
				case -90:
					this->AnimationID = TURRET_n90_ANIMATION;
					Tgun->Charge(GetX() + 15, GetY() - 31, SHOOT_DOWN, 2);
					break;
				case -60:
					this->AnimationID = TURRET_n60_ANIMATION;
					Tgun->Charge(GetX() + 23, GetY() - 31, SHOOT_DOWNRIGHT2, 2);
					break;
				case -30:
					this->AnimationID = TURRET_n30_ANIMATION;
					Tgun->Charge(GetX() + 31, GetY() - 23, SHOOT_DOWNRIGHT, 2);
					break;
				}
				Tgun->Update(dt);

			}
		}
		else
		{
			openDelay = 0;
			this->AnimationID = TURRET_CLOSE_ANIMATION;
		}
	}
}

void Turret::Render()
{
	Tgun->Render();

	if (isDeleted) return;
	if (inDieAnimation)
		AnimationID = EXPLODE_EFFECT_ANIMATION;
	AniHandler->Render(AnimationID, x, y);
}

void Turret::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);
}

void Turret::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	Player* player = Player::GetInstance();
	int dmg = player->GetGunDMG();
	hp = hp - dmg;

	if (hp <= 0 && !inDieAnimation)
	{
		inDieAnimation = true;
		dieAnimationStart = GetTickCount64();
	}
}