#include "Animation.h"

RECT Animation :: GetSprite(int index)
{
	int texWidth = texture->getWidth();
	int texHeight = texture->getHeight();
	int SpriteEachRow = texWidth / spriteWidth;
	int spriteRow = index / SpriteEachRow;
	int spriteCol = index % SpriteEachRow;

	RECT rect;
	rect.left = spriteWidth * spriteCol;
	rect.right = rect.left + spriteWidth;
	rect.top = spriteHeight * spriteRow;
	rect.bottom = rect.top + spriteHeight;

	return rect;
}
