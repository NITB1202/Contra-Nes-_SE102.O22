#include "Runman.h"
#include "Game.h"
#include "ObjectConfig.h"

void Runman::Update(DWORD dt)
{
	x += vx * dt;

	Camera* cam = Camera::GetInstance();

	//if (x < cam->getX() || x > cam->getX()+cam->getWidth()-RUNMAN_SPRITE_WIDTH)
		//vx = -vx;
}

void Runman::Render()
{
	if (vx >= 0)
	{
		AniHandler.FlipSpriteHorizontal(0);
		AnimationID = RUNMAN_RUN_RIGHT_ANIMATION;
	}
	else
	{
		AniHandler.FlipSpriteHorizontal(1);
		AnimationID = RUNMAN_RUN_RIGHT_ANIMATION;
	}

	AniHandler.Render(AnimationID, x, y);
}