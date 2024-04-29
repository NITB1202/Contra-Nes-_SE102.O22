#include "Gun.h"
#include "Game.h"
#include "Collision.h"

void Gun::Charge(float bulletX, float bulletY, int direction, int bulletType)
{
	if (lastShootTime == -1)
		lastShootTime = GetTickCount64();
	else
		if (GetTickCount64() - lastShootTime < CHARGE_TIME + 320)
			return;

	lastShootTime = GetTickCount64();

	Bullet* bullet;

	switch (bulletType)
	{
	case 1:
		bullet = new NormalBullet(bulletX, bulletY, direction);
		break;
	case 2:
		bullet = new TurretBullet(bulletX, bulletY, direction);
		break;
	}

	bullets.push_back(bullet);
}

void Gun::Update(DWORD dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);

		if (bullets[i]->OutOfScreen())
			bullets[i]->Delete();
		else
		{
			vector<LPGAMEOBJECT> collidableObjects = Game::GetInstance()->GetCurrentScene()->GetCollidableObject(bullets[i]);
			for (int j = 0; j < collidableObjects.size(); j++)
			{
				LPCOLLISIONEVENT e = Collision::GetInstance()->SweptAABB(collidableObjects[j], bullets[i], dt);
				if (e != NULL && collidableObjects[j]->GetBaseType() == ENEMY)
				{
					bullets[i]->Delete();
					collidableObjects[j]->OnCollisionWith(e);
					break;
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