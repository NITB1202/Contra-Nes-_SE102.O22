#pragma once
#include "AnimationHandler.h"
#include "GameObject.h"

class Transition : public GameObject
{
private:
	float xStart, yStart;
	float xEnd, yEnd;
	bool finish;
public:
	Transition(float xStart, float yStart, float xEnd, float yEnd, float vx, float vy, int ID);
	void Begin();
	void Update(DWORD dt);
	void Render();
	bool IsFinish() { return finish; }
};