#include "Scene.h"
#include <fstream>
#include <sstream>
#include "Player.h"
//file scene gom co link file map va link file ma tran va link file obj

LPWSTR ConvertStringToLPWSTR(const string& str) 
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	LPWSTR lpwstr = new WCHAR[size_needed];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, lpwstr, size_needed);
	return lpwstr;
}

Scene::Scene(string path)
{
	ifstream file(path);
	if (!file.is_open())
		return;

	string mapPath; 
	getline(file, mapPath);
	string matrixPath;
	getline(file, matrixPath);

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

	map = new Map(ConvertStringToLPWSTR(mapPath), matrixPath);

	file.close();
}

void Scene :: Update()
{
	map->Update();
	//gameobject->Update();
}

void Scene :: Render()
{
	map->Render();
}