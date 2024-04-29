#pragma once
#include "GameObject.h"

class Ground : public GameObject
{
public:
	Ground()
	{
		baseType = GROUND;
	}

	bool IsBlocking();
};