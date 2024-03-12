#pragma once
#include "Map.h"
#include "Camera.h"

class Scene
{
	LPMAP map;
	//BinaryTree objectList;

public:
	Scene(string path);
	void Update();
	void Render();

	int GetMapWidth() { return map->GetWidth(); }
	int GetMapheight() { return map->GetHeitgh(); }
};