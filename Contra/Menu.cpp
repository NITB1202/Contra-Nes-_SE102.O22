#include <dinput.h>
#include "Menu.h"
#include "ObjectConfig.h"

void Menu::Update(DWORD dt)
{
	//selectArrowY = (select - 1) * OPTION_HEIGHT;
}

void Menu::Render()
{
	animationHandler->DrawAsset(GAMEOVER_BACKGROUND, 0, 0);
	//animationHandler->DrawAsset(selectArrowX, selectArrowY);
}

void Menu::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_UP)
		select--;

	if (keyCode == DIK_DOWN)
		select++;

	if (select < 1)
		select = option;

	if (select > option)
		select = 1;
}