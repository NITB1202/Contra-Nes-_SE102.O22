#include "Scene.h"
#include "Player.h"
#include "MyUtility.h"
#include <fstream>
#include <sstream>

using namespace std;

LPWSTR ConvertStringToLPWSTR(const string& str) 
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	LPWSTR lpwstr = new WCHAR[size_needed];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, lpwstr, size_needed);
	return lpwstr;
}

Scene::Scene(LPWSTR path)
{
	ifstream file(path);
	if (!file.is_open())
		return;

	string mapPath; 
	getline(file, mapPath);
	string matrixPath;
	getline(file, matrixPath);

	background = new Map(ConvertStringToLPWSTR(mapPath), matrixPath);

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
	objectOnScreen = objectTree->GetObjectInBound(cameraBound);
	for (auto it = objectOnScreen.begin(); it != objectOnScreen.end();)
	{
		if (!MyUtility::CheckIntersect(cameraBound, it->second->GetCollisionBound()))
		{
			it = objectOnScreen.erase(it);	//If not then remove it
			continue;
		}

		if (it->second->IsDeleted())
		{
			objectTree->RemoveObjectInTree(it->first, it->second);
			it = objectOnScreen.erase(it);
		}
		else
		{
			//Update object on screen
			it->second->Update(dt);
			it++;
		}
	}
}

void Scene :: Render()
{
	background->Render();

	for (auto it = objectOnScreen.begin(); it != objectOnScreen.end(); it++)
		it->second->Render();
}

vector<LPGAMEOBJECT> Scene::GetCollidableObject(LPGAMEOBJECT obj)
{
	map<int, LPGAMEOBJECT> objectInTree = objectTree->GetObjectInBound(obj->GetCollisionBound());
	vector<LPGAMEOBJECT> collidableObject;

	for (auto it = objectInTree.begin(); it != objectInTree.end(); it++)
		collidableObject.push_back(it->second);

	return collidableObject;
}