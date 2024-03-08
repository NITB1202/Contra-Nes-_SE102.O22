#pragma once
#include "Animation.h"

class AnimationHandler
{
	int flipHorizontal = 0;
	int currentFrame = -1;
	ULONGLONG lastRendertime = 0;
	int period = 100;

public:
	void SetPeriod(int p) { period = p; }
	void FlipSpriteHorizontal(bool flip);
	void setIDLE(int ID, float x, float y);
	void Render(int ID, float x, float y);
	void SetCurrentFrame(int frame) { currentFrame = frame; }
};