#include "BossState.h"
#include "ObjectConfig.h"

BossAppear::BossAppear()
{
	duration = 300;
}

int BossAppear::GetAnimationID()
{
	return BOSS_APPEAR_ANIMATION;
}

BossState* BossAppear::ChangeState()
{
	if (GetTickCount64() - startTime > duration)
		return new BossClose();

	return NULL;
}

BossOpen::BossOpen()
{
	duration = 2000;
}

int BossOpen::GetAnimationID()
{
	if(GetTickCount64() - startTime < 300)
		return BOSS_OPEN_ANIMATION;

	return BOSS_OPEN_STOP_ANIMATION;
}

BossState* BossOpen::ChangeState()
{
	if (GetTickCount64() - startTime > duration)
		return new BossClose();

	return NULL;
}

BossClose::BossClose()
{
	duration = 3000;
}

int BossClose::GetAnimationID()
{
	return BOSS_CLOSE_ANIMATION;
}

BossState* BossClose::ChangeState()
{
	if (GetTickCount64() - startTime > duration)
		return new BossOpen();

	return NULL;
}

int BossDie::GetAnimationID()
{
	return BOOS_DIE_ANIMATION;
}

BossState* BossDie::ChangeState()
{
	return NULL;
}

BallState* BallAppear::ChangeState()
{
	return NULL;
}

void BallAppear::UpdateStatus(float& vx, float& vy, int direction)
{
	vx = direction * 0.1;
	vy = 0.1;
}
