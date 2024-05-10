#include "Portal.h"
#include "MyUtility.h"
#include "Player.h"
#include "Game.h"
#include "SoundManager.h"

void Portal::Update(DWORD dt)
{
	Player* player = Player::GetInstance();
	Game* game = Game::GetInstance();

	if (MyUtility::CheckIntersect(player->GetCollisionBound(), this->GetCollisionBound()))
	{
		SoundManager::GetInstance()->Stop(game->GetCurrentScene()->GetSoundID());
		game->SwitchScene(sceneID);
		game->ClearBackGround();
		game->GetCurrentScene()->ClearSpawnEnemy();
		game->GetCurrentScene()->BeginScene();
		player->Reset();
	}
}

//void Portal::Render() { AniHandler->Render(TEST, x, y);}