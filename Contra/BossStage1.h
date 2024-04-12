#pragma once
#pragma once
#pragma once
#include "GameObject.h"

#define TEXTURE_PATH_BOSSSTAGE1_RUN_RIGHT	L"image\\Enemy\\EndBoss.png"

// define all information of BOSSSTAGE1 sprites
#define BOSSSTAGE1_SPRITE_WIDTH			112
#define BOSSSTAGE1_SPRITE_HEIGHT		216
#define BOSSSTAGE1_DEAD_ANIMATION		7001


class BossStage1 : public GameObject
{
private:
	int face = 1;

public:
	BossStage1(float x, float y, float vx = 0, float vy = 0) :GameObject(x, y, vx, vy) {};
	void SetState(int ID);
	void Render();
	void Update(DWORD dt);
	int GetFace() { return face; }
};