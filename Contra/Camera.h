#pragma once
#include <Windows.h>

class Camera
{
	static Camera* instance;

	float camx, camy;

	float vx = 0.15;
	float vy = 0.15;

	int width, height;
	
	int cameraUpdateType = 1;

public:
	
	void Init(int w, int h);
	void SetPosCamera(float x, float y);
	void SetCameraUpdateType(int type) { cameraUpdateType = type; }
	float getX() { return camx; }
	float getY() { return camy; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	RECT GetBound();
	
	void Update(DWORD dt);
	void UpdateByX(DWORD dt);
	void UpdateByY(DWORD dt);

	static Camera* GetInstance();

};
typedef Camera* LPCAMERA;