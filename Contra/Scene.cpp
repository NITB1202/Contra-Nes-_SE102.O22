#include "Scene.h"
#include "Player.h"
#include "MyUtility.h"
#include <fstream>
#include <sstream>

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

	string objPath;
	getline(file, objPath);

	objectTree = new BinaryTree(objPath, background->GetWidth(), background->GetHeight());

	string pos;
	getline(file, pos);
	stringstream ss(pos);

	float playerBeginX, playerBeginY, camBeginX, camBeginY, state;

	ss >> playerBeginX;
	ss >> playerBeginY;
	ss >> state;
	ss >> camBeginX;
	ss >> camBeginY;

	Player::GetInstance()->SetPosition(playerBeginX, playerBeginY);

	Camera::GetInstance()->setPosCamera(camBeginX, camBeginY);

	file.close();
}

void Scene :: Update(DWORD dt)
{
	background->Update();

	//Check if the object is actually collide with camera
	RECT cameraBound = Camera::GetInstance()->GetBound();
	map<int,LPGAMEOBJECT> objectFromTree = objectTree->GetObjectInBound(cameraBound);
	objectOnScreen.clear();
	for (auto it = objectFromTree.begin(); it != objectFromTree.end();it++)
	{
		if (!MyUtility::CheckIntersect(cameraBound, it->second->GetCollisionBound()) || it->second->IsDeleted())
		{
			if(it->second->IsDeleted())
				objectTree->RemoveObjectInTree(it->first, it->second);
			continue;
		}

		it->second->Update(dt);
		objectOnScreen.push_back(it->second);
	}
}

void Scene :: Render()
{
	background->Render();

	for (int i = 0; i < objectOnScreen.size(); i++)
		objectOnScreen[i]->Render();
}

vector<LPGAMEOBJECT> Scene::GetCollidableObject(LPGAMEOBJECT obj)
{
	map<int, LPGAMEOBJECT> objectInTree = objectTree->GetObjectInBound(obj->GetCollisionBound());
	vector<LPGAMEOBJECT> collidableObject;

	for (auto it = objectInTree.begin(); it != objectInTree.end(); it++)
		collidableObject.push_back(it->second);

	return collidableObject;
}