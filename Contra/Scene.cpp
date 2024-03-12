#include "Scene.h"
#include <fstream>
#include <sstream>
#include "Player.h"

extern LPPLAYER player;
//file scene gom co link file map va link file ma tran va link file obj

LPWSTR ConvertStringToLPWSTR(const string& str) 
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	LPWSTR lpwstr = new WCHAR[size_needed];
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, lpwstr, size_needed);
	return lpwstr;
}

Scene::Scene(string path, LPCAMERA camera)
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

	player->SetPosition(playerBeginX, playerBeginY);
	player->SetState(state);
	camera->setPosCamera(camBeginX, camBeginY);

	map = new Map(ConvertStringToLPWSTR(mapPath), matrixPath);

	file.close();
}

void Scene :: Update(LPCAMERA cam)
{
	map->Update(cam);
	//gameobject->Update();
}

void Scene :: Render()
{
	map->DrawMap();
}