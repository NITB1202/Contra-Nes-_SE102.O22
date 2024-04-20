#pragma once
#include "GameObject.h"
#include "Runman.h"
#include "Turret.h"
#include "Ground.h"

#define RUNMAN_OBJECT 1000
#define TURRET_OBJECT 1001
#define SNIPER_OBJECT 1002
#define TURRET_OBJECT 1003
#define GROUND_OBJECT 0
#define WATER_OBJECT 1

class MyUtility
{

public:

	static LPGAMEOBJECT InitObj(int type)
	{
		LPGAMEOBJECT obj = NULL;

		switch (type)
		{
		case RUNMAN_OBJECT:
			obj = new Runman();
			break;
		case TURRET_OBJECT:
			obj = new Turret();
			break;
		default:
			obj = new Ground();
		}

		return obj;
	}


	static int CalculateArea(RECT rect)
	{
		int width = rect.right - rect.left;
		int height = rect.top - rect.bottom;
		return width * height;
	}

	static bool IsMovingObject(int type)
	{
		if (type == RUNMAN_OBJECT)
			return true;

		return false;
	}

	static bool IsInterger(double num) {
		return num - static_cast<int>(num) == 0;
	}

	static bool CheckIntersect(RECT rect1, RECT rect2)
	{
		bool overlapX = (rect1.left <= rect2.right) && (rect1.right >= rect2.left);
		bool overlapY = (rect1.top >= rect2.bottom) && (rect1.bottom <= rect2.top);

		return overlapX && overlapY;
	}

};