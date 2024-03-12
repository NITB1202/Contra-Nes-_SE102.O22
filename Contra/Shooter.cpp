#include "Shooter.h"

// set movement x y foreach Shooter state
void Shooter::SetState(int ID)
{
	state = ID;

	switch (ID)
	{
	case SHOOTER_RUN_RIGHT:
		vx = SHOOTER_START_VX;
		vy = 0;
		face = 1;
		break;
	case SHOOTER_RUN_LEFT:
		vx = -SHOOTER_START_VX;
		vy = 0;
		face = -1;
		break;
	case SHOOTER_RUN_DEAD:
		vy = 0;
		vx = 0;
		face = -1;
		break;
	}
}

void Shooter::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();

	if (x <= SHOOTER_SPRITE_WIDTH || x >= BackBufferWidth - SHOOTER_SPRITE_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - SHOOTER_SPRITE_WIDTH)
		{
			x = (float)(BackBufferWidth - SHOOTER_SPRITE_WIDTH);
		}
	}
}

void Shooter::Render()
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
		case SHOOTER_RUN_RIGHT:
			AnimationID = SHOOTER_RUN_RIGHT_ANIMATION;
			break;
		case SHOOTER_RUN_LEFT:
			AnimationID = SHOOTER_RUN_LEFT_ANIMATION;
			break;
	}

	AniHandler.Render(AnimationID, x, y);
}