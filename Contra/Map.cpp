#include "Map.h"
#include "Game.h"
#include <fstream>
#include <sstream>

Map::Map(LPWSTR mapPath, string matrixPath)
{
	tilesetImage = Game::GetInstance()->LoadTexture(mapPath);

	ifstream file(matrixPath);

	if (!file.is_open())
		return;

	string line;
	getline(file, line);
	stringstream ss(line);

	ss >> tileWidth;
	ss >> tileHeight;

	int row, col;
	ss >> col;
	ss >> row;

	width = tileWidth * col;
	height = tileHeight * row;

	while (getline(file, line))
	{
		stringstream temp(line);
		int num;
		vector<int> vec;

		while (temp >> num)
			vec.push_back(num);

		matrix.push_back(vec);
	}

	file.close();
}

bool IsInterger(double num) {
	return num - static_cast<int>(num) == 0;
}

void Map :: Update()
{
	LPCAMERA cam = Camera::GetInstance();
	//toa do y huong len
	colBegin = cam->getX() / tileWidth;
	float num = cam->getX() + cam->getWidth();
	if (IsInterger(num) && (int)num % tileWidth == 0)
		colEnd = num / tileWidth - 1;
	else
		colEnd = num / tileWidth;
	rowBegin = (height - cam->getY()) / tileHeight;
	num = height - cam->getY() + cam->getHeight();
	if (IsInterger(num) && (int)num % tileHeight == 0)
		rowEnd = num / tileHeight - 1;
	else
		rowEnd = num / tileHeight;
}

void Map::Render()
{
	for (int i = rowBegin; i <= rowEnd; i++)
		for (int j = colBegin; j <= colEnd; j++)
		{
			int tileIndex = matrix[i][j]-1;

			int texWidth = tilesetImage->getWidth();
			int texHeight = tilesetImage->getHeight();
			int tileEachRow = texWidth / tileWidth;

			int tileRow = tileIndex / tileEachRow;
			int tileCol = tileIndex % tileEachRow;

			RECT rect;
			rect.left = tileWidth * tileCol;
			rect.right = rect.left + tileWidth;
			rect.top = tileHeight * tileRow;
			rect.bottom = rect.top + tileHeight;

			int tileX = j * tileWidth;
			int tileY = height-i * tileHeight;

			Game::GetInstance()->Draw(tileX, tileY, tilesetImage, 1, 1, 0, &rect);
		}
}