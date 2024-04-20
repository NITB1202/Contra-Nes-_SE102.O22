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
	if (abs(x1-x2) < 20 && y1 < y2)
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
	if (abs(y1-y2) < 20 && x1 > x2)
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
	Player* player = Player::GetInstance();
	int px = player->GetX();
	int py = player->GetY();
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
				delay++;
				if (delay < 20)
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
				break;
			case 30:
				this->AnimationID = TURRET_30_ANIMATION;
				break;
			case 60:
				this->AnimationID = TURRET_60_ANIMATION;
				break;
			case 90:
				this->AnimationID = TURRET_90_ANIMATION;
				break;
			case 120:
				this->AnimationID = TURRET_120_ANIMATION;
				break;
			case 150:
				this->AnimationID = TURRET_150_ANIMATION;
				break;
			case 180:
				this->AnimationID = TURRET_180_ANIMATION;
				break;
			case -150:
				this->AnimationID = TURRET_n150_ANIMATION;
				break;
			case -120:
				this->AnimationID = TURRET_n120_ANIMATION;
				break;
			case -90:
				this->AnimationID = TURRET_n90_ANIMATION;
				break;
			case -60:
				this->AnimationID = TURRET_n60_ANIMATION;
				break;
			case -30:
				this->AnimationID = TURRET_n30_ANIMATION;
				break;
			}
		}
	}
	else
	{
		delay = 0;
		this->AnimationID = TURRET_CLOSE_ANIMATION;
	}
}

void Turret::Render()
{
	AniHandler->Render(AnimationID, x, y);
}