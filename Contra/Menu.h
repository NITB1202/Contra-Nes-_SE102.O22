#pragma once
#include<Windows.h>
#include "AnimationHandler.h"

class Menu
{
private:

	AnimationHandler* animationHandler;
	float menuX, menuY;
	float selectArrowX, selectArrowY;
	int optionHeight;
	int option;
	int select;
	int backGroundID;

public:
	Menu(float x, float y, int option, int optionHeight, int backGroundID )
	{
		select = 1;
		menuX = x;
		menuY = y;
		selectArrowX = x;
		selectArrowY = y;
		this->option = option;
		this->optionHeight = optionHeight;
		this->backGroundID = backGroundID;
		animationHandler = new AnimationHandler();
	}

	void OnKeyDown(int keyCode);
	void Update(DWORD dt);
	void Render();
	void HandlerOption();
	void Reset() { select = 1; }

	~Menu() { delete animationHandler; }
};
typedef Menu* LPMENU;