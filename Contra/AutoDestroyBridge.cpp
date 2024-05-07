#include "AutoDestroyBridge.h"
#include "Player.h"
#include "ObjectConfig.h"
#include "SoundManager.h"

int AutoDestroyBridge::GetDestroyDistance()
{
	switch (destroyState)
	{
	case 0:
		return 0;
	case 1:
		return 66;
	case 2:
		return 133;
	case 3:
		return 193;
	case 4:
		return 256;
	}
}

RECT AutoDestroyBridge::GetCollisionBound()
{
	RECT collisionBound;
	collisionBound.top = y;
	collisionBound.bottom = y - height;
	collisionBound.left = x + GetDestroyDistance();
	collisionBound.right = x + width;
	return collisionBound;
}

void AutoDestroyBridge::Update(DWORD dt)
{
	LPPLAYER player = Player::GetInstance();
	float left = x + GetDestroyDistance();

	if (player->GetX() >= left && destroyState < 4)
	{
		destroyState++;
		explode = true;
		explodeStart = GetTickCount64();
		SoundManager::GetInstance()->Play(DESTROY_BRIDGE);
	}

	if (explode && GetTickCount64() - explodeStart > EXPLODE_EFFECT_DURATION)
		explode = false;
}

void AutoDestroyBridge::Render()
{
	switch (destroyState)
	{
	case 0:
		AnimationID = BRIDGE_NORMAL_ANIMATION;
		break;
	case 1:
		AnimationID = BRIDGE_DESTROY1_ANIMATION;
		break;
	case 2:
		AnimationID = BRIDGE_DESTROY2_ANIMATION;
		break;
	case 3:
		AnimationID = BRIDGE_DESTROY3_ANIMATION;
		break;
	case 4:
		AnimationID = BRIDGE_DESTROY4_ANIMATION;
		break;
	}

	AniHandler->Render(AnimationID, x + 54, y);

	if (explode)
	{
		float explodeX = x + GetDestroyDistance() - EXPLODE_EFFECT_WIDTH;
		effectHandler->Render(EXPLODE_EFFECT_ANIMATION, explodeX, y + EXPLODE_EFFECT_WIDTH / 2);
	}
}