#pragma once
#include "GameObject.h"
#include "Runman.h"

#define RUNMAN_OBJECT 1000
#define TURRET_OBJECT 1001
#define SNIPER_OBJECT 1002

LPGAMEOBJECT InitObj(int type)
{
	LPGAMEOBJECT obj = NULL;

	switch (type)
	{
	case RUNMAN_OBJECT:
		obj = new Runman();
		break;
	
	}

	return obj;
}
