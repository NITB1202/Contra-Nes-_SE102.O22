#pragma once
#include <Windows.h>

//Define player status
enum PlayerDirection {
	LEFT = -1,
	RIGHT = 1
};

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
private:
	bool shooting;
public:
	PlayerRunningState(int dir) : PlayerState(dir){
		shooting = false;
	}
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
};

class PlayerFallState : public PlayerState
{
public:
	PlayerFallState(int dir) : PlayerState(dir) {}
	int GetStateAnimation();
	void UpdateStatus();
	PlayerState* ChangeStateAfterLanding();
};

class PlayerDieState :public PlayerState
{
private:
	int startTime;
public:
	PlayerDieState(int dir) : PlayerState(dir) {
		startTime = GetTickCount64();
	}
	int GetStateAnimation();
	void UpdateStatus();
};

#define PLAYER_START_VX 0.15f
#define PLAYER_START_VY 0.2f
#define PLAYER_GRAVITY 0.001f

#define PLAYER_WIDTH 28
#define PLAYER_HEIGHT 70
#define PLAYER_JUMP_WIDTH 44
#define PLAYER_JUMP_HEIGHT 40
#define PLAYER_LAY_DOWN_WIDTH 40
#define PLAYER_LAY_DOWN_HEIGHT 34
#define GUN_UP_HEIGHT_ADJUST 8

#define DIE_ANIMATION_DURATION 500
#define DIE_ANIMATION_DEFLECT_SPEED_X 0.1f
#define DIE_ANIMATION_DEFLECT_SPEED_Y 0.05f
#define RESET_TIME 1000