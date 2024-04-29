#pragma once
//player define

#define TEXTURE_PATH_PLAYER_IDLE_RIGHT L"image\\Player\\bill_stand_right.png"
#define TEXTURE_PATH_PLAYER_RUN_RIGHT L"image\\Player\\bill_run_right.png"
#define TEXTURE_PATH_PLAYER_GUN_TOP_RIGHT L"image\\Player\\bill_topright.png"
#define TEXTURE_PATH_PLAYER_GUN_DOWN_RIGHT L"image\\Player\\bill_downright.png"
#define TEXURE_PATH_PLAYER_GUN_UP L"image\\Player\\bill_up.png"
#define TEXURE_PATH_PLAYER_LAY_DOWN L"image\\Player\\bill_lay_down.png"
#define TEXTURE_PATH_PLAYER_JUMP_UP L"image\\Player\\bill_jump.png"
#define TEXTURE_PATH_PLAYER_DIE_RIGHT L"image\\Player\\bill_die.png"
#define TEXTURE_PATH_PLAYER_LAY_DIE_RIGHT L"image\\Player\\bill_die_lay.png"
#define TEXTURE_PATH_PLAYER_SHOOT_RUN_RIGHT L"image\\Player\\bill_shoot_run.png"

#define PLAYER_SPRITE_WIDTH 28
#define PLAYER_SPRITE_HEIGHT 40
#define PLAYER_JUMP_SPRITE_WIDTH 22
#define PLAYER_JUMP_SPRITE_HEIGHT 20
#define PLAYER_GUN_UP_HEIGHT 46
#define PLAYER_LAY_DOWN_SPRITE_WIDTH 34
#define PLAYER_LAY_DOWN_SPRITE_HEIGHT 17
#define PLAYER_DIE_SPRITE_WIDTH 34


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
#define PLAYER_DIE_RIGHT_ANIMATION 313
#define PLAYER_DIE_LEFT_ANIMATION 314
#define PLAYER_LAY_DIE_RIGHT_ANIMATION 315
#define PLAYER_LAY_DIE_LEFT_ANIMATION 316
#define PLAYER_SHOOT_RUN_RIGHT_ANIMATION 317
#define PLAYER_SHOOT_RUN_LEFT_ANIMATION 318

//runman define

#define TEXTURE_PATH_RUNMAN_RIGHT L"image\\Enemy\\run_man_right.png"

#define RUNMAN_SPRITE_WIDTH 24
#define RUNMAN_SPRITE_HEIGHT 36

#define RUNMAN_RUN_LEFT_ANIMATION 100
#define RUNMAN_RUN_RIGHT_ANIMATION 101

//Sniper define
#define TEXTURE_PATH_SNIPER_LEFT_BASE L"image\\Enemy\\Sniper\\Sniper_Left_Base.png"
#define TEXTURE_PATH_SNIPER_LEFT_HIGH L"image\\Enemy\\Sniper\\Sniper_Left_High.png"
#define TEXTURE_PATH_SNIPER_LEFT_LOW L"image\\Enemy\\Sniper\\Sniper_Left_Low.png"
#define TEXTURE_PATH_HIDDEN_SNIPER L"image\\Enemy\\Sniper\\HiddenSniper.png"
#define TEXTURE_PATH_HIDDEN_SNIPER_START L"image\\Enemy\\Sniper\\HiddenSniper_Start.png"
#define TEXTURE_PATH_HIDDEN_SNIPER_END L"image\\Enemy\\Sniper\\HiddenSniper_End.png"

#define SNIPER_SPRITE_WIDTH 24
#define SNIPER_SPRITE_HEIGHT 43

#define SNIPER_AMBUSH_ANIMATION 4000
#define SNIPER_HIDDEN_START_ANIMATION 4001
#define SNIPER_HIDDEN_END_ANIMATION 4002

#define SNIPER_LEFT_BASE_ANIMATION 4003
#define SNIPER_LEFT_HIGH_ANIMATION 4004
#define SNIPER_LEFT_LOW_ANIMATION 4005


//turret define

