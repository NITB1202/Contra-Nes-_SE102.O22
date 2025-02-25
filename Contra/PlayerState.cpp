#include "PlayerState.h"
#include "Player.h"
#include "Game.h"
#include "ObjectConfig.h"
#include <dinput.h>


void ChangeToFallingState(int direction)
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(new PlayerFallState(direction));
	player->SetPosition(player->GetX(), player->GetY() - (PLAYER_HEIGHT - PLAYER_JUMP_HEIGHT));
	player->SetWidthHeight(PLAYER_JUMP_WIDTH, PLAYER_JUMP_HEIGHT);
}

//Player standing func
PlayerState* PlayerStandingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_A:
		return new PlayerJumpingState(this->direction, Player::GetInstance()->GetY());
	case DIK_UP:
		return new PlayerGunOverHeadState(this->direction);
	case DIK_DOWN:
		return new PlayerLayingState(this->direction);
	case DIK_LEFT:
		return new PlayerRunningState(LEFT);
	case DIK_RIGHT:
		return new PlayerRunningState(RIGHT);
	}

	return NULL;
}

PlayerState* PlayerStandingState::OnKeyUp(int keyCode)
{
	return NULL;
}

int PlayerStandingState::GetStateAnimation()
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		if (player->IsShooting())
		{
			if (player->IsUnderWater())
				return PLAYER_SHOOT_RIGHT_IN_WATER_ANIMATION;
			else
				return PLAYER_STAND_RIGHT_SHOOT_ANIMATION;
		}

		if (player->IsUnderWater())
			return PLAYER_STAND_RIGHT_IN_WATER_ANIMATION;
	
		return PLAYER_IDLE_RIGHT_ANIMATION;
	}
	else
	{
		if (player->IsShooting())
		{
			if (player->IsUnderWater())
				return PLAYER_SHOOT_LEFT_IN_WATER_ANIMATION;
			else
				return PLAYER_STAND_LEFT_SHOOT_ANIMATION;
		}

		if (player->IsUnderWater())
			return PLAYER_STAND_LEFT_IN_WATER_ANIMATION;

		return PLAYER_IDLE_LEFT_ANIMATION;
	}
}

void PlayerStandingState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	if (player->IsUnderWater())
		player->SetWidthHeight(PLAYER_WIDTH, PLAYER_HEIGHT / 2);
	else
		player->SetWidthHeight(PLAYER_WIDTH, PLAYER_HEIGHT);
	player->SetSpeed(0, 0);

	if (!player->IsOnGround())
		ChangeToFallingState(direction);
}

bool PlayerStandingState::GetGunDirection(float& x, float& y, int& gunDir)
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		x = player->GetX() + player->GetWidth();
		gunDir = SHOOT_RIGHT;
	}
	else
	{
		x = player->GetX()-8;
		gunDir = SHOOT_LEFT;
	}

	if(player->IsUnderWater())
		y = player->GetY()-12;
	else
		y = player->GetY() - 4;

	return true;
}

//Player running func
PlayerState* PlayerRunningState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_A:
		return new PlayerJumpingState(this->direction, Player::GetInstance()->GetY());
	case DIK_LEFT:
		direction = LEFT;
		break;
	case DIK_RIGHT:
		direction = RIGHT;
		break;
	case DIK_UP:
		return new PlayerPointGunUpState(this->direction);
	case DIK_DOWN:
		return new PlayerPointGunDownState(this->direction);
	}

	return NULL;
}

PlayerState* PlayerRunningState::OnKeyUp(int keyCode)
{
	return new PlayerStandingState(this->direction);
}

int PlayerRunningState::GetStateAnimation()
{	
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		if (player->IsShooting())
		{
			if (player->IsUnderWater())
				return PLAYER_SHOOT_RIGHT_IN_WATER_ANIMATION;
			else
				return PLAYER_SHOOT_RUN_RIGHT_ANIMATION;
		}

		if (player->IsUnderWater())
			return PLAYER_RUN_RIGHT_IN_WATER_ANIMTION;

		return PLAYER_RUN_RIGHT_ANIMATION;
	}
	else
	{
		if (player->IsShooting())
		{
			if (player->IsUnderWater())
				return PLAYER_SHOOT_LEFT_IN_WATER_ANIMATION;
			else
				return PLAYER_SHOOT_RUN_LEFT_ANIMATION;
		}
		
		if (player->IsUnderWater())
			return PLAYER_RUN_LEFT_IN_WATER_ANIMTION;

		return PLAYER_RUN_LEFT_ANIMATION;
	}
}

