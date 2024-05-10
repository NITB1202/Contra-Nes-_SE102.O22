#include <dinput.h>
#include "Menu.h"
#include "Game.h"
#include "ObjectConfig.h"
#include "SoundManager.h"

void Menu::Update(DWORD dt)
{
	if (trans != NULL && !trans->IsFinish())
	{
		trans->Update(dt);
		return;
	}

	selectArrowY = menuY + (select - 1) * optionHeight;
}

void Menu::Render()
{
	if (trans != NULL && !trans->IsFinish())
	{
		trans->Render();
		return;
	}

	animationHandler->DrawAsset(backgroundID, 0, 0);
	animationHandler->DrawAsset(CURSOR,selectArrowX, selectArrowY);
}

void Menu::OnKeyDown(int keyCode)
{
	if (trans != NULL && !trans->IsFinish())
		return;

	if (keyCode == DIK_A)
	{
		HandlerOption();
		return;
	}

	if (keyCode == DIK_UP)
		select--;

	if (keyCode == DIK_DOWN)
		select++;

	if (select < 1)
		select = option;

	if (select > option)
		select = 1;
}

void Menu::HandlerOption()
{
	Game* game = Game::GetInstance();
	Player* player = Player::GetInstance();
	SoundManager* sound = SoundManager::GetInstance();

	switch (backgroundID)
	{
	case GAMEOVER_BACKGROUND:
	{
		switch (select)
		{
		case 1:
		{
			game->showMenu = false;
			game->ClearBackGround();
			sound->Stop(GAMEOVER_SOUND);
			sound->Play(game->GetCurrentScene()->GetSoundID());
			player->Reset();
			break;
		}
		case 2:
		{
			game->SetCurrentMenu(INTRO_MENU);
			break;
		}
		}
		break;
	}
	case INTRO_BACKGROUND:
	{
		switch (select)
		{
		case 1:
		{
			game->showMenu = false;
			game->GetCurrentScene()->BeginScene();
			game->GetCurrentScene()->ClearSpawnEnemy();
			player->Reset();
			break;
		}
		}
		break;
	}
	case CREDIT_BACKGROUND:
	{
		game->SetCurrentMenu(INTRO_MENU);
		sound->Stop(WINGAME_SOUND);
		break;
	}
	}
}

void Menu::BeginTransition()
{
	Game* game = Game::GetInstance();

	if (trans == NULL)
	{
		if (transType == 1)
			trans = new Transition(game->GetBackBufferWidth(), 0, 0, 0, -0.2, 0, backgroundID);
		else
			trans = new Transition(0, game->GetBackBufferWidth(), 0, 0, 0, -0.2, backgroundID);
	}
	trans->Begin();

	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->Play(backgroundSound);
}