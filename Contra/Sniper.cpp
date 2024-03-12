#include "Sniper.h"

// set movement x y foreach Shooter state
void Sniper::SetState(int ID)
{
	state = ID;

	switch (ID)
	{
	case SNIPER_RUN_RIGHT:
		vx = SNIPER_START_VX;
		vy = 0;
		face = 1;
		break;
	case SNIPER_RUN_LEFT:
		vx = -SNIPER_START_VX;
		vy = 0;
		face = -1;
		break;
	case SNIPER_RUN_DEAD:
		vy = 0;
		vx = 0;
		face = -1;
		break;
	}
}

void Sniper::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();

	if (x <= SNIPER_SPRITE_WIDTH || x >= BackBufferWidth - SNIPER_SPRITE_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - SNIPER_SPRITE_WIDTH)
		{
			x = (float)(BackBufferWidth - SNIPER_SPRITE_WIDTH);
		}
	}
}

void Sniper::Render()
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
	case SNIPER_RUN_RIGHT:
		AnimationID = SNIPER_RUN_RIGHT_ANIMATION;
		break;
	case SNIPER_RUN_LEFT:
		AnimationID = SNIPER_RUN_LEFT_ANIMATION;
		break;
	}

	AniHandler.Render(AnimationID, x, y);
}