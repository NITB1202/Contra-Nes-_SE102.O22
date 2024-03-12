#include "Camera.h"
#include "Player.h"

Camera* Camera::instance = NULL;

extern Player* player;

void Camera::Init(int w, int h)
{
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

void Camera::UpdateByY(DWORD dt)
{

}

Camera* Camera::GetInstance()
{
	if (instance == NULL) instance = new Camera();
	return instance;
}