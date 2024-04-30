#pragma once
#include "AnimationLib.h"
#include "Game.h"
#include "objectConfig.h"
#include <fstream>
#include <sstream>

vector<LPWSTR> scenelink;

void LoadResource()
{
	Game* game = Game::GetInstance();
	LPTEXTURE tex = NULL;
	AnimationLib* aniLib = AnimationLib::GetInstance();
	string resourcePath = "image\\load_resources.txt";

	ifstream file(resourcePath);
	if (!file.is_open())
		return;

	vector<string> animationPath;
	string line;
	while (getline(file, line))
		animationPath.push_back(line);

	file.close();

	for (int i = 0; i < animationPath.size(); i++)
	{
		ifstream animationFile(animationPath[i]);
		if (!animationFile.is_open())
			continue;

		string imagePath;
		int id, spriteWidth, spriteHeight;
		bool flip;

		string line;

		while (getline(animationFile, line))
		{
			if (isdigit(line[0]))
			{
				stringstream ss(line);

				ss >> id;
				ss >> spriteWidth;
				ss >> spriteHeight;
				ss >> flip;

				aniLib->AddAnimation(id, Animation(tex, spriteWidth, spriteHeight, 2, 2,flip));
			}
			else
				tex = game->LoadTexture(MyUtility::ConvertStringToLPWSTR(line));
		}

		animationFile.close();
	}

	tex = game->LoadTexture(TEXTURE_PATH_NORMAL_BULLET);
	aniLib->AddAnimation(NORMAL_BULLET, Animation(tex,tex->getWidth(), tex->getHeight()));

	tex = game->LoadTexture(TEXTURE_PATH_LIFE);
	aniLib->AddAnimation(PLAYER_LIFE, Animation(tex,tex->getWidth(), tex->getHeight(), 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_GAMEOVER_BACKGROUND);
	aniLib->AddAnimation(GAMEOVER_BACKGROUND, Animation(tex, tex->getWidth(), tex->getHeight(), tex->getWidth() / game->GetBackBufferWidth(), tex->getHeight() / game->GetBackBufferHeight()));

	tex = game->LoadTexture(TEXTURE_PATH_CURSOR);
	aniLib->AddAnimation(CURSOR, Animation(tex, tex->getWidth(), tex->getHeight(), 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_DIE_EFFECT);
	aniLib->AddAnimation(DIE_EFFECT_ANIMATION, Animation(tex, DIE_EFFECT_SPRITE_WIDTH, DIE_EFFECT_SPRITE_HEIGHT, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_CLOSE);
	aniLib->AddAnimation(TURRET_CLOSE_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_OPENING);
	aniLib->AddAnimation(TURRET_OPENING_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_0);
	aniLib->AddAnimation(TURRET_0_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	aniLib->AddAnimation(TURRET_180_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5, true));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_30);
	aniLib->AddAnimation(TURRET_30_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	aniLib->AddAnimation(TURRET_n30_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5, true));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_60);
	aniLib->AddAnimation(TURRET_60_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	aniLib->AddAnimation(TURRET_n60_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5, true));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_90);
	aniLib->AddAnimation(TURRET_90_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	aniLib->AddAnimation(TURRET_n90_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5, true));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_120);
	aniLib->AddAnimation(TURRET_120_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	aniLib->AddAnimation(TURRET_n120_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5, true));

	tex = game->LoadTexture(TEXTURE_PATH_TURRET_150);
	aniLib->AddAnimation(TURRET_150_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5));
	aniLib->AddAnimation(TURRET_n150_ANIMATION, Animation(tex, TURRET_SPRITE_WIDTH, TURRET_SPRITE_HEIGHT, 1.5, 1.5, true));

	scenelink.push_back((LPWSTR)PATH_SCENE_0);
}

