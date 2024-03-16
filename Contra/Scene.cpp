#include "Scene.h"
#include "Player.h"
#include <fstream>
#include <sstream>

//scene file include link to map file, link to matrix file and link to object file

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

	map = new Map(ConvertStringToLPWSTR(mapPath), matrixPath);

	string objPath;
	getline(file, objPath);

	objList = new BinaryTree(objPath, map);

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
	Player::GetInstance()->SetState(state);

	Camera::GetInstance()->setPosCamera(camBeginX, camBeginY);

	file.close();
}

void Scene :: Update(DWORD dt)
{
	map->Update();
	objList->Update(dt);
}

void Scene :: Render()
{
	map->Render();
	objList->Render();
}