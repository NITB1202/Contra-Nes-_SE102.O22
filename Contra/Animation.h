#pragma once
#include "Texture.h"

class Animation
{
	LPTEXTURE texture;

	int spriteWidth;
	int spriteHeight;

	float scaleX;
	float scaleY;

	int size;
	bool flipped;

public:

	Animation(LPTEXTURE tex = NULL, int sw = 0, int sh = 0, float sx = 1,float sy = 1, bool fl = false)
	{
		texture = tex;
		spriteWidth = sw;
		spriteHeight = sh;
		scaleX = sx;
		scaleY = sy;
		flipped = fl;

		size = (tex->getWidth() / sw)* (tex->getHeight() / sh);;
	}

	LPTEXTURE GetTexture(){ return texture; }
	int GetWidth() { return spriteWidth; }
	int GetHeight() { return spriteHeight; }
	float GetScaleX() { return scaleX; }
	float GetScaleY() { return scaleY; }
	int GetSize() { return size; }
	bool IsFlipped() { return flipped; }
	
	RECT GetSprite(int index);
};
