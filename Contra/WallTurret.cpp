#include "WallTurret.h"

// set movement x y foreach Shooter state
void WallTurret::SetState(int ID)
{
	state = ID;

	switch (ID)
	{
	case WALLTURRET_RUN_RIGHT:
		vx = WALLTURRET_START_VX;
		vy = 0;
		face = 1;
		break;
	case WALLTURRET_RUN_LEFT:
		vx = -WALLTURRET_START_VX;
		vy = 0;
		face = -1;
		break;
	case WALLTURRET_RUN_DEAD:
		vy = 0;
		vx = 0;
		face = -1;
		break;
	}
}

void WallTurret::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();

	if (x <= WALLTURRET_SPRITE_WIDTH || x >= BackBufferWidth - WALLTURRET_SPRITE_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - WALLTURRET_SPRITE_WIDTH)
		{
			x = (float)(BackBufferWidth - WALLTURRET_SPRITE_WIDTH);
		}
	}
}

void WallTurret::Render()
{
	if (face == 1)
	{
		AniHandler.FlipSpriteHorizontal(0);
	}
	else
	{
		AniHandler.FlipSpriteHorizontal(1);
	}

	switch (state)
	{
	case WALLTURRET_RUN_RIGHT:
		AnimationID = WALLTURRET_RUN_RIGHT_ANIMATION;
		break;
	case WALLTURRET_RUN_LEFT:
		AnimationID = WALLTURRET_RUN_LEFT_ANIMATION;
		break;
	}

	AniHandler.Render(AnimationID, x, y);
}