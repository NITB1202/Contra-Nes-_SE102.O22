#pragma once
#include "GameObject.h"
#include "Runman.h"
#include "Turret.h"

#define RUNMAN_OBJECT 1000
#define TURRET_OBJECT 1001
#define SNIPER_OBJECT 1002
#define TURRET_OBJECT 1003

LPGAMEOBJECT InitObj(int type)
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
	}

	return obj;
}


bool IsMovingObject(int type)
{
	if (type == RUNMAN_OBJECT)
		return true;

	return false;
}