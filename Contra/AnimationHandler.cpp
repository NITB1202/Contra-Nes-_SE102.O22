#include "AnimationHandler.h"
#include "AnimationLib.h"
#include "Game.h"

void AnimationHandler::setIDLE(int ID, float x, float y)
{
	if (currentFrame != -1) currentFrame = -1;
	Animation ani = AnimationLib::GetInstance()->GetAnimation(ID);
	lastRendertime = GetTickCount64();
	Game::GetInstance()->Draw(x, y, ani.GetTexture(), ani.GetScaleX(), ani.GetScaleY(),flipHorizontal);
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
	Game::GetInstance()->Draw(x, y, ani.GetTexture(), ani.GetScaleX(), ani.GetScaleY(),flipHorizontal,&rect);
}

void AnimationHandler::FlipSpriteHorizontal(bool flip)
{
	if (flip)
		flipHorizontal = 1;
	else
		flipHorizontal = 0;
}