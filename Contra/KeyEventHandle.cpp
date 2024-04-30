#include "KeyEventHandler.h"
#include "Player.h"
#include "Game.h"

void KeyEventHandler::OnKeyDown(int KeyCode)
{
	Game* game = Game::GetInstance();

	if (!game->showMenu)
		Player::GetInstance()->OnKeyDown(KeyCode);
	else
		game->GetCurrentMenu()->OnKeyDown(KeyCode);
}
void KeyEventHandler::OnKeyUp(int KeyCode)
{
	Player::GetInstance()->OnKeyUp(KeyCode);
}