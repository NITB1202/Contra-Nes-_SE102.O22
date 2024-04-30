#include "Runman.h"
#include "RunmanState.h"
#include "Game.h"
#include "ObjectConfig.h"

void Runman::SetCurrentState(RunmanState* runmanState)
{
	delete currentState;
	currentState = runmanState;
}

void Runman::Update(DWORD dt)
{
	if (isDeleted) return;

	Camera* camera = Camera::GetInstance();

	if (!inDieAnimation)
	{
		isOnGround = false;
		isUnderWater = false;

		map<int, LPGAMEOBJECT> objectFromTree = Game::GetInstance()->GetCurrentScene()->GetObjectTree()->GetObjectInBound(this->GetCollisionBound());
		vector<LPGAMEOBJECT> collidableObject;

		vy = -RUNMAN_START_VY;

		for (auto it = objectFromTree.begin(); it != objectFromTree.end(); it++)
		{
			LPGAMEOBJECT object = it->second;

			if (object->GetBaseType() == GROUND || object->GetBaseType() == WATER)
				collidableObject.push_back(object);
		}

		Collision::GetInstance()->Process(this, dt, collidableObject);

		if (!isOnGround && !isUnderWater)
			SetCurrentState(new RunmanFalling(currentState->GetDirection()));

		if (isOnGround)
			SetCurrentState(new RunmanRunning(currentState->GetDirection()));

		if (isUnderWater)
		{
			SetCurrentState(new RunmanDieByDrown(currentState->GetDirection()));
			inDieAnimation = true;
		}
	}

	currentState->UpdateStatus(vx, vy, isDeleted);

	if (inDieAnimation)
	{
		x += vx * dt;
		y += vy * dt;
	}

	if (y < camera->getY() - camera->getHeight()) Delete();

}

void Runman::Render()
{
	if (isDeleted) return;

	AnimationID = currentState->GetAnimationID();

	AniHandler->Render(AnimationID, x, y);
}

void Runman::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}

void Runman::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
		OnColllisionWithBullet(e);

	if (e->desObject->GetBaseType() == GROUND)
		isOnGround = true;

	if (e->desObject->GetBaseType() == WATER)
		isUnderWater = true;
}

void Runman::OnColllisionWithBullet(LPCOLLISIONEVENT e)
{
	if (currentState != dynamic_cast<RunmanDieByShooting*>(currentState))
	{
		SetCurrentState(new RunmanDieByShooting(e->nx));
		inDieAnimation = true;
	}
}
