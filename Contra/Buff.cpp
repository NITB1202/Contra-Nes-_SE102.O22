#include "Buff.h"
#include "Player.h"
#include "ObjectConfig.h"
#include "SoundManager.h"
#include "Game.h"
#include "SoundManager.h"

#define BUFF_VX 0.05f
#define BUFF_VY 0.2f

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

	if (!afterBreak && dieAnimationStart != -1 && GetTickCount64() - dieAnimationStart > EXPLODE_EFFECT_DURATION)
	{
		
		this->state = B_EATABLE;
		afterBreak = true;
		inDieAnimation = false;
		return;
	}

	if (afterBreak)
	{
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

		vy -= 0.5 * GRAVITY * dt;

		vector<LPGAMEOBJECT> col = Game::GetInstance()->GetCurrentScene()->GetOnScreenObject();
		Collision::GetInstance()->Process(this, dt, col);

		return;
	}

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

	if (e->desObject->GetBaseType() == GROUND  && e->ny == -1)
	{
		vx = 0;
		vy = 0;
	}
}

void Buff::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	Player* player = Player::GetInstance();
	int dmg = player->GetGunDMG();
	hp = hp - dmg;

	if (!afterBreak)
		SoundManager::GetInstance()->Play(ATTACK_CANNON_SOUND);

	if (hp <= 0 && !inDieAnimation && !afterBreak)
	{
		inDieAnimation = true;
		dieAnimationStart = GetTickCount64();

		this->baseType = ITEM;
		width = 48;
		height = 30;

		vx = e->nx * BUFF_VX;
		vy = BUFF_VY;
		SoundManager::GetInstance()->Play(ENEMY_KILLED);
	}
}

void Buff::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
