#include "Bullet.h"
#include "ObjectConfig.h"
#include "MyUtility.h"
#include "Game.h"

bool Bullet::OutOfScreen()
{
	return !MyUtility::CheckIntersect(Camera::GetInstance()->GetBound(), this->GetCollisionBound());
}

void NormalBullet::Update(DWORD dt)
{
	switch (shootingDirection)
	{
		case SHOOT_RIGHT:
		{
			vx = BULLET_SPEED;
			vy = 0;
			break;
		}
		case SHOOT_LEFT:
		{
			vx = -BULLET_SPEED;
			vy = 0;
			break;
		}
		case SHOOT_TOP:
		{
			vx = 0;
			vy = BULLET_SPEED;
			break;
		}
		case SHOOT_TOPRIGHT:
		{
			vx = BULLET_SPEED;
			vy = 0.5*BULLET_SPEED;
			break;
		}
		case SHOOT_TOPLEFT:
		{
			vx = -BULLET_SPEED;
			vy = 0.5*BULLET_SPEED;
			break;
		}
		case SHOOT_DOWNRIGHT:
		{
			vx = BULLET_SPEED;
			vy = -0.5 * BULLET_SPEED;
			break;
		}
		case SHOOT_DOWNLEFT:
		{
			vx = -BULLET_SPEED;
			vy = -0.5 * BULLET_SPEED;
			break;
		}
	}

	x += vx * dt;
	y += vy * dt;
}

void NormalBullet::Render()
{
	AniHandler->Render(NORMAL_BULLET, x, y);
}

void TurretBullet::Update(DWORD dt)
{
	switch (shootingDirection)
	{
	case SHOOT_RIGHT:
	{
		vx = BULLET_SPEED;
		vy = 0;
		break;
	}
	case SHOOT_LEFT:
	{
		vx = -BULLET_SPEED;
		vy = 0;
		break;
	}
	case SHOOT_TOP:
	{
		vx = 0;
		vy = BULLET_SPEED;
		break;
	}
	case SHOOT_DOWN:
	{
		vx = 0;
		vy = -BULLET_SPEED;
		break;
	}
	case SHOOT_TOPLEFT:
	{
		vx = -BULLET_SPEED;
		vy = (float)4 / 9 * -vx;
		break;
	}
	case SHOOT_TOPLEFT2:
	{
		vx = -BULLET_SPEED;
		vy = -9 / 4 * vx;
		break;
	}
	case SHOOT_TOPRIGHT:
	{
		vx = BULLET_SPEED;
		vy = 9 / 4 * vx;
		break;
	}
	case SHOOT_TOPRIGHT2:
	{
		vx = BULLET_SPEED;
		vy = (float)4 / 9 * vx;
		break;
	}
	case SHOOT_DOWNRIGHT:
	{
		vx = BULLET_SPEED;
		vy = -(float)4 / 9 * vx;
		break;
	}
	case SHOOT_DOWNRIGHT2:
	{
		vx = BULLET_SPEED;
		vy = -9 / 4 * vx;
		break;
	}
	case SHOOT_DOWNLEFT:
	{
		vx = -BULLET_SPEED;
		vy = 9 / 4 * vx;
		break;
	}
	case SHOOT_DOWNLEFT2:
	{
		vx = -BULLET_SPEED;
		vy = (float)4 / 9 * vx;
		break;
	}
	case SHOOT_SNIPER_UP:
	{
		vx = -BULLET_SPEED;
		vy = sqrt(4 / 3 * vx * vx);
		break;
	}
	case SHOOT_SNIPER_DOWN:
	{
		vx = -BULLET_SPEED;
		vy = -sqrt(4 / 3 * vx * vx);
		break;
	}
	}
	x += vx * dt;
	y += vy * dt;
}

void TurretBullet::Render()
{
	AniHandler->Render(TURRET_BULLET, x, y);
}