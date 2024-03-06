#include "AnimationLib.h"

AnimationLib* AnimationLib::instance = NULL;

AnimationLib* AnimationLib :: GetInstance() {
	if (instance == NULL)
		instance = new AnimationLib();
	return instance;
}

void AnimationLib :: AddAnimation(int ID, Animation ani) 
{ 
	AnimationArray.insert({ ID,ani }); 
}

Animation AnimationLib :: GetAnimation(int ID) 
{ 
	return AnimationArray[ID]; 
}