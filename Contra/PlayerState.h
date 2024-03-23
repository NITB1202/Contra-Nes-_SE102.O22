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
	virtual PlayerState* OnKeyUp(int keyCode) { return NULL; }
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

enum jumpingState 
{
	THROW,
	FALL
};

class PlayerJumpingState : public PlayerState
{
private:
	bool jumpingDone;
	int maxJumpHeight = 60;
	int jumpingState;
public:
	PlayerJumpingState(int dir) { 
		direction = dir;
		jumpingDone = false;
		jumpingState = THROW;
	}
	PlayerState* OnKeyDown(int keyCode);
	PlayerState* OnKeyUp(int keyCode);
	int GetStateAnimation();
	void UpdateStatus();
	PlayerState* ChangeStateAfterJumpEnd();
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

//Define player state animation ID

#define PLAYER_IDLE_RIGHT_ANIMATION 300
#define PLAYER_IDLE_LEFT_ANIMATION 301
#define PLAYER_RUN_RIGHT_ANIMATION 302
#define PLAYER_RUN_LEFT_ANIMATION 303
#define PLAYER_GUN_UP_LEFT_ANIMATION 304
#define PLAYER_GUN_UP_RIGHT_ANIMATION 305
#define PLAYER_LAY_DOWN_RIGHT_ANIMATION 306
#define PLAYER_LAY_DOWN_LEFT_ANIMATION 307
#define PLAYER_GUN_TOP_RIGHT_ANIMATION 308
#define PLAYER_GUN_TOP_LEFT_ANIMATION 309
#define PLAYER_GUN_DOWN_RIGHT_ANIMATION 310
#define PLAYER_GUN_DOWN_LEFT_ANIMATION 311
#define PLAYER_JUMP_UP_ANIMATION 312

#define PLAYER_START_VX 0.2f
#define PLAYER_START_VY 0.25f
#define PLAYER_GRAVITY 0.16f