#pragma once
#include <Windows.h>

class Camera
{
	float camx;
	float camy;
	
	int width;
	int height;

	float vx = 0.2f;
	float vy = 0.1f;

	int mapWidth;
	int mapHeight;

public:

	Camera(float x, float y, int w, int h);
	void setPosCamera(float x, float y);

	float getX() { return camx; }
	float getY() { return camy; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	
	void UpdateByX(DWORD dt);
	void UpdateByY();

};
typedef Camera* LPCAMERA;