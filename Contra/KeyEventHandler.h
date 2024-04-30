#pragma once
#include <Windows.h>

class KeyEventHandler
{
public:
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};
typedef KeyEventHandler* LPKEYEVENTHANDLER;
