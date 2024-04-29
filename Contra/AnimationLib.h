#pragma once

#include "Animation.h"
#include <unordered_map>

using namespace std;

class AnimationLib
{
private:
	static AnimationLib* instance;
	unordered_map<int, Animation> AnimationArray;

public:
	static AnimationLib* GetInstance();
	void AddAnimation(int ID, Animation ani);
	Animation GetAnimation(int ID);
};

