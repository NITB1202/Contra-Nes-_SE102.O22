#include "Player.h"
#include "Camera.h"
#include "Game.h"
#include "ObjectConfig.h"

Player* Player::instance = NULL;

void Player::SetCurrentState(PlayerState* newState)
{
	delete currentState;
	currentState = newState;
	AniHandler.Reset();
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

	vector<LPGAMEOBJECT> colliableObject = Game::GetInstance()->GetCurrentScene()->GetCollidableObject(this);
	Collision::GetInstance()->Process(this, dt, colliableObject);

	if (!isOnGround && vy < 0 && currentState != dynamic_cast<PlayerFallState*>(currentState))
		SetCurrentState(new PlayerFallState(currentState->GetDirection()));
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