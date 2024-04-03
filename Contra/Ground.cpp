#include "Ground.h"
#include "Player.h"

bool Ground::IsBlocking()
{
	Player* player = Player::GetInstance();
	if (player->GetY() - player->GetHeight() < y)
		return false;
	return true;
}