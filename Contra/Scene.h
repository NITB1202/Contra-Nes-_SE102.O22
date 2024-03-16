#pragma once
#include "Map.h"
#include "BinaryTree.h"

class Scene
{
	LPMAP map;
	LPBINARYTREE objList;

public:
	Scene(LPWSTR path);
	void Update(DWORD dt);
	void Render();

	int GetMapWidth() { return map->GetWidth(); }
	int GetMapheight() { return map->GetHeight(); }
};