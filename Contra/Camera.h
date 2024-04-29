#pragma once
#include <Windows.h>

class Camera
{
	static Camera* instance;

	float camx, camy;

	float vx = 0.15;
	float vy = 0.15;

	int width, height;

public:
	
	void Init(int w, int h);
	void setPosCamera(float x, float y);

	float getX() { return camx; }
	float getY() { return camy; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	RECT GetBound();
	
	void UpdateByX(DWORD dt);
	void UpdateByY(DWORD dt);

	static Camera* GetInstance();

};
typedef Camera* LPCAMERA;