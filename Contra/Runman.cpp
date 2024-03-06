#include "Runman.h"

void Runman::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();

	if (x <= RUNMAN_SPRITE_WIDTH / 2 || x >= BackBufferWidth - RUNMAN_SPRITE_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - RUNMAN_SPRITE_WIDTH)
		{
			x = (float)(BackBufferWidth - RUNMAN_SPRITE_WIDTH);
		}
	}
}

void Runman::Render()
{
	if (vx >= 0)
		AnimationID = RUNMAN_RUN_RIGHT_ANIMATION;
	else
		AnimationID = RUNMAN_RUN_LEFT_ANIMATION;

	AniHandler.Render(AnimationID, x, y);
}