#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "SoundManager.h"

Player* Player::instance = NULL;

void Player::SetCurrentState(PlayerState* newState)
{
	delete currentState;
	currentState = newState;
}

void Player::GainHP()
{
	if (hp < MAX_HP)
		hp++;
}

void Player::Update(DWORD dt)
{
	if (hp <= 0)
	{
		Game* game = Game::GetInstance();
		if (!game->showMenu)
		{
			game->showMenu = true;
			game->ClearBackGround();
			game->SetCurrentMenu(GAMEOVER_MENU);
		}
		return;
	}

	currentState->UpdateStatus();

	vy += -0.5* GRAVITY * dt;

	//basic collision
	Camera* camera = Camera::GetInstance();

	if (x < camera->getX())
		x = camera->getX();

	if (x > camera->getX() + camera->getWidth() - width)
		x = camera->getX() + camera->getWidth() - width;

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

	if (untouchable && GetTickCount64() - untouchableStart > UNTOUCHABLE_TIME)
	{
		untouchable = false;
		untouchableStart = -1;
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
				gun->Charge(bulletX, bulletY, gunDir, gun->GetBulletType());
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
	if (e->ny != 0 && e->desObject->IsBlocking() && e->desObject->GetBaseType() != ENEMY && e->desObject->GetBaseType() != ITEM)
	{
		vy = 0;
		if (e->ny < 0) isOnGround = true;
	}

	if (e->nx != 0 && e->desObject->IsBlocking())
		vx = 0;

	if (currentState == dynamic_cast<PlayerJumpingState*>(currentState))
		SetCurrentState(new PlayerFallState(currentState->GetDirection()));

	if (e->desObject->GetBaseType() == ENEMY)
		OnCollisionWithEnenmy(e);

	if (e->desObject->GetBaseType() == ITEM)
		OnCollisionWithItem(e);

	if (e->desObject->GetBaseType() == OTHER)
		e->desObject->OnCollisionWith(e);

	if (e->desObject->GetBaseType() == WATER)
		isUnderWater = true;
}

void Player::OnCollisionWithEnenmy(LPCOLLISIONEVENT e)
{
	if (untouchable)
		return;

	if (currentState != dynamic_cast<PlayerDieState*>(currentState)) {
		SetCurrentState(new PlayerDieState(e->nx));
		SoundManager::GetInstance()->Play(DEAD_MUSIC);
	}
}

void Player::OnCollisionWithItem(LPCOLLISIONEVENT e)
{
	int item = e->desObject->GetState();
	switch (item)
	{
	case B_BIG:
		SetGunDMG(2);
		SetBulletType(4);
		break;
	case B_REGEN:
		GainHP();
		break;
	}
	SoundManager::GetInstance()->Play(EAT_ITEM_SOUND);
	e->desObject->SetState(B_EATEN);
}


void Player::Render()
{
	if (hp <= 0) return;

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
	untouchableStart = GetTickCount64();
}

void Player::GetRespawnPoint(float& xRespawn, float& yRespawn)
{
	vector<LPGAMEOBJECT> objectOnScreen = Game::GetInstance()->GetCurrentScene()->GetOnScreenObject();
	vector<LPGAMEOBJECT> canRespawnObject;

	for (int i = 0; i < objectOnScreen.size(); i++)
	{
		if (objectOnScreen[i]->GetBaseType() == GROUND || objectOnScreen[i]->GetBaseType() == OTHER)
		{
			if (objectOnScreen[i]->GetX() <= x && x + width <= objectOnScreen[i]->GetX() + objectOnScreen[i]->GetWidth())
			{
				xRespawn = x;
				yRespawn = objectOnScreen[i]->GetY() + PLAYER_HEIGHT;
				return;
			}
			canRespawnObject.push_back(objectOnScreen[i]);
		}
	}

	float minDistance = -1;

	for (int i = 0; i < canRespawnObject.size(); i++)
	{
		float headDistance = abs(x - canRespawnObject[i]->GetX());
		float tailDistance = abs(x - (canRespawnObject[i]->GetX() + canRespawnObject[i]->GetWidth()));

		float canRespawnX, canRespawnY, distance;

		if (headDistance <= tailDistance)
		{
			canRespawnX = canRespawnObject[i]->GetX();
			distance = headDistance;
		}
		else
		{
			canRespawnX = canRespawnObject[i]->GetX() + canRespawnObject[i]->GetWidth() - PLAYER_WIDTH;
			distance = tailDistance;
		}

		canRespawnY = canRespawnObject[i]->GetY() + PLAYER_HEIGHT;
		
		if (minDistance == -1 || distance < minDistance)
		{
			minDistance = distance;
			xRespawn = canRespawnX;
			yRespawn = canRespawnY;
		}
	}
}

void Player::Reset()
{
	hp = MAX_HP + 1;
	SetGunDMG(1);
	SetBulletType(1);
	UntouchableStart();
}

void Player::SetBeginState(int stage)
{
	switch (stage)
	{
	case 1:
	{
		SetCurrentState(new PlayerFallState(RIGHT));
		break;
	}
	}
}
