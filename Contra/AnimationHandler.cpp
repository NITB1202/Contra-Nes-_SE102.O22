#include "AnimationHandler.h"
#include "AnimationLib.h"

void AnimationHandler::setIDLE(int ID, float x, float y)
{
	Animation ani = AnimationLib::GetInstance()->GetAnimation(ID);
	RECT rect = ani.GetSprite(0);
	lastRendertime = GetTickCount64();
	Game::GetInstance()->Draw(x, y, ani.GetTexture(), &rect, ani.GetScaleX(), ani.GetScaleY());
}

void AnimationHandler::Render(int ID, float x, float y)
{
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
	Game::GetInstance()->Draw(x, y, ani.GetTexture(), &rect, ani.GetScaleX(), ani.GetScaleY());
}