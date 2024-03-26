#include "Gulcan.h"

// set movement x y foreach Shooter state
void Gulcan::SetState(int ID)
{
	state = ID;

	switch (ID)
	{
	case GULCAN_RUN_RIGHT:
		vx = GULCAN_START_VX;
		vy = 0;
		face = 1;
		break;
	case GULCAN_RUN_LEFT:
		vx = -GULCAN_START_VX;
		vy = 0;
		face = -1;
		break;
	case GULCAN_RUN_DEAD:
		vy = 0;
		vx = 0;
		face = -1;
		break;
	}
}

void Gulcan::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();

	if (x <= GULCAN_SPRITE_WIDTH || x >= BackBufferWidth - GULCAN_SPRITE_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - GULCAN_SPRITE_WIDTH)
		{
			x = (float)(BackBufferWidth - GULCAN_SPRITE_WIDTH);
		}
	}
}

void Gulcan::Render()
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
	case GULCAN_RUN_RIGHT:
		AnimationID = GULCAN_RUN_RIGHT_ANIMATION;
		break;
	case GULCAN_RUN_LEFT:
		AnimationID = GULCAN_RUN_LEFT_ANIMATION;
		break;
	}

	AniHandler.Render(AnimationID, x, y);
}