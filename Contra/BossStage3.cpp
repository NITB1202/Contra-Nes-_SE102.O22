#include "BossStage3.h"

void BossHandBall::Update(DWORD dt)
{

}

void BossHandBall::Render()
{
}

BossHand::BossHand()
{
}

void BossHand::Update(DWORD dt)
{
}

void BossHand::Render()
{
}

BossHand::~BossHand()
{
}

BossStage3::BossStage3()
{
	baseType = PLAYER;
	leftHand = new BossHand();
	leftHand->SetDirection(-1);
	rightHand = new BossHand();
	rightHand->SetDirection(1);
	currentState = new BossAppear();
}

void BossStage3::Update(DWORD dt)
{
	BossState* newState = currentState->ChangeState();
	if (newState != NULL)
	{
		delete currentState;
		currentState = newState;
	}
}

void BossStage3::Render()
{
	AnimationID = currentState->GetAnimationID();

	AniHandler->Render(AnimationID, x, y);
}

BossStage3::~BossStage3()
{
	delete leftHand;
	delete rightHand;
	delete currentState;
}
