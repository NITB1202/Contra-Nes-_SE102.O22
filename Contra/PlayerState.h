#pragma once
#include <Windows.h>

class PlayerState
{
protected:
	int direction;
public:
	PlayerState(int dir) { direction = dir; }
	int GetDirection() { return direction; }
	virtual PlayerState* OnKeyDown(int keyCode) { return NULL; }
	virtual PlayerState* OnKeyUp(int keyCode) { return NULL; }
	virtual void UpdateStatus() = 0;
	virtual int GetStateAnimation() = 0;
	virtual bool GetGunDirection(float& x, float& y, int& gunDir) { return false; }
	virtual bool CanShoot() { return true; }
};

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(int dir) : PlayerState(dir) {}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	bool GetGunDirection(float& x, float& y, int& gunDir);
};

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(int dir) : PlayerState(dir) {}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	bool GetGunDirection(float& x, float& y, int& gunDir);
};

class PlayerJumpingState : public PlayerState
{
private:
	int maxJumpHeight = 70;
public:
	PlayerJumpingState(int dir, float currentY) : PlayerState(dir) {
		direction = dir;
		maxJumpHeight = currentY + maxJumpHeight;
	}
	int GetStateAnimation();
	void UpdateStatus();
	bool CanShoot() { return false; }
};

class PlayerLayingState : public PlayerState
{
public:
	PlayerLayingState(int dir) : PlayerState(dir) {}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	bool GetGunDirection(float& x, float& y, int& gunDir);
	bool CanShoot();
};

class PlayerGunOverHeadState : public PlayerState
{
public:
	PlayerGunOverHeadState(int dir) : PlayerState(dir) {}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	bool GetGunDirection(float& x, float& y, int& gunDir);
};

class PlayerPointGunUpState : public PlayerState
{
public:
	PlayerPointGunUpState(int dir) : PlayerState(dir) {}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	bool GetGunDirection(float& x, float& y, int& gunDir);
};

class PlayerPointGunDownState : public PlayerState
{
public:
	PlayerPointGunDownState(int dir) : PlayerState(dir) {}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	bool GetGunDirection(float& x, float& y, int& gunDir);
	bool CanShoot();
};

class PlayerFallState : public PlayerState
{
public:
	PlayerFallState(int dir) : PlayerState(dir) {}
	int GetStateAnimation();
	void UpdateStatus();
	PlayerState* ChangeStateAfterLanding();
	bool CanShoot() { return false; }
};

class PlayerDieState :public PlayerState
{
private:
	ULONGLONG startTime;
public:
	PlayerDieState(int dir) : PlayerState(dir) {
		startTime = GetTickCount64();
	}
	int GetStateAnimation();
	void UpdateStatus();
	bool CanShoot() { return false;}
};

#define PLAYER_START_VX 0.15f
#define PLAYER_START_VY 0.2f

#define PLAYER_WIDTH 26
#define PLAYER_HEIGHT 60
#define PLAYER_JUMP_WIDTH 38
#define PLAYER_JUMP_HEIGHT 40
#define PLAYER_LAY_DOWN_WIDTH 30
#define PLAYER_LAY_DOWN_HEIGHT 34
#define GUN_UP_HEIGHT_ADJUST 8
#define PLAYER_DIE_WIDTH 64
#define PLAYER_DIE_HEIGHT 46

#define DIE_ANIMATION_DURATION 500
#define DIE_ANIMATION_DEFLECT_SPEED_X 0.1f
#define DIE_ANIMATION_DEFLECT_SPEED_Y 0.1f
#define RESET_TIME 1000