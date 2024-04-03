#pragma once
#include <Windows.h>
//Define player status
enum PlayerDirection {
	LEFT,
	RIGHT
};

class PlayerState
{
protected:
	int direction;
public:
	int GetDirection() { return direction; }
	virtual PlayerState* OnKeyDown(int keyCode) = 0;
	virtual PlayerState* OnKeyUp(int keyCode) = 0;
	virtual void UpdateStatus() = 0;
	virtual int GetStateAnimation() = 0;
};

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState(int dir) {direction = dir;}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerRunningState : public PlayerState
{
public:
	PlayerRunningState(int dir) { direction = dir; }
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerJumpingState : public PlayerState
{
private:
	int maxJumpHeight = 100;
public:
	PlayerJumpingState(int dir, float currentY) { 
		direction = dir;
		maxJumpHeight = currentY + maxJumpHeight;
	}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerLayingState : public PlayerState
{
public:
	PlayerLayingState(int dir) { direction = dir; }
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerGunOverHeadState : public PlayerState
{
public:
	PlayerGunOverHeadState(int dir) { direction = dir; }
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerPointGunUpState : public PlayerState
{
public:
	PlayerPointGunUpState(int dir) { direction = dir; }
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerPointGunDownState : public PlayerState
{
public:
	PlayerPointGunDownState(int dir) { direction = dir; }
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
};

class PlayerFallState : public PlayerState
{
public:
	PlayerFallState(int dir) { direction = dir; }
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	PlayerState* ChangeStateAfterLanding();
};

#define PLAYER_START_VX 0.2f
#define PLAYER_START_VY 0.2f
#define PLAYER_GRAVITY 0.001f


#define PLAYER_WIDTH 28
#define PLAYER_HEIGHT 70
#define PLAYER_JUMP_WIDTH 44
#define PLAYER_JUMP_HEIGHT 40