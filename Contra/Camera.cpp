#include "Camera.h"
#include "Player.h"
#include "Game.h"

Camera* Camera::instance = NULL;

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

RECT Camera::GetBound()
{
	RECT bound;
	bound.left = camx;
	bound.right = camx + width;
	bound.top = camy;
	bound.bottom = camy - height;
	return bound;
}

void Camera::UpdateByX(DWORD dt)
{
	Game* game = Game::GetInstance();
	Player* player = Player::GetInstance();

	if (player->GetX() > camx+width / 2)
		camx +=  vx * dt;

	//if (player->GetX() < camx + width / 3 && player->GetCurrentState()->GetDirection() == LEFT)
		//camx += -vx * dt;

	int mapwidth = game->GetCurrentScene()->GetMap()->GetWidth();

	if (camx < 0)
		camx = 0;

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