void PlayerRunningState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	if (player->IsUnderWater())
		player->SetWidthHeight(PLAYER_WIDTH, PLAYER_HEIGHT / 2);
	else
		player->SetWidthHeight(PLAYER_WIDTH, PLAYER_HEIGHT);
	if(direction == RIGHT)
		player->SetSpeed(PLAYER_START_VX, 0);
	else
		player->SetSpeed(-PLAYER_START_VX, 0);

	if (!player->IsOnGround())
		ChangeToFallingState(direction);
}

bool PlayerRunningState::GetGunDirection(float& x, float& y, int& gunDir)
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		x = player->GetX() + player->GetWidth();
		gunDir = SHOOT_RIGHT;
	}
	else
	{
		x = player->GetX() - 8;
		gunDir = SHOOT_LEFT;
	}

	if (player->IsUnderWater())
		y = player->GetY() - 12;
	else
		y = player->GetY() - 4;

	return true;
}

//Player jumping func

int PlayerJumpingState::GetStateAnimation()
{
	if(direction == RIGHT)
		return PLAYER_JUMP_UP_RIGHT_ANIMATION;

	return PLAYER_JUMP_UP_LEFT_ANIMATION;
}

void PlayerJumpingState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	player->SetWidthHeight(PLAYER_JUMP_WIDTH, PLAYER_JUMP_HEIGHT);
	player->SetSpeed(player->GetVx(), PLAYER_START_VY);

	if (player->GetY() > maxJumpHeight)
		player->SetCurrentState(new PlayerFallState(this->direction));
}

//Player fall func

int PlayerFallState::GetStateAnimation()
{
	if (direction == RIGHT)
		return PLAYER_JUMP_UP_RIGHT_ANIMATION;

	return PLAYER_JUMP_UP_LEFT_ANIMATION;
}

void PlayerFallState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	player->SetWidthHeight(PLAYER_JUMP_WIDTH, PLAYER_JUMP_HEIGHT);
	player->SetSpeed(player->GetVx(), -PLAYER_START_VY);

	if (player->IsOnGround())
		player->SetCurrentState(ChangeStateAfterLanding());

}

PlayerState* PlayerFallState::ChangeStateAfterLanding()
{
	Game* game = Game::GetInstance();
	Player* player = Player::GetInstance();

	if (player->IsUnderWater())
	{
		player->SetPosition(player->GetX(), player->GetY() + (PLAYER_HEIGHT/2 - PLAYER_JUMP_HEIGHT));
		player->SetWidthHeight(PLAYER_WIDTH, PLAYER_HEIGHT/2);

	}
	else
	{
		player->SetPosition(player->GetX(), player->GetY() + (PLAYER_HEIGHT - PLAYER_JUMP_HEIGHT));
		player->SetWidthHeight(PLAYER_WIDTH, PLAYER_HEIGHT);
	}

	if (game->IsKeyDown(DIK_LEFT))
		return new PlayerRunningState(LEFT);

	if (game->IsKeyDown(DIK_RIGHT))
		return new PlayerRunningState(RIGHT	);

	return new PlayerStandingState(this->direction);
}


//Player laying func
PlayerState* PlayerLayingState::OnKeyDown(int keyCode)
{
	return NULL;
}

PlayerState* PlayerLayingState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_DOWN)
	{
		Player* player = Player::GetInstance();
		if (player->IsUnderWater())
			player->SetPosition(player->GetX(), player->GetY() + (PLAYER_HEIGHT/2 - PLAYER_LAY_DOWN_HEIGHT/2));
		else
			player->SetPosition(player->GetX(), player->GetY() + (PLAYER_HEIGHT - PLAYER_LAY_DOWN_HEIGHT));
		return new PlayerStandingState(this->direction);
	}

	return NULL;
}

int PlayerLayingState::GetStateAnimation()
{
	Player* player = Player::GetInstance();

	if (player->IsUnderWater())
		return PLAYER_LAY_DOWN_IN_WATER_ANIMATION;

	if (direction == RIGHT)
	{
		if (player->IsShooting())
			return PLAYER_LAY_DOWN_RIGHT_SHOOT_ANIMATION;
		return PLAYER_LAY_DOWN_RIGHT_ANIMATION;
	}
	else
	{
		if (player->IsShooting())
			return PLAYER_LAY_DOWN_LEFT_SHOOT_ANIMATION;
		return PLAYER_LAY_DOWN_LEFT_ANIMATION;
	}
}

