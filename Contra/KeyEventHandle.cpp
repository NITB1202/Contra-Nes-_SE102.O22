#include "KeyEventHandler.h"
#include "Player.h"
#include "Game.h"

void PlaySceneKeyEventHandler::OnKeyDown(int KeyCode)
{
	Player* player = Player::GetInstance();
	player->OnKeyDown(KeyCode);
}
void PlaySceneKeyEventHandler::OnKeyUp(int KeyCode)
{
	Player* player = Player::GetInstance();
	player->OnKeyUp(KeyCode);
}

void MenuSceneKeyEventHandler::OnKeyUp(int keyCode)
{

}

void MenuSceneKeyEventHandler::OnKeyDown(int keyCode)
{

}