#define TEXTURE_PATH_TURRET_CLOSE L"image\\Enemy\\Turret\\Turret_Close.png"
#define TEXTURE_PATH_TURRET_OPENING L"image\\Enemy\\Turret\\Turret_Opening.png"
#define TEXTURE_PATH_TURRET_0 L"image\\Enemy\\Turret\\Turret_0.png"
#define TEXTURE_PATH_TURRET_30 L"image\\Enemy\\Turret\\Turret_30.png"
#define TEXTURE_PATH_TURRET_n30 L"image\\Enemy\\Turret\\Turret_-30.png"
#define TEXTURE_PATH_TURRET_60 L"image\\Enemy\\Turret\\Turret_60.png"
#define TEXTURE_PATH_TURRET_n60 L"image\\Enemy\\Turret\\Turret_-60.png"
#define TEXTURE_PATH_TURRET_90 L"image\\Enemy\\Turret\\Turret_90.png"
#define TEXTURE_PATH_TURRET_n90 L"image\\Enemy\\Turret\\Turret_-90.png"
#define TEXTURE_PATH_TURRET_120 L"image\\Enemy\\Turret\\Turret_120.png"
#define TEXTURE_PATH_TURRET_n120 L"image\\Enemy\\Turret\\Turret_-120.png"
#define TEXTURE_PATH_TURRET_150 L"image\\Enemy\\Turret\\Turret_150.png"
#define TEXTURE_PATH_TURRET_n150 L"image\\Enemy\\Turret\\Turret_-150.png"
#define TEXTURE_PATH_TURRET_180 L"image\\Enemy\\Turret\\Turret_-180.png"


#define TURRET_CLOSE_ANIMATION 3000
#define TURRET_OPENING_ANIMATION 3001
#define TURRET_0_ANIMATION 3002
#define TURRET_30_ANIMATION 3003
#define TURRET_n30_ANIMATION 3004
#define TURRET_60_ANIMATION 3005
#define TURRET_n60_ANIMATION 3006
#define TURRET_90_ANIMATION 3007
#define TURRET_n90_ANIMATION 3008
#define TURRET_120_ANIMATION 3009
#define TURRET_n120_ANIMATION 3010
#define TURRET_150_ANIMATION 3011
#define TURRET_n150_ANIMATION 3012
#define TURRET_180_ANIMATION 3013

#define TURRET_SPRITE_HEIGHT 32
#define TURRET_SPRITE_WIDTH 32

//cannon define
#define TEXTURE_PATH_CANNON_CLOSE L"image\\Enemy\\Cannon\\Cannon_Close.png"
#define TEXTURE_PATH_CANNON_OPENING L"image\\Enemy\\Cannon\\Cannon_Init.png"
#define TEXTURE_PATH_CANNON_120 L"image\\Enemy\\Cannon\\Cannon_120.png"
#define TEXTURE_PATH_CANNON_150 L"image\\Enemy\\Cannon\\Cannon_150.png"
#define TEXTURE_PATH_CANNON_180 L"image\\Enemy\\Cannon\\Cannon_180.png"

#define CANNON_CLOSE_ANIMATION 3300
#define CANNON_OPENING_ANIMATION 3301
#define CANNON_120_ANIMATION 3302
#define CANNON_150_ANIMATION 3303
#define CANNON_180_ANIMATION 3304

#define CANNON_SPRITE_HEIGHT 32
#define CANNON_SPRITE_WIDTH 32


//bullet define
#define TEXTURE_PATH_NORMAL_BULLET L"image\\Bullet\\bullet_b.png"

#define NORMAL_BULLET 400

#define TEXTURE_PATH_TURRET_BULLET L"image\\Bullet\\TBullet.png"

#define TURRET_BULLET 401


//effect define
#define TEXTURE_PATH_DIE_EFFECT L"image\\Effect\\die_effect.png"

#define DIE_EFFECT_SPRITE_WIDTH 32
#define DIE_EFFECT_SPRITE_HEIGHT 32

#define DIE_EFFECT_ANIMATION 500

// List of path scene
#define PATH_SCENE_0 L"SceneInfo\\Scene0.txt"

enum shootingDirection
{
	SHOOT_LEFT,
	SHOOT_RIGHT,
	SHOOT_TOP,
	SHOOT_DOWN,
	SHOOT_TOPLEFT,
	SHOOT_TOPLEFT2,
	SHOOT_TOPRIGHT,
	SHOOT_TOPRIGHT2,
	SHOOT_DOWNLEFT,
	SHOOT_DOWNLEFT2,
	SHOOT_DOWNRIGHT,
	SHOOT_DOWNRIGHT2,
};