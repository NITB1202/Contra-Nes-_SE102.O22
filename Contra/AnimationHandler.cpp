#include "AnimationHandler.h"
#include "AnimationLib.h"
#include "Game.h"

void AnimationHandler::Render(int ID, float x, float y)
{
	if (preID != ID)
		currentFrame = -1;

	preID = ID;

	Animation ani = AnimationLib::GetInstance()->GetAnimation(ID);

	ULONGLONG now = GetTickCount64();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastRendertime = now;
	}
	else
	{ 
		if (now - lastRendertime > period)
		{
			currentFrame++;
			lastRendertime = now;
			if (currentFrame == ani.GetSize()) currentFrame = 0;
		}

	}

	RECT rect = ani.GetSprite(currentFrame);
	Game::GetInstance()->Draw(x, y, ani.GetTexture(), ani.GetScaleX(), ani.GetScaleY(),ani.IsFlipped(), &rect);
}

void AnimationHandler::DrawAsset(int ID, float x, float y)
{
	Animation ani = AnimationLib::GetInstance()->GetAnimation(ID);
	RECT rect = ani.GetSprite(0);
	Game::GetInstance()->DrawInScreenCoord(x, y, ani.GetTexture(), ani.GetScaleX(), ani.GetScaleY(), ani.IsFlipped(), &rect);
}
