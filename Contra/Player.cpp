#include "Player.h"

void Player::SetState(int ID)
{
	if (ID == PLAYER_NOT_CHANGE_STATE)
	{
		vx = 0;
		return;
	}

	AnimationID = ID;

	switch (ID)
	{
	case PLAYER_RUN_RIGHT_ANIMATION:
		vx = PLAYER_START_VX;
		break;
	case PLAYER_RUN_LEFT_ANIMATION:
		vx = -PLAYER_START_VX;
		break;
	case PLAYER_TOP_RIGHT:
		vx = PLAYER_START_VX;
		break;
	}
}

void Player::Update(DWORD dt)
{
	x += vx * dt;
	//y += vy * dt;

	//basic collision
	if (x < PLAYER_SPRITE_WIDTH)
		x = PLAYER_SPRITE_WIDTH;
	int maxRightside = Game::GetInstance()->GetBackBufferWidth() - PLAYER_SPRITE_WIDTH;
	if (x > maxRightside)
		x = maxRightside;
}

void Player::Render()
{
	if (vx == 0)
		AniHandler.setIDLE(AnimationID, x, y);
	else
		AniHandler.Render(AnimationID, x, y);
}

void Player::Press(int key)
{
	switch (key)
	{
	case 1:
		upPressed = true;
		break;
	case 2:
		rightPressed = true;
		break;
	case 3:
		downPressed = true;
		break;
	case 4:
		leftPressed = true;
	}
}
void Player::Release(int key)
{
	switch (key)
	{
	case 1:
		upPressed = false;
		break;
	case 2:
		rightPressed = false;
		break;
	case 3:
		downPressed = false;
		break;
	case 4:
		leftPressed = false;
	}
}

bool Player::IsPressed(int key)
{
	switch (key)
	{
	case 1:
		return upPressed;
	case 2:
		return rightPressed;
	case 3:
		return downPressed;
	case 4:
		return leftPressed;
	}
}