#pragma once
#include "GameObject.h"

class AutoDestroyBridge : public GameObject
{
private:
	bool explode = false;
	int destroyState = 0;
	DWORD explodeStart = -1;
	AnimationHandler* effectHandler;
public:
	AutoDestroyBridge()
	{
		baseType = OTHER;
		effectHandler = new AnimationHandler();
	}
	RECT GetCollisionBound();
	int GetDestroyDistance();
	void Update(DWORD dt);
	void Render();
};

