#include "KeyEventHandler.h"
#include "Player.h"
#include "Game.h"

void KeyEventHandler::KeyState(BYTE* state)
{
	Game* game = Game::GetInstance();
	Player* player = Player::GetInstance();

	int left = game->IsKeyDown(DIK_LEFT);
	int right = game->IsKeyDown(DIK_RIGHT);
	int up = game->IsKeyDown(DIK_UP);
	int down = game->IsKeyDown(DIK_DOWN);
	
	if (player->GetState() == PLAYER_JUMP_UP)
		return;

	if (player->IsPressed(DIK_RIGHT))
	{
		player->SetState(PLAYER_RUN_RIGHT);

		if (up)
			player->SetState(PLAYER_TOP_RIGHT);
		
		if (down)
			player->SetState(PLAYER_DOWN_RIGHT);
		
		return;
	}

	if (player->IsPressed(DIK_LEFT))
	{
		player->SetState(PLAYER_RUN_LEFT);

		if (up)
			player->SetState(PLAYER_TOP_LEFT);
		
		if (down)
			player->SetState(PLAYER_DOWN_LEFT);
		
		return;
	}

	if (player->IsPressed(DIK_UP))
	{
		player->SetState(PLAYER_GUN_UP);
		return;
	}

	if (player->IsPressed(DIK_DOWN))
	{
		player->SetState(PLAYER_LAY_DOWN);
		return;
	}

	if (player->GetFace() == 1)
		player->SetState(PLAYER_IDLE_RIGHT);
	else
		player->SetState(PLAYER_IDLE_LEFT);
}

void KeyEventHandler::OnKeyDown(int KeyCode)
{
	Player* player = Player::GetInstance();

	switch (KeyCode)
	{
	case DIK_A:
		if (player->GetState() != PLAYER_JUMP_UP)
		{
			player->ResetAction();	//call this function if animation between 2 actions have different size
			player->SetState(PLAYER_JUMP_UP);
		}
		break;
	case DIK_RIGHT:
		player->Press(DIK_RIGHT);
		break;
	case DIK_LEFT:
		player->Press(DIK_LEFT);
		break;
	case DIK_UP:
		player->Press(DIK_UP);
		break;
	case DIK_DOWN:
		player->Press(DIK_DOWN);
		break;
	}
}
void KeyEventHandler::OnKeyUp(int KeyCode)
{
	Player* player = Player::GetInstance();

	switch (KeyCode)
	{
	case DIK_RIGHT:
		player->Release(DIK_RIGHT);
		break;
	case DIK_LEFT:
		player->Release(DIK_LEFT);
		break;
	case DIK_UP:
		player->Release(DIK_UP);
		break;
	case DIK_DOWN:
		player->Release(DIK_DOWN);
		break;
	}
}