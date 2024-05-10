#include "Gun.h"
#include "Game.h"
#include "Collision.h"
#include "SoundManager.h"

void Gun::Charge(float bulletX, float bulletY, int direction, int bulletType)
{
	if (reloadStart != -1)
	{
		if (GetTickCount64() - reloadStart > reloadTime)
		{
			reloadStart = -1;
			cap = MAX_CAP;
		}

		return;
	}

	if (lastShootTime == -1)
		lastShootTime = GetTickCount64();
	else
		if (GetTickCount64() - lastShootTime < chargeTime)
			return;

	lastShootTime = GetTickCount64();

	Bullet* bullet;

	switch (bulletType)
	{
	case 1:
		bullet = new NormalBullet(bulletX, bulletY, direction,spd);
		SoundManager::GetInstance()->Play(NORMAL_BULLET_SHOOT_SOUND);
		break;
	case 2:
		bullet = new TurretBullet(bulletX, bulletY, direction,spd);
		break;
	case 3:
		bullet = new BossStage1Bullet(bulletX, bulletY, direction, spd);
		break;
	case 4:
		bullet = new BigBullet(bulletX, bulletY, direction, spd);
		SoundManager::GetInstance()->Play(BIG_BULLET_SHOOT_SOUND);
		break;
	case 5:
		bullet = new MoonBullet(bulletX, bulletY, direction, spd);
		break;
	}


	bullets.push_back(bullet);

	if (!canReload) return;

	cap--;

	if (cap <= 0)
		reloadStart = GetTickCount64();

}

void Gun::Update(DWORD dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);

		if (!bullets[i]->IsDeleted())
		{
			if (bullets[i]->OutOfScreen())
				bullets[i]->Delete();
			else
			{
				if (bullets[i]->GetBaseType() == ENEMY)
				{
					Player* player = Player::GetInstance();

					LPCOLLISIONEVENT e = Collision::GetInstance()->SweptAABB(player, bullets[i], dt);
					if (e != NULL)
					{
						player->OnCollisionWith(e);
						if (!player->IsUntouchable() && !player->IsDying())
							bullets[i]->Delete();
						break;
					}
				}
				else
				{
					vector<LPGAMEOBJECT> collidableObjects = Game::GetInstance()->GetCurrentScene()->GetCollidableObject(bullets[i]);
					for (int j = 0; j < collidableObjects.size(); j++)
					{
						LPCOLLISIONEVENT e = Collision::GetInstance()->SweptAABB(collidableObjects[j], bullets[i], dt);
						if (e != NULL && (collidableObjects[j]->GetBaseType() == ENEMY || collidableObjects[j]->GetBaseType() == OTHER))
						{
							bullets[i]->Delete();
							collidableObjects[j]->OnCollisionWith(e);
							if (bullets[i]->IsDeleted()) break;
						}
					}
				}
			}
		}

		if (bullets[i]->IsDeleted())
		{
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}

void Gun::Render()
{
	for (int i = 0; i < bullets.size(); i++)
		bullets[i]->Render();
}
