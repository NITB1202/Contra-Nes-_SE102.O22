#pragma once
#include<Windows.h>
#include "AnimationHandler.h"
#include "Transition.h"

class Menu
{
private:

	AnimationHandler* animationHandler;
	float menuX, menuY;

	float selectArrowX, selectArrowY;
	int optionHeight;
	int option;
	int select;

	int backgroundID;
	int backgroundSound;

	Transition* trans;
	int transType;

public:
	Menu(float x, float y, int option, int optionHeight, int backGroundID, int backgroundSound, int transType = 1)
	{
		select = 1;
		menuX = x;
		menuY = y;
		selectArrowX = x;
		selectArrowY = y;
		this->option = option;
		this->optionHeight = optionHeight;
		this->backgroundID = backGroundID;
		this->backgroundSound = backgroundSound;
		animationHandler = new AnimationHandler();
		trans = NULL;
		this->transType = transType;
	}
	void BeginTransition();
	void OnKeyDown(int keyCode);
	void Update(DWORD dt);
	void Render();
	void HandlerOption();
	void Reset() { select = 1; }

	~Menu() { delete animationHandler; }
};
typedef Menu* LPMENU;