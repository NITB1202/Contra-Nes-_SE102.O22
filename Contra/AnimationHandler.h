#pragma once
#include "Animation.h"

class AnimationHandler
{
	int currentFrame = -1;
	ULONGLONG lastRendertime = 0;
	int period = 100;

public:
	void SetPeriod(int p) { period = p; }
	void setIDLE(int ID, float x, float y);
	void Render(int ID, float x, float y);

};