#include "BossStage1.h"
#include "ObjectConfig.h"
#include "Game.h"

//Boss gun
void BossGun::Update(DWORD dt)
{
	if (inExplodeAnimation && GetTickCount64() - explodeStart > EXPLODE_EFFECT_DURATION)
	{
		isDestroy = true;
		inExplodeAnimation = false;
	}

	if(!isDestroy) gun->Charge(x - 16, y, 0, 3);
	gun->Update(dt);
}

void BossGun::Render()
{
	if (inExplodeAnimation)
	{
		AniHandler->Render(EXPLODE_EFFECT_ANIMATION, x, y + 10);
		return;
	}

	if (direction == 1)
	{
		if (isDestroy)
			AniHandler->Render(BOSS_GUN_RIGHT_DESTROY_ANIMATION, x, y);
		else
			AniHandler->Render(BOSS_GUN_RIGHT_NORMAL_ANIMATION, x, y);
	}
	else
	{
		if (isDestroy)
			AniHandler->Render(BOSS_GUN_LEFT_DESTROY_ANIMATION, x+10, y-5);
		else
			AniHandler->Render(BOSS_GUN_LEFT_NORMAL_ANIMATION, x, y);
	}

	gun->Render();
}

void BossGun::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
	{
		Player* player = Player::GetInstance();
		int dmg = player->GetGunDMG();
		hp = hp - dmg;

		if (hp <= 0 && !inExplodeAnimation && !isDestroy)
		{
			inExplodeAnimation = true;
			explodeStart = GetTickCount64();
		}
	}
}

//Boss door
void BossDoor::Update(DWORD dt)
{
	if (explodeState > 3)
	{
		Delete();
		inExplodeAnimation = false;
	}

	if (inExplodeAnimation && GetTickCount64() - explodeStart > EXPLODE_EFFECT_DURATION)
	{
		explodeStart = GetTickCount64();
		explodeState++;
	}
}

void BossDoor::Render()
{
	if (inExplodeAnimation)
	{
		if(explodeState == 0)
			AniHandler->Render(EXPLODE_EFFECT_ANIMATION, x, y);
		else
		{
			float explodeX = x + EXPLODE_EFFECT_WIDTH * explodeState;
			AniHandler->Render(EXPLODE_EFFECT_ANIMATION, explodeX, y + EXPLODE_EFFECT_WIDTH / 2);
			AniHandler->Render(EXPLODE_EFFECT_ANIMATION, explodeX, y - EXPLODE_EFFECT_WIDTH / 2);
		}
	}
	else
		AniHandler->Render(BOSS_DOOR_NORMAL_ANIMATION, x, y);
}

void BossDoor::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
	{
		Player* player = Player::GetInstance();
		int dmg = player->GetGunDMG();
		hp = hp - dmg;

		if (hp <= 0 && !inExplodeAnimation)
		{
			inExplodeAnimation = true;
			explodeStart = GetTickCount64();
		}
	}
}

//Boss
BossStage1::BossStage1()
{
	baseType = OTHER;

	gunLeft = new BossGun();
	gunLeft->SetDirection(-1);

	gunRight = new BossGun();
	gunRight->SetDirection(1);
	gunRight->SetSpeed(0.05);

	door = new BossDoor();
}

void BossStage1::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	gunLeft->SetPosition(x + 11, y - 131);
	gunRight->SetPosition(x + 42, y - 133);
	door->SetPosition(x + 23, y - 208);
}

RECT BossStage1::GetCollisionBound()
{
	RECT collisionBound = GameObject::GetCollisionBound();

	if (door->IsDeleted())
		collisionBound.bottom = gunLeft->GetY();

	return collisionBound;
}

void BossStage1::Update(DWORD dt)
{
	if (!insertToObjectTree)
	{
		insertToObjectTree = true;

		BinaryTree* objectTree = Game::GetInstance()->GetCurrentScene()->GetObjectTree();
		objectTree->InsertObject(3000, gunLeft);
		objectTree->InsertObject(3001, gunRight);
		objectTree->InsertObject(3002, door);
	}
}

void BossStage1::Render()
{
	if (door->IsDeleted())
		AniHandler->Render(BOSS_DOOR_DESTROY_ANIMATION,x + 58, y - 208);
}

void BossStage1::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
		e->desObject->Restore();
}