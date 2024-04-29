#pragma once
#include "AnimationLib.h"
#include "Game.h"
#include "objectConfig.h"

vector<LPWSTR> scenelink;

void LoadResource()
{
	Game* game = Game::GetInstance();
	LPTEXTURE tex;
	AnimationLib* aniLib = AnimationLib::GetInstance();

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_IDLE_RIGHT);
	aniLib->AddAnimation(PLAYER_IDLE_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_IDLE_LEFT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2,true));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_RUN_RIGHT);
	aniLib->AddAnimation(PLAYER_RUN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_RUN_LEFT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2, true));

	tex = game->LoadTexture(TEXURE_PATH_PLAYER_GUN_UP);
	aniLib->AddAnimation(PLAYER_GUN_UP_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_GUN_UP_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_GUN_UP_LEFT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_GUN_UP_HEIGHT, 2, 2,true));

	tex = game->LoadTexture(TEXURE_PATH_PLAYER_LAY_DOWN);
	aniLib->AddAnimation(PLAYER_LAY_DOWN_RIGHT_ANIMATION, Animation(tex, PLAYER_LAY_DOWN_SPRITE_WIDTH, PLAYER_LAY_DOWN_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_LAY_DOWN_LEFT_ANIMATION, Animation(tex, PLAYER_LAY_DOWN_SPRITE_WIDTH, PLAYER_LAY_DOWN_SPRITE_HEIGHT, 2, 2,true));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_GUN_TOP_RIGHT);
	aniLib->AddAnimation(PLAYER_GUN_TOP_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_GUN_TOP_LEFT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2,true));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_GUN_DOWN_RIGHT);
	aniLib->AddAnimation(PLAYER_GUN_DOWN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_GUN_DOWN_LEFT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2, true));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_JUMP_UP);
	aniLib->AddAnimation(PLAYER_JUMP_UP_ANIMATION, Animation(tex, PLAYER_JUMP_SPRITE_WIDTH, PLAYER_JUMP_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_DIE_RIGHT);
	aniLib->AddAnimation(PLAYER_DIE_RIGHT_ANIMATION, Animation(tex, PLAYER_DIE_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_DIE_LEFT_ANIMATION, Animation(tex, PLAYER_DIE_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2, true));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_LAY_DIE_RIGHT);
	aniLib->AddAnimation(PLAYER_LAY_DIE_RIGHT_ANIMATION, Animation(tex, PLAYER_DIE_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_LAY_DIE_LEFT_ANIMATION, Animation(tex, PLAYER_DIE_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2, true));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_SHOOT_RUN_RIGHT);
	aniLib->AddAnimation(PLAYER_SHOOT_RUN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(PLAYER_SHOOT_RUN_LEFT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 2, 2, true));
	// load bullet
	tex = game->LoadTexture(TEXTURE_PATH_NORMAL_BULLET);
	aniLib->AddAnimation(NORMAL_BULLET, Animation(tex,8,8));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_BULLET);
	aniLib->AddAnimation(TURRET_BULLET, Animation(tex, 3, 3));
	// load sniper
	tex = game->LoadTexture(TEXTURE_PATH_HIDDEN_SNIPER);
	aniLib->AddAnimation(SNIPER_AMBUSH_ANIMATION, Animation(tex, SNIPER_SPRITE_WIDTH, SNIPER_SPRITE_HEIGHT, 2, 2, true));
	tex = game->LoadTexture(TEXTURE_PATH_HIDDEN_SNIPER_END);
	aniLib->AddAnimation(SNIPER_HIDDEN_END_ANIMATION, Animation(tex, SNIPER_SPRITE_WIDTH, SNIPER_SPRITE_HEIGHT, 2, 2, true));
	tex = game->LoadTexture(TEXTURE_PATH_HIDDEN_SNIPER_START);
	aniLib->AddAnimation(SNIPER_HIDDEN_START_ANIMATION, Animation(tex, SNIPER_SPRITE_WIDTH, SNIPER_SPRITE_HEIGHT, 2, 2, true));
	tex = game->LoadTexture(TEXTURE_PATH_SNIPER_LEFT_BASE);
	aniLib->AddAnimation(SNIPER_LEFT_BASE_ANIMATION, Animation(tex, SNIPER_SPRITE_WIDTH, SNIPER_SPRITE_HEIGHT, 2, 2));
	tex = game->LoadTexture(TEXTURE_PATH_SNIPER_LEFT_LOW);
	aniLib->AddAnimation(SNIPER_LEFT_LOW_ANIMATION, Animation(tex, SNIPER_SPRITE_WIDTH, SNIPER_SPRITE_HEIGHT, 2, 2));
	tex = game->LoadTexture(TEXTURE_PATH_SNIPER_LEFT_HIGH);
	aniLib->AddAnimation(SNIPER_LEFT_HIGH_ANIMATION, Animation(tex, SNIPER_SPRITE_WIDTH, SNIPER_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_RUNMAN_RIGHT);
	aniLib->AddAnimation(RUNMAN_RUN_RIGHT_ANIMATION, Animation(tex, RUNMAN_SPRITE_WIDTH, RUNMAN_SPRITE_HEIGHT, 2, 2));
	aniLib->AddAnimation(RUNMAN_RUN_LEFT_ANIMATION, Animation(tex, RUNMAN_SPRITE_WIDTH, RUNMAN_SPRITE_HEIGHT, 2, 2,true));
	//load cannon
	tex = game->LoadTexture(TEXTURE_PATH_CANNON_OPENING);
	aniLib->AddAnimation(CANNON_OPENING_ANIMATION, Animation(tex, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, 2, 2));
	tex = game->LoadTexture(TEXTURE_PATH_CANNON_CLOSE);
	aniLib->AddAnimation(CANNON_CLOSE_ANIMATION, Animation(tex, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, 2, 2));
	tex = game->LoadTexture(TEXTURE_PATH_CANNON_120);
	aniLib->AddAnimation(CANNON_120_ANIMATION, Animation(tex, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, 2, 2));
	tex = game->LoadTexture(TEXTURE_PATH_CANNON_150);
	aniLib->AddAnimation(CANNON_150_ANIMATION, Animation(tex, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, 2, 2));
	tex = game->LoadTexture(TEXTURE_PATH_CANNON_180);
	aniLib->AddAnimation(CANNON_180_ANIMATION, Animation(tex, CANNON_SPRITE_WIDTH, CANNON_SPRITE_HEIGHT, 2, 2));


	tex = game->LoadTexture(TEXTURE_PATH_DIE_EFFECT);
	aniLib->AddAnimation(DIE_EFFECT_ANIMATION, Animation(tex, DIE_EFFECT_SPRITE_WIDTH, DIE_EFFECT_SPRITE_HEIGHT, 2, 2));
	

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_CLOSE);
	aniLib->AddAnimation(TURRET_CLOSE_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_OPENING);
	aniLib->AddAnimation(TURRET_OPENING_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_0);
	aniLib->AddAnimation(TURRET_0_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	tex = game->LoadTexture(TEXTURE_PATH_TURRET_180);
	aniLib->AddAnimation(TURRET_180_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_30);
	aniLib->AddAnimation(TURRET_30_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	tex = game->LoadTexture(TEXTURE_PATH_TURRET_n30);
	aniLib->AddAnimation(TURRET_n30_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_60);
	aniLib->AddAnimation(TURRET_60_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	tex = game->LoadTexture(TEXTURE_PATH_TURRET_n60);
	aniLib->AddAnimation(TURRET_n60_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_90);
	aniLib->AddAnimation(TURRET_90_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	tex = game->LoadTexture(TEXTURE_PATH_TURRET_n90);
	aniLib->AddAnimation(TURRET_n90_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_120);
	aniLib->AddAnimation(TURRET_120_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	tex = game->LoadTexture(TEXTURE_PATH_TURRET_n120);
	aniLib->AddAnimation(TURRET_n120_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_150);
	aniLib->AddAnimation(TURRET_150_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	tex = game->LoadTexture(TEXTURE_PATH_TURRET_n150);
	aniLib->AddAnimation(TURRET_n150_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	scenelink.push_back((LPWSTR)PATH_SCENE_0);
}

