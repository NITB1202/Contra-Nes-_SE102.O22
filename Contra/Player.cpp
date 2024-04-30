#include "Player.h"
#include "Camera.h"
#include "Game.h"

Player* Player::instance = NULL;

void Player::SetCurrentState(PlayerState* newState)
{
	delete currentState;
	currentState = newState;
}

void Player::Update(DWORD dt)
{
	currentState->UpdateStatus();

	vy += -0.5*PLAYER_GRAVITY * dt;

	//basic collision
	Camera* camera = Camera::GetInstance();

	if (x < camera->getX())
		x = camera->getX();

	if (y < camera->getY() - camera->getHeight())
	{
		float xRespawn, yRespawn;
		GetRespawnPoint(xRespawn, yRespawn);
		x = xRespawn;
		y = yRespawn;
		UntouchableStart();
	}

	isOnGround = false;
	isUnderWater = false;

	if (untouchable && GetTickCount64() - untouchableStartTime > UNTOUCHABLE_TIME)
	{
		untouchable = false;
		untouchableStartTime = -1;
	}

	vector<LPGAMEOBJECT> colliableObject = Game::GetInstance()->GetCurrentScene()->GetCollidableObject(this);
	Collision::GetInstance()->Process(this, dt, colliableObject);

	//Charge gun
	if (isShooting)
	{
		float bulletX, bulletY;
		int gunDir;
		if (currentState->GetGunDirection(bulletX, bulletY, gunDir))
		{
			if (currentState->CanShoot())
				gun->Charge(bulletX, bulletY, gunDir);
		}
	}

	//Gun Update
	gun->Update(dt);
}

void Player::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Player::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->desObject->IsBlocking() && e->desObject->GetBaseType() != ENEMY)
	{
		vy = 0;
		if (e->ny < 0) isOnGround = true;
	}

	if (e->nx != 0 && e->desObject->IsBlocking())
		vx = 0;

	if (e->desObject->GetBaseType() == ENEMY)
		OnCollisionWithEnenmy(e);

	if (e->desObject->GetBaseType() == WATER)
		isUnderWater = true;
}

void Player::OnCollisionWithEnenmy(LPCOLLISIONEVENT e)
{
	if (untouchable)
		return;

	if (currentState != dynamic_cast<PlayerDieState*>(currentState))
		SetCurrentState(new PlayerDieState(e->nx));
}

void Player::Render()
{
	AnimationID = currentState->GetStateAnimation();

	if (currentState == dynamic_cast<PlayerGunOverHeadState*>(currentState))
	{
		int gunUpYAdjust = y + 15;
		int gunUpXAdjust = currentState->GetDirection() == RIGHT ? x : x + 15;
		AniHandler->Render(AnimationID, gunUpXAdjust, gunUpYAdjust);
	}
	else
		AniHandler->Render(AnimationID, x, y);

	gun->Render();

	for (int i = 0; i < hp; i++)
		AniHandler->DrawAsset(PLAYER_LIFE, 10 + LIFE_ASSET_WIDTH * i, 12);
}		

Player* Player::GetInstance() 
{
	if (instance == NULL) instance = new Player();
	return instance;
}

void Player:: OnKeyDown(int keyCode)
{
	PlayerState* newState = currentState->OnKeyDown(keyCode);

	if (newState != NULL)
		SetCurrentState(newState);

	if (keyCode == DIK_S)
		isShooting = true;
}

void Player::OnKeyUp(int keyCode)
{
	PlayerState* newState = currentState->OnKeyUp(keyCode);

	if (newState != NULL)
		SetCurrentState(newState);

	if (keyCode == DIK_S)
		isShooting = false;
}

void Player::UntouchableStart()
{
	hp--;
	untouchable = true;
	untouchableStartTime = GetTickCount64();
}

void Player::GetRespawnPoint(float& xRespawn, float& yRespawn)
{
	vector<LPGAMEOBJECT> objectOnScreen = Game::GetInstance()->GetCurrentScene()->GetOnScreenObject();
	float minDistance = -1;

	for (int i = 0; i < objectOnScreen.size(); i++)
	{
		if (objectOnScreen[i]->GetBaseType() == GROUND || objectOnScreen[i]->GetBaseType() == WATER)
		{
			if (currentState->GetDirection() == RIGHT)
			{
				float endPoint = objectOnScreen[i]->GetX() + objectOnScreen[i]->GetWidth();
				float distance = x - endPoint;
				if ((distance >= 0) && (minDistance == -1 || distance < minDistance))
				{
					minDistance = distance;
					xRespawn = endPoint - PLAYER_WIDTH;
					yRespawn = objectOnScreen[i]->GetY() + PLAYER_HEIGHT;
				}
			}
			else
			{
				float distance = objectOnScreen[i]->GetX() - ( x + width);
				if ((distance >= 0) && (minDistance == -1 || distance < minDistance))
				{
					minDistance = distance;
					xRespawn = objectOnScreen[i]->GetX();
					yRespawn = objectOnScreen[i]->GetY() + PLAYER_HEIGHT;
				}
			}
		}
	}
}
