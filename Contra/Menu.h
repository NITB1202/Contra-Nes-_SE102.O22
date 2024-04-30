#pragma once
#include<Windows.h>
#include "AnimationHandler.h"

class Menu
{
private:
	AnimationHandler* animationHandler;
	float selectArrowX, selectArrowY;
	int option;
	int select;
public:
	Menu(float x, float y, int option)
	{
		select = 1;
		selectArrowX = x;
		selectArrowY = y;
		this->option = option;
		animationHandler = new AnimationHandler();
	}

	void OnKeyDown(int keyCode);

	void Update(DWORD dt);
	void Render();

	~Menu() { delete animationHandler; }
};
typedef Menu* LPMENU;