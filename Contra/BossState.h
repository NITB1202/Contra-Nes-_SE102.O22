#pragma once
#include <Windows.h>

class BossState
{
protected:
	int duration = 0;
	ULONGLONG startTime;
public:
	BossState() { startTime = GetTickCount64(); }
	virtual int GetAnimationID() = 0;
	virtual BossState* ChangeState() = 0;
};

class BossAppear : public BossState
{
public :
	BossAppear();
	int GetAnimationID();
	BossState* ChangeState();
};

class BossOpen : public BossState
{
public:
	BossOpen();
	int GetAnimationID();
	BossState* ChangeState();
};

class BossClose : public BossState
{
public:
	BossClose();
	int GetAnimationID();
	BossState* ChangeState();
};

class BossDie :public BossState
{
public:
	int GetAnimationID();
	BossState* ChangeState();
};


class BallState
{
public:
	virtual BallState* ChangeState() = 0;
	virtual void UpdateStatus(float& vx, float& vy, int direction) = 0;
};

class BallAppear: public BallState
{
public:
	BallState* ChangeState();
	void UpdateStatus(float& vx, float& vy, int direction);
};

class BallSplash : BallState
{
};

class BallSpin :public BallState
{

};

