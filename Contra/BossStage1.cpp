#include "BossStage1.h"

// set movement x y foreach Shooter state
void BossStage1::SetState(int ID)
{
	state = ID;

	switch (ID)
	{
	
	}
}

void BossStage1::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = Game::GetInstance()->GetBackBufferWidth();

	if (x <= BOSSSTAGE1_SPRITE_WIDTH || x >= BackBufferWidth - BOSSSTAGE1_SPRITE_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - BOSSSTAGE1_SPRITE_WIDTH)
		{
			x = (float)(BackBufferWidth - BOSSSTAGE1_SPRITE_WIDTH);
		}
	}
}

void BossStage1::Render()
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

	}

	AniHandler.Render(AnimationID, x, y);
}