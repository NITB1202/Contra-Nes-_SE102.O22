#pragma once
#include "Map.h"
#include "Camera.h"

class Scene
{
	LPMAP map;
	//BinaryTree object;

public:
	Scene(string path, LPCAMERA camera);
	void Update(LPCAMERA cam);
	void Render();

	int GetMapWidth() { return map->GetWidth(); }
	int GetMapheight() { return map->GetHeitgh(); }
};