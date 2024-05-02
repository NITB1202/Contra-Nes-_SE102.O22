#pragma once

#include <Windows.h>

#define RUNMAN_START_VX 0.1f
#define RUNMAN_START_VY 0.2f
#define RUNMAN_DIE_DEFLECT_SPEED 0.1f 

#define RUNMAN_DIE_BY_GUN_DURATION 300
#define RUNMAN_DIE_BY_WATER_DURATION 100

class RunmanState
{
protected:
	int direction;
public:
	RunmanState(int direction) { this->direction = direction; }
	int GetDirection() { return direction; }
	virtual void UpdateStatus(float& vx, float& vy, bool& isDeleted) = 0;
	virtual int GetAnimationID() = 0;
};

class RunmanRunning : public RunmanState
{
public:
	RunmanRunning(int direction) : RunmanState(direction) {}
	void UpdateStatus(float& vx, float& vy, bool& isDeleted);
	int GetAnimationID();
};

class RunmanFalling : public RunmanState
{
public:
	RunmanFalling(int direction) : RunmanState(direction) {}
	void UpdateStatus(float& vx, float& vy, bool& isDeleted);
	int GetAnimationID();
};

class RunmanDieByShooting : public RunmanState
{
private:
	DWORD dieAnimationStart = -1;
public:
	RunmanDieByShooting(int direction) : RunmanState(direction) 
	{
		dieAnimationStart = GetTickCount64();
	}
	void UpdateStatus(float& vx, float& vy, bool& isDeleted);
	int GetAnimationID();
};

class RunmanDieByDrown : public RunmanState
{
private:
	DWORD dieAnimationStart = -1;
public:
	RunmanDieByDrown(int direction) : RunmanState(direction)
	{
		dieAnimationStart = GetTickCount64();
	}
	void UpdateStatus(float& vx, float& vy, bool& isDeleted);
	int GetAnimationID();
};