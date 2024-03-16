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

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_RUN_RIGHT);
	aniLib->AddAnimation(PLAYER_RUN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_TOP_RIGHT);
	aniLib->AddAnimation(PLAYER_TOP_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_DOWN_RIGHT);
	aniLib->AddAnimation(PLAYER_DOWN_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_FACE_RIGHT_IDLE);
	aniLib->AddAnimation(PLAYER_IDLE_RIGHT_ANIMATION, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXURE_PATH_PLAYER_GUN_UP);
	aniLib->AddAnimation(PLAYER_GUN_UP, Animation(tex, PLAYER_SPRITE_WIDTH, PLAYER_GUN_UP_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXURE_PATH_PLAYER_LAY_DOWN);
	aniLib->AddAnimation(PLAYER_LAY_DOWN_ANIMATION, Animation(tex, PLAYER_LAY_DOWN_WIDTH, PLAYER_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_PLAYER_JUMP_UP);
	aniLib->AddAnimation(PLAYER_JUMP_UP, Animation(tex, PLAYER_JUMP_WIDTH, PLAYER_JUMP_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_RUNMAN_RIGHT);
	aniLib->AddAnimation(RUNMAN_RUN_RIGHT_ANIMATION, Animation(tex, RUNMAN_SPRITE_WIDTH, RUNMAN_SPRITE_HEIGHT, 1.5, 1.5));

	scenelink.push_back((LPWSTR)PATH_SCENE_0);
}

