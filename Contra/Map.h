#pragma once

#include "Texture.h"
#include "Camera.h"
#include <string>
#include <vector>
using namespace std;

class Map
{
	LPTEXTURE tilesetImage;

	int width;
	int height;

	int tileWidth;
	int tileHeight;

	vector<vector<int>> matrix;

	int rowBegin = -1;
	int rowEnd = -1;
	int colBegin = -1;
	int colEnd = -1;

public:

	Map(LPWSTR MapPath, string MatrixPath);
	int GetWidth() { return width; }
	int GetHeitgh() { return height; }
	void DrawMap();
	void Update(LPCAMERA cam);
};
typedef Map* LPMAP;