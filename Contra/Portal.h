#pragma once
#include "GameObject.h"

class Portal :public GameObject
{
private:
	int sceneID;
public:
	Portal()
	{
		width = 50;
		height = 50;
	}
	void SetSceneID(int id) { sceneID = id; }
	void Update(DWORD dt);
	//void Render();
	bool IsBlocking() { return false; }
};
typedef Portal* LPPORTAL;