void PlayerLayingState::UpdateStatus()
{
	Player* player = Player::GetInstance();
	if (player->IsUnderWater())
	{
		player->SetPosition(player->GetX(), player->GetY() - (player->GetHeight() - PLAYER_LAY_DOWN_HEIGHT/2));
		player->SetWidthHeight(PLAYER_LAY_DOWN_WIDTH, PLAYER_LAY_DOWN_HEIGHT/2);
	}
	else
	{
		player->SetPosition(player->GetX(), player->GetY() - (player->GetHeight() - PLAYER_LAY_DOWN_HEIGHT));
		player->SetWidthHeight(PLAYER_LAY_DOWN_WIDTH, PLAYER_LAY_DOWN_HEIGHT);
	}
	player->SetSpeed(0, 0);
}

bool PlayerLayingState::GetGunDirection(float& x, float& y, int& gunDir)
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		x = player->GetX() + player->GetWidth()+8;
		gunDir = SHOOT_RIGHT;
	}
	else
	{
		x = player->GetX()-16;
		gunDir = SHOOT_LEFT;
	}

	y = player->GetY() - player->GetHeight() + 30;

	return true;
}

//Player gun over head func
PlayerState* PlayerGunOverHeadState::OnKeyDown(int keyCode)
{
	return NULL;
}

PlayerState* PlayerGunOverHeadState::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_UP)
		return new PlayerStandingState(this->direction);

	return NULL;
}

int PlayerGunOverHeadState::GetStateAnimation()
{
	Player* player = Player::GetInstance();
	if (direction == RIGHT)
	{
		if (player->IsUnderWater())
		{
			if (player->IsShooting())
				return PLAYER_GUN_UP_SHOOT_RIGHT_IN_WATER_ANIMATION;

			return PLAYER_GUN_UP_RIGHT_IN_WATER_ANIMATION;
		}

		if (player->IsShooting())
			return PLAYER_GUN_UP_RIGHT_SHOOT_ANIMATION;

		return PLAYER_GUN_UP_RIGHT_ANIMATION;
	}
	else
	{
		if (player->IsUnderWater())
		{
			if (player->IsShooting())
				return PLAYER_GUN_UP_SHOOT_LEFT_IN_WATER_ANIMATION;

			return PLAYER_GUN_UP_LEFT_IN_WATER_ANIMATION;
		}

		if (player->IsShooting())
			return PLAYER_GUN_UP_LEFT_SHOOT_ANIMATION;

		return PLAYER_GUN_UP_LEFT_ANIMATION;
	}
}

void PlayerGunOverHeadState::UpdateStatus()
{
	Player* player = Player::GetInstance();
	player->SetSpeed(0, 0);
}

bool PlayerGunOverHeadState::GetGunDirection(float& x, float& y, int& gunDir)
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
		x = player->GetX() + player->GetWidth()/2 - 4;
	else
		x = player->GetX() + 12;

	y = player->GetY() + 30;

	gunDir = SHOOT_TOP;

	return true;
}

//Player point gun up func
PlayerState* PlayerPointGunUpState::OnKeyDown(int keyCode)
{
	return NULL;
}

PlayerState* PlayerPointGunUpState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		return new PlayerRunningState(this->direction);
	case DIK_LEFT:
		return new PlayerStandingState(LEFT);
	case DIK_RIGHT:
		return new PlayerStandingState(RIGHT);
	}

	return NULL;
}

int PlayerPointGunUpState::GetStateAnimation()
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		if (player->IsUnderWater())
			return PLAYER_TOP_RIGHT_IN_WATER_ANIMATION;
		else
			return PLAYER_GUN_TOP_RIGHT_ANIMATION;
	}

	if (player->IsUnderWater())
		return PLAYER_TOP_LEFT_IN_WATER_ANIMATION;

	return PLAYER_GUN_TOP_LEFT_ANIMATION;
}

void PlayerPointGunUpState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
		player->SetSpeed(PLAYER_START_VX, 0);

	if (direction == LEFT)
		player->SetSpeed(-PLAYER_START_VX, 0);

	if (!player->IsOnGround())
		ChangeToFallingState(direction);
}

