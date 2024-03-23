#include "KeyEventHandler.h"
#include "Player.h"
#include "Game.h"

void KeyEventHandler::KeyState(BYTE* state)
{

}

void KeyEventHandler::OnKeyDown(int KeyCode)
{
	Player* player = Player::GetInstance();
	player->OnKeyDown(KeyCode);
}
void KeyEventHandler::OnKeyUp(int KeyCode)
{
	Player* player = Player::GetInstance();
	player->OnKeyUp(KeyCode);
}