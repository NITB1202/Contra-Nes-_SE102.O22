#include "Camera.h"
#include "Player.h"

extern Player* player;

Camera::Camera(float x, float y, int w, int h)
{
	camx = x;
	camy = y;
	width = w;
	height = h;
}

void Camera::setPosCamera(float x, float y)
{
	camx = x;
	camy = y;
}

void Camera::UpdateByX(DWORD dt)
{
	Game* game = Game::GetInstance();
	if (player->GetX() > camx+width / 2)
		camx += vx*dt;

	int mapwidth = game->GetCurrentScene().GetMapWidth();
	if (camx > mapwidth - width)
		camx = mapwidth - width;
}

void Camera::UpdateByY()
{

}