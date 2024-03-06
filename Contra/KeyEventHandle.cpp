#include "KeyEventHandler.h"
#include "Player.h"

extern Player* player;

void KeyEventHandler::KeyState(BYTE* state)
{
	Game* game = Game::GetInstance();

	int left = game->IsKeyDown(DIK_LEFT);
	int right = game->IsKeyDown(DIK_RIGHT);
	int up = game->IsKeyDown(DIK_UP);
	int down = game->IsKeyDown(DIK_DOWN);
	
	player->SetState(PLAYER_NOT_CHANGE_STATE);

	if (player->IsPressed(2))
	{
		if (up)
			player->SetState(PLAYER_TOP_RIGHT);
		else
			player->SetState(PLAYER_RUN_RIGHT_ANIMATION);
	}
	if (player->IsPressed(4))
		player->SetState(PLAYER_RUN_LEFT_ANIMATION);

}

void KeyEventHandler::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_RIGHT:
		player->Press(2);
		break;
	case DIK_LEFT:
		player->Press(4);
		break;
	}
}
void KeyEventHandler::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_RIGHT:
		player->Release(2);
		break;
	case DIK_LEFT:
		player->Release(4);
		break;
	}
}