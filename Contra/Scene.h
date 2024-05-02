#pragma once
#include "Map.h"
#include "BinaryTree.h"
#include "Portal.h"

#define MAX_SPAWN_ENEMY 3
#define SPAWN_SEPARATION 3000

class Scene
{
private:

	LPMAP background;
	LPBINARYTREE objectTree;

	vector<LPGAMEOBJECT> objectOnScreen;
	vector<LPGAMEOBJECT> randomSpawnEnemy;

	DWORD lastSpawnTime = -1;

	string objectPath;
	int playerState, cameraUpdateType, binaryTreeType;
	float playerStartX, playerStartY;
	float cameraStartX, cameraStartY;

	RECT bossArea;

	LPPORTAL portal;

public:

	Scene(LPWSTR path);

	void BeginScene();
	void ClearSpawnEnemy() {
		lastSpawnTime = -1;
		randomSpawnEnemy.clear();
	}

	void Update(DWORD dt);
	void Render();

	vector<LPGAMEOBJECT> GetCollidableObject(LPGAMEOBJECT obj);
	vector<LPGAMEOBJECT> GetOnScreenObject() { return objectOnScreen; }

	LPMAP GetMap() { return background; }
	LPBINARYTREE GetObjectTree() { return objectTree; }

	RECT GetBossArea() { return bossArea; }

	~Scene();
};
typedef Scene* LPSCENE;