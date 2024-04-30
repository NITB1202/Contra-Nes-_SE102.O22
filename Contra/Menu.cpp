#include <dinput.h>
#include "Menu.h"
#include "Game.h"
#include "ObjectConfig.h"

void Menu::Update(DWORD dt)
{
	selectArrowY = menuY + (select - 1) * optionHeight;
}

void Menu::Render()
{
	animationHandler->DrawAsset(backGroundID, 0, 0);
	animationHandler->DrawAsset(CURSOR,selectArrowX, selectArrowY);
}

void Menu::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_A)
	{
		HandlerOption();
		return;
	}

	if (keyCode == DIK_UP)
		select--;

	if (keyCode == DIK_DOWN)
		select++;

	if (select < 1)
		select = option;

	if (select > option)
		select = 1;
}

void Menu::HandlerOption()
{
	Game* game = Game::GetInstance();
	Player* player = Player::GetInstance();

	switch (backGroundID)
	{
	case GAMEOVER_BACKGROUND:
	{
		switch (select)
		{
		case 1:
		{
			game->showMenu = false;
			game->ClearBackGround();
			player->Reset();
			break;
		}
		case 2:
			break;
		}
		break;
	}
	case INTRO_BACKGROUND:
	{
		switch (select)
		{
		case 1:
			break;
		}
		break;
	}
	}
}