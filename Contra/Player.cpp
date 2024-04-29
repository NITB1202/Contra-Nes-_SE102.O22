#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "ObjectConfig.h"

Player* Player::instance = NULL;

void Player::SetCurrentState(PlayerState* newState)
{
	delete currentState;
	currentState = newState;
	AniHandler->Reset();
}

void Player::Update(DWORD dt)
{
	currentState->UpdateStatus();

	vy += -0.5*PLAYER_GRAVITY * dt;

	//basic collision
	Camera* camera = Camera::GetInstance();

	if (x < camera->getX())
		x = camera->getX();

	isOnGround = false;

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
			gun->Charge(bulletX, bulletY, gunDir);
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
	if (e->ny != 0 && e->object->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnGround = true;
	}

	if (e->nx != 0 && e->object->IsBlocking())
		vx = 0;

	if (e->object->GetBaseType() == ENEMY)
		OnCollisionWithEnenmy(e);
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

	if (AnimationID == PLAYER_GUN_UP_RIGHT_ANIMATION || AnimationID == PLAYER_GUN_UP_LEFT_ANIMATION)
		AniHandler->Render(AnimationID, x, y + GunUpHeightAdjust);
	else
		AniHandler->Render(AnimationID, x, y);

	gun->Render();
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
	untouchable = true;
	untouchableStartTime = GetTickCount64();
}