#pragma once
#include "Map.h"
#include "BinaryTree.h"

class Scene
{
private:

	LPMAP background;
	LPBINARYTREE objectTree;
	vector<LPGAMEOBJECT> objectOnScreen;

public:

	Scene(LPWSTR path);

	void Update(DWORD dt);
	void Render();

	vector<LPGAMEOBJECT> GetCollidableObject(LPGAMEOBJECT obj);
	vector<LPGAMEOBJECT> GetOnScreenObject() { return objectOnScreen; }

	LPMAP GetMap() { return background; }
	LPBINARYTREE GetObjectTree() { return objectTree; }
};
typedef Scene* LPSCENE;