bool PlayerPointGunUpState::GetGunDirection(float& x, float& y, int& gunDir)
{
	Player* player = Player::GetInstance();
		
	if (direction == RIGHT)
	{
		if (player->IsUnderWater())
			x = player->GetX() + player->GetWidth() - 8;
		else
			x = player->GetX() + player->GetWidth() - 12;
		gunDir = SHOOT_TOPRIGHT;
	}
	else
	{

		if (player->IsUnderWater())
			x = player->GetX() - 6;
		else
			x = player->GetX();
		gunDir = SHOOT_TOPLEFT;
	}

	y = player->GetY() + 12;

	return true;
}

//Player point gun down func
PlayerState* PlayerPointGunDownState::OnKeyDown(int keyCode)
{
	return NULL;
}

PlayerState* PlayerPointGunDownState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_DOWN:
		return new PlayerRunningState(this->direction);
	case DIK_LEFT:
		return new PlayerStandingState(LEFT);
	case DIK_RIGHT:
		return new PlayerStandingState(RIGHT);
	}
	return NULL;
}

int PlayerPointGunDownState::GetStateAnimation()
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		if (player->IsUnderWater())
			return PLAYER_RUN_RIGHT_IN_WATER_ANIMTION;

		return PLAYER_GUN_DOWN_RIGHT_ANIMATION;
	}

	if (player->IsUnderWater())
		return PLAYER_RUN_LEFT_IN_WATER_ANIMTION;

	return PLAYER_GUN_DOWN_LEFT_ANIMATION;
}

void PlayerPointGunDownState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
		player->SetSpeed(PLAYER_START_VX, 0);

	if (direction == LEFT)
		player->SetSpeed(-PLAYER_START_VX, 0);

	if (!player->IsOnGround())
		ChangeToFallingState(direction);
}

bool PlayerPointGunDownState::GetGunDirection(float& x, float& y, int& gunDir)
{
	Player* player = Player::GetInstance();

	if (direction == RIGHT)
	{
		x = player->GetX() + player->GetWidth() - 4;
		gunDir = SHOOT_DOWNRIGHT;
	}
	else
	{
		x = player->GetX();
		gunDir = SHOOT_DOWNLEFT;
	}

	y = player->GetY() - player->GetHeight()/2 + 8;

	return true;
}

//Player die func
int PlayerDieState::GetStateAnimation()
{
	Player* player = Player::GetInstance();

	if (GetTickCount64() - startTime < DIE_ANIMATION_DURATION)
	{
		if (direction == RIGHT)
			return PLAYER_DIE_RIGHT_ANIMATION;
		else
			return PLAYER_DIE_LEFT_ANIMATION;
	}
	else
	{

		if (direction == RIGHT)
			return PLAYER_LAY_DIE_RIGHT_ANIMATION;
		else
			return PLAYER_LAY_DIE_LEFT_ANIMATION;
	}
}

void PlayerDieState::UpdateStatus()
{
	Player* player = Player::GetInstance();

	player->SetWidthHeight(PLAYER_DIE_WIDTH, PLAYER_DIE_HEIGHT);
	
	if (GetTickCount64() - startTime < DIE_ANIMATION_DURATION)
	{
		if (direction == RIGHT)
			player->SetSpeed(-DIE_ANIMATION_DEFLECT_SPEED_X, DIE_ANIMATION_DEFLECT_SPEED_Y);
		else
			player->SetSpeed(DIE_ANIMATION_DEFLECT_SPEED_X, DIE_ANIMATION_DEFLECT_SPEED_Y);
	}
	else
	{
		if(player->IsOnGround())
			player->SetSpeed(0,0);

		if (GetTickCount64() - startTime > DIE_ANIMATION_DURATION + RESET_TIME)
		{
			player->UntouchableStart();
			if(!player->IsUnderWater())
				player->SetPosition(player->GetX(), player->GetY() + (PLAYER_HEIGHT + 4-PLAYER_DIE_HEIGHT));
			else
				player->SetPosition(player->GetX(), player->GetY() + (PLAYER_DIE_HEIGHT-PLAYER_HEIGHT/2 + 4));
			player->SetCurrentState(new PlayerStandingState(direction));
		}
	}
}
bool PlayerLayingState::CanShoot()
{
	return !Player::GetInstance()->IsUnderWater();
}

bool PlayerPointGunDownState::CanShoot()
{
	return !Player::GetInstance()->IsUnderWater();
}