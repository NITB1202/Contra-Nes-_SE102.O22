#include "Camera.h"
#include "Player.h"
#include "Game.h"
#include "MyUtility.h"

Camera* Camera::instance = NULL;

void Camera::Init(int w, int h)
{
	width = w;
	height = h;
}

void Camera::SetPosCamera(float x, float y)
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

void Camera::Update(DWORD dt)
{
	switch (cameraUpdateType)
	{
	case 1:
		UpdateByX(dt);
		break;
	case 2:
		UpdateByY(dt);
		break;
	}
}

void Camera::UpdateByX(DWORD dt)
{
	Player* player = Player::GetInstance();
	RECT bossArea = Game::GetInstance()->GetCurrentScene()->GetBossArea();

	if (camx + width == bossArea.right) return;

	if (camx + width < bossArea.right && MyUtility::CheckIntersect(bossArea, this->GetBound()))
	{
		camx += vx * dt;

		if (camx + width > bossArea.right)
			camx = bossArea.right - width;
		return;
	}

	if (player->GetX() > camx + width / 2)
		camx += vx * dt;

}

void Camera::UpdateByY(DWORD dt)
{
	Player* player = Player::GetInstance();
	RECT bossArea = Game::GetInstance()->GetCurrentScene()->GetBossArea();

	if (camy == bossArea.top) return;

	if (camy < bossArea.top && MyUtility::CheckIntersect(bossArea, this->GetBound()))
	{
		camy += vy * dt;
		if (camy > bossArea.top)
			camy = bossArea.top;

		return;
	}

	if (player->GetY() - player->GetHeight() > camy - height/2)
		camy += vy * dt;

}

Camera* Camera::GetInstance()
{
	if (instance == NULL) instance = new Camera();
	return instance;
}