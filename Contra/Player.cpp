#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "ObjectConfig.h"

Player* Player::instance = NULL;

void Player::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	groundLevel = y;
}

void Player::SetCurrentState(PlayerState* newState)
{
	delete currentState;
	currentState = newState;
	AniHandler.Reset();
}

void Player::Update(DWORD dt)
{
	currentState->UpdateStatus();

	x += vx * dt; // chuyen dong thang deu khong gia toc
	y += vy * dt - 1/2*PLAYER_GRAVITY*dt*dt;
	

	//basic collision
	float camx = Camera::GetInstance()->getX();
	if (x < camx)
		x = camx;
}

void Player::Render()
{
	AnimationID = currentState->GetStateAnimation();

	if (AnimationID == PLAYER_GUN_UP_RIGHT_ANIMATION || AnimationID == PLAYER_GUN_UP_LEFT_ANIMATION)
		AniHandler.Render(AnimationID, x, y + GunUpHeightAdjust);
	else
		AniHandler.Render(AnimationID, x, y);
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
}

void Player::OnKeyUp(int keyCode)
{
	PlayerState* newState = currentState->OnKeyUp(keyCode);
	if (newState != NULL)
		SetCurrentState(newState);
}