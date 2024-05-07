#pragma once
#include "AnimationLib.h"
#include "Game.h"
#include "objectConfig.h"
#include <fstream>
#include <sstream>

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

				aniLib->AddAnimation(id, Animation(tex, spriteWidth, spriteHeight, 2, 2, flip));
			}
			else
				tex = game->LoadTexture(MyUtility::ConvertStringToLPWSTR(line));
		}

		animationFile.close();
	}

	tex = game->LoadTexture(TEXTURE_PATH_NORMAL_BULLET);
	aniLib->AddAnimation(NORMAL_BULLET, Animation(tex,tex->getWidth(), tex->getHeight()));

	tex = game->LoadTexture(TEXTURE_PATH_BIG_BULLET);
	aniLib->AddAnimation(BIG_BULLET, Animation(tex, tex->getWidth(), tex->getHeight()));
	aniLib->AddAnimation(BOSS_BULLET, Animation(tex, tex->getWidth(), tex->getHeight(), 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_MOON_BULLET);
	aniLib->AddAnimation(MOON_BULLET, Animation(tex, 18, 16, 2, 2));

	tex = game->LoadTexture(TEXTURE_PATH_GAMEOVER_BACKGROUND);
	aniLib->AddAnimation(GAMEOVER_BACKGROUND, Animation(tex, tex->getWidth(), tex->getHeight()));

	tex = game->LoadTexture(TEXTURE_PATH_INTRO_BACKGROUND);
	aniLib->AddAnimation(INTRO_BACKGROUND, Animation(tex, tex->getWidth(), tex->getHeight()));

	tex = game->LoadTexture(TEXTURE_PATH_TEST);
	aniLib->AddAnimation(TEST, Animation(tex, tex->getWidth(), tex->getHeight()));
}

