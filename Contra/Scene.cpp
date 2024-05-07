#include "Scene.h"
#include "Player.h"
#include "MyUtility.h"
#include "Runman.h"

#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

Scene::Scene(LPWSTR path)
{
	ifstream file(path);
	if (!file.is_open())
		return;

	string mapPath; 
	getline(file, mapPath);
	string matrixPath;
	getline(file, matrixPath);

	background = new Map(MyUtility::ConvertStringToLPWSTR(mapPath), matrixPath);

	getline(file, objectPath);

	string line;

	getline(file, line);
	stringstream ss(line);

	ss >> binaryTreeType;

	ss >> playerStartX;
	ss >> playerStartY;
	ss >> playerState;

	ss >> cameraStartX;
	ss >> cameraStartY;
	ss >> cameraUpdateType;

	ss >> bossArea.left;
	ss >> bossArea.right;
	ss >> bossArea.top;
	ss >> bossArea.bottom;

	file.close();
}

void Scene::BeginScene()
{
	Camera* camera = Camera::GetInstance();
	camera->SetPosCamera(cameraStartX, cameraStartY);
	camera->SetCameraUpdateType(cameraUpdateType);

	Player* player = Player::GetInstance();
	player->SetPosition(playerStartX, playerStartY);
	player->SetBeginState(playerState);

	delete objectTree;
	objectTree = new BinaryTree(objectPath, background->GetWidth(), background->GetHeight(),binaryTreeType);
}

void Scene :: Update(DWORD dt)
{
	background->Update();

	//Check if the object is actually collide with camera
	RECT cameraBound = Camera::GetInstance()->GetBound();
	map<int,LPGAMEOBJECT> objectFromTree = objectTree->GetObjectInBound(cameraBound);
	vector<pair<float, float>> spawnPoint;
	objectOnScreen.clear();

	for (auto it = objectFromTree.begin(); it != objectFromTree.end();it++)
	{
		LPGAMEOBJECT object = it->second;
		RECT objectCollisionBound = object->GetCollisionBound();

		if (!MyUtility::CheckIntersect(cameraBound, objectCollisionBound) || object->IsDeleted())
		{
			if(object->IsDeleted())
				objectTree->RemoveObject(it->first, it->second);

			continue;
		}

		if(object->GetBaseType() == GROUND && objectCollisionBound.left < cameraBound.left)
		{
			float spawnX = cameraBound.left - RUNMAN_WIDTH;
			float spawnY = object->GetY() + RUNMAN_HEIGHT;
			spawnPoint.push_back(make_pair(spawnX, spawnY));
			continue;
		}

		if (object->GetBaseType() == GROUND && objectCollisionBound.right > cameraBound.right)
		{
			float spawnX = cameraBound.right + RUNMAN_WIDTH;
			float spawnY = object->GetY() + RUNMAN_HEIGHT;
			spawnPoint.push_back(make_pair(spawnX, spawnY));
			continue;
		}

		object->Update(dt);
		objectOnScreen.push_back(object);
	}

	if (!MyUtility::CheckIntersect(cameraBound,bossArea)) // Boss area -> don't spawn enemy
	{
		if (GetTickCount64() - lastSpawnTime > SPAWN_SEPARATION && randomSpawnEnemy.size() < MAX_SPAWN_ENEMY)
		{
			if (spawnPoint.size() > 0)
			{
				int numOfEnemy = rand() % 2;
				pair<float, float> spawnSpot = spawnPoint[rand() % spawnPoint.size()];
				int direction = spawnSpot.first < cameraBound.left ? 1 : -1;

				if (numOfEnemy > 0)
				{
					Runman* runman = new Runman(direction);
					runman->SetSpeed(direction * RUNMAN_START_VX, 0);
					runman->SetPosition(spawnSpot.first, spawnSpot.second);
					randomSpawnEnemy.push_back(runman);
					lastSpawnTime = GetTickCount64();
				}
			}
		}
	}

	for (int i = 0; i < randomSpawnEnemy.size(); i++)
	{
		LPGAMEOBJECT enemy = randomSpawnEnemy[i];
		enemy->Update(dt);

		if ((enemy->GetVx() > 0 && enemy->GetX() > cameraBound.right) ||
			(enemy->GetVx() < 0 && enemy->GetX()+ enemy->GetWidth() < cameraBound.left) ||
			enemy->IsDeleted())
		{
			randomSpawnEnemy.erase(randomSpawnEnemy.begin() + i);
			i--;
		}
	}

}

void Scene :: Render()
{
	background->Render();

	for (int i = 0; i < objectOnScreen.size(); i++)
		objectOnScreen[i]->Render();

	for (int i = 0; i < randomSpawnEnemy.size(); i++)
		randomSpawnEnemy[i]->Render();
}

vector<LPGAMEOBJECT> Scene::GetCollidableObject(LPGAMEOBJECT obj)
{
	map<int, LPGAMEOBJECT> objectInTree = objectTree->GetObjectInBound(obj->GetCollisionBound());
	vector<LPGAMEOBJECT> collidableObject;

	for (auto it = objectInTree.begin(); it != objectInTree.end(); it++)
		collidableObject.push_back(it->second);

	for (int i = 0; i < randomSpawnEnemy.size(); i++)
		collidableObject.push_back(randomSpawnEnemy[i]);

	return collidableObject;
}

Scene::~Scene()
{
	delete background;
	delete objectTree;

	for (int i = 0; i < objectOnScreen.size(); i++)
		delete objectOnScreen[i];
	
	for (int i = 0; i < randomSpawnEnemy.size(); i++)
		delete randomSpawnEnemy[i];
}