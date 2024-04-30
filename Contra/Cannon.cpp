#include "Cannon.h"
#include "ObjectConfig.h"
#include "Player.h"
#include <math.h>

void Cannon::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->object->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);
}

void Cannon::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	if (!inDieAnimation)
	{
		hp--;
		if (hp <= 0)
		{
			inDieAnimation = true;
			AniHandler->Reset();
			dieAnimationStart = GetTickCount64();
		}
	}
}

void Cannon::Render()
{
	if (inDieAnimation)
		AnimationID = DIE_EFFECT_ANIMATION;
	AniHandler->Render(AnimationID, x, y);
	Cgun->Render();
}

void Cannon::Update(DWORD dt)
{
	Player* player = Player::GetInstance();
	int px = player->GetX();
	int py = player->GetY();
	if (dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > DIE_ANIMATION_DURATION)
	{
		Delete();
		return;
	}
	else
		if (this->x - px <= 250 && this->x - px > 0)
		{
			if (this->state == C_CLOSE)
			{
				this->state = C_OPEN;
				this->preState = C_OPEN;
				this->AnimationID = CANNON_OPENING_ANIMATION;
			}
			if (this->state == C_OPEN)
			{
				if (this->preState = C_OPEN)
				{
					openDelay++;
					if (openDelay < 20)
						return;
					else
					{
						this->preState = C_CLOSE;
					}
				}
				int angle = Angle(this->x, this->y, px, py);

				switch (angle)
				{
				case 120:
					this->AnimationID = CANNON_120_ANIMATION;
					Cgun->Charge(GetX() + 7, GetY(), SHOOT_TOPLEFT2, 2);
					break;
				case 150:
					this->AnimationID = CANNON_150_ANIMATION;
					Cgun->Charge(GetX(), GetY() - 7, SHOOT_TOPLEFT, 2);
					break;
				case 180:
					this->AnimationID = CANNON_180_ANIMATION;
					Cgun->Charge(GetX(), GetY() - 15, SHOOT_LEFT, 2);
					break;
				}
				Cgun->Update(dt);

			}
		}
		else
		{
			openDelay = 0;
			this->AnimationID = CANNON_CLOSE_ANIMATION;
		}
}

int Cannon::Angle(int x1, int y1, int x2, int y2)
{
	int angle = 180;
	double MinDistance = (x1 + 15 - x2) * (x1 + 15 - x2) + (y1 - 15 - y2) * (y1 - 15 - y2);
	if (abs(y1 - y2) < 50 && x1 > x2)
		return angle;
	if ((x1 - x2) * (x1 - x2) + (y1 - 5 - y2) * (y1 - 5 - y2) < MinDistance)
	{
		angle = 150; MinDistance = (x1 - x2) * (x1  - x2) + (y1 - 5 - y2) * (y1 - 5 - y2);
	}
	if ((x1 +5 - x2) * (x1 +5 - x2) + (y1  - y2) * (y1 - y2) < MinDistance)
	{
		angle = 120; MinDistance = (x1 +5 - x2) * (x1 +5 - x2) + (y1 - y2) * (y1 - y2);
	}
	return angle;
}
