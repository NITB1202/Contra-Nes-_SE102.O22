#pragma once
#include "Animation.h"

class AnimationHandler
{
	int preID = -1;
	int currentFrame = -1;
	ULONGLONG lastRendertime = 0;
	int period = 100;

public:
	void SetPeriod(int p) { period = p; }
	void Render(int ID, float x, float y);
	void DrawAsset(int ID, float x, float y);
};