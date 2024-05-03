#include "Buff.h"
#include "Player.h"
#include "ObjectConfig.h"

void Buff::Update(DWORD dt)
{

	Player* player = Player::GetInstance();
	int px = player->GetX();
	int py = player->GetY();
	if (this->state == B_EATEN)
	{
		Delete();
		return;
	}

	if (dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > EXPLODE_EFFECT_DURATION && afterBreak == false)
	{
		
		this->state = B_EATABLE;
		width = BUFF_WIDTH;
		height = BUFF_HEIGHT;
		afterBreak = true;
		inDieAnimation = false;
		return;
	}
	else
	{
		if (this->state < B_EATABLE)
		{
			if (abs(px - this->x) <= 250)
			{
				if (this->state == B_CLOSE)
				{
					this->state = B_OPEN;
					this->preState = B_OPEN;
					this->AnimationID = BUFF_INIT_ANIMATION;
				}
				if (this->state == B_OPEN)
				{
					if (this->preState = B_OPEN)
					{
						openDelay++;
						if (openDelay < 20)
							return;
						else
						{
							this->preState = B_CLOSE;
						}
					}

					this->AnimationID = BUFF_OPEN_ANIMATION;

				}
			}
			else
			{
				openDelay = 0;
				this->AnimationID = BUFF_CLOSE_ANIMATION;
			}
		}
		else
		{
			this->baseType = ITEM;
			switch (buffStat)
			{
			case BUFF_BIG:
				this->AnimationID = BUFF_BIG_ANIMATION;
				this->state = B_BIG;
				break;
			case BUFF_REGEN:
				this->AnimationID = BUFF_REGEN_ANIMATION;
				this->state = B_REGEN;
				break;
			}
		}
	}
}

void Buff::Render()
{
	if (isDeleted) return;
	if (inDieAnimation)
		AnimationID = EXPLODE_EFFECT_ANIMATION;
	AniHandler->Render(AnimationID, x, y);
}

void Buff::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);
}

void Buff::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	Player* player = Player::GetInstance();
	int dmg = player->GetGunDMG();
	hp = hp - dmg;
	if (hp <= 0 && !inDieAnimation || state < B_EATABLE)
	{
		inDieAnimation = true;
		dieAnimationStart = GetTickCount64();
	}
}
