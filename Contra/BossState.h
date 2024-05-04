#pragma once
#include <Windows.h>

class BossState
{
protected:
	int duration = 0;
	int startTime;
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

