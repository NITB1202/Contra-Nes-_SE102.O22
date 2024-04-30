#pragma once
#include <Windows.h>

class KeyEventHandler
{
public:
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef KeyEventHandler* LPKEYEVENTHANDLER;

class PlaySceneKeyEventHandler:public KeyEventHandler
{
public:
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};

class MenuSceneKeyEventHandler :public KeyEventHandler
{
public:
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};