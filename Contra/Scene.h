#pragma once
#include "Map.h"
#include "BinaryTree.h"

class Scene
{
private:

	LPMAP background;
	LPBINARYTREE objectTree;

	map<int, LPGAMEOBJECT> objectOnScreen;

public:

	Scene(LPWSTR path);

	void Update(DWORD dt);
	void Render();

	vector<LPGAMEOBJECT> GetCollidableObject(LPGAMEOBJECT obj);

	LPMAP GetMap() { return background; }
	LPBINARYTREE GetObjectTree() { return objectTree; }
};
typedef Scene* LPSCENE;