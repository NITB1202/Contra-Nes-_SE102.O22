#include "BossStage3.h"
#include "ObjectConfig.h"
#include "SoundManager.h"
#include "Game.h"

#define PI 3.14

void BossHandBall::SetCircleMovement(float centerX, float centerY, float r)
{
	this->centerX = centerX;
	this->centerY = centerY;
	this->r = r;
}

BossHandBall::BossHandBall()
{
	baseType = ENEMY;
	top = false;
	centerX = 0;
	centerY = 0;
	r = 0;
	width = 32;
	height = 32;
	state = 0;
	alpha = 0.785;
	damaged = false;
}

void BossHandBall::Update(DWORD dt)
{
	damaged = false;

	switch (state)
	{
	case 0:

		if (y < centerY + r * sin(0.785))
		{
			x += vx * dt;
			y += vy * dt;
		}

		break;
	case 1:

		x = centerX + r * cos(alpha);
		y = centerY + r * sin(alpha);

		break;
	}

}

void BossHandBall::Render()
{
	if (state == 3)
		AniHandler->Render(EXPLODE_EFFECT_ANIMATION, x, y);
	else
	{
		if (!top)
			AniHandler->Render(BOSS_HAND, x, y);
		else
			AniHandler->Render(BOSS_HAND_TOP, x, y);
	}
}

void BossHandBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->desObject->GetBaseType() == BULLET)
		damaged = true;
}

BossHand::BossHand()
{
	hp = 15;
	maxAlpha = 0;
	minAlpha = 0;
	vr = 0;
	gun = new Gun();
	gun->SetSpeed(0.2);
	gun->SetChargeTime(3000);
}

void BossHand::Insert()
{
	if (balls.size() < 5)
	{
		BossHandBall* ball = new BossHandBall();

		if (balls.size() == 0)
			ball->SetTop();

		ball->SetPosition(x, y);
		ball->SetSpeed(direction * 0.1, 0.1);
		ball->SetCircleMovement(x, y, ball->GetHeight() * (4 - balls.size()));
		balls.push_back(ball);
	}
	else
	{
		LPBINARYTREE objectTree = Game::GetInstance()->GetCurrentScene()->GetObjectTree();
		float alpha = direction > 0 ? PI / 4 : 3 * PI / 4;

		for (int i = 0; i < balls.size(); i++)
		{
			balls[i]->SetState(1);
			balls[i]->SetAlpha(alpha);
			objectTree->InsertObject(100 + i * direction, balls[i]);
		}

		this->state = 1;
	}
}

void BossHand::Update(DWORD dt)
{
	gun->Update(dt);

	if (IsDeleted()) return;

	if (hp <= 0)
	{
		if (!isDestroy)
		{
			isDestroy = true;
			explodeAnimationStart = GetTickCount64();
			for (int i = 0; i < balls.size(); i++)
				balls[i]->SetState(3);
			return;
		}

		if (isDestroy && GetTickCount64() - explodeAnimationStart > EXPLODE_EFFECT_DURATION)
		{
			for (int i = 0; i < balls.size(); i++)
				balls[i]->Delete();
			Delete();
		}

		return;
	}

	for (int i = 0; i < balls.size(); i++)
		if (balls[i]->IsDamaged())
		{
			Player* player = Player::GetInstance();
			int dmg = player->GetGunDMG();
			hp -= dmg;
		}

	switch (state)
	{
	case 0:
		if (insertTime == -1 || GetTickCount64() - insertTime > 220)
		{
			Insert();
			insertTime = GetTickCount64();
		}
		break;
	case 1:

		if (balls[3]->GetAlpha() > maxAlpha || balls[3]->GetAlpha() < minAlpha)
			vr = -vr;

		balls[3]->SetAlpha(balls[3]->GetAlpha() - vr);
		balls[3]->Update(dt);

		for (int i = 2; i >= 0; i--)
		{
			balls[i]->SetAlpha(balls[i + 1]->GetAlpha() + vr);
			balls[i]->Update(dt);
		}

		gun->Charge(balls[0]->GetX(), balls[0]->GetY(), SHOOT_DOWN, 5);

		break;
	}

	for (int i = 0; i < balls.size(); i++)
		balls[i]->Update(dt);
}

void BossHand::Render()
{
	gun->Render();

	if (isDeleted) return;

	for (int i = 0; i < balls.size(); i++)
		balls[i]->Render();
	
}

BossHand::~BossHand()
{
	for (int i = 0; i < balls.size(); i++)
		delete balls[i];

	delete gun;
}

BossStage3::BossStage3()
{
	baseType = ENEMY;
	hp = 30;

	appear = false;
	arriveTime = -1;

	inExplodeAnimation = false;
	explodeStart = -1;
	explodeState = 0;
	destroy=false;

	effectHandler = new AnimationHandler();

	leftHand = new BossHand();
	leftHand->SetDirection(-1);
	leftHand->SetMaxAlpha(5*PI/3);
	leftHand->SetMinAlpha(PI / 3);
	leftHand->SetVr(-0.05);

	rightHand = new BossHand();
	rightHand->SetDirection(1);
	rightHand->SetMaxAlpha(2 * PI / 3);
	rightHand->SetMinAlpha(-2 * PI / 3);
	rightHand->SetVr(0.05);

	currentState = NULL;
	gun = new Gun();
	gun->SetSpeed(0.2);
	gun->SetChargeTime(0);
}

void BossStage3::Update(DWORD dt)
{
	if (arriveTime == -1 && Camera::GetInstance()->GetBound().top == Game::GetInstance()->GetCurrentScene()->GetBossArea().top)
		arriveTime = GetTickCount64();

	if (!appear && arriveTime != - 1 &&  GetTickCount64() - arriveTime > 500)
	{
		appear = true;
		currentState = new BossAppear();
		return;
	}

	if (!appear) return;

	gun->Update(dt);
	leftHand->Update(dt);
	rightHand->Update(dt);

	if (destroy) return;

	if (inExplodeAnimation)
	{
		if (GetTickCount64() - explodeStart > EXPLODE_EFFECT_DURATION)
		{
			explodeState++;
			explodeStart = GetTickCount64();
		}

		if (explodeState == 4)
		{
			delete currentState;
			currentState = new BossDie();
		}

		if (explodeState > 6)
		{
			destroy = true;
			inExplodeAnimation = false;
		}

		return;
	}

	BossState* newState = currentState->ChangeState();

	if (currentState == dynamic_cast<BossAppear*>(currentState) && newState != NULL)
	{
		leftHand->SetState(0);
		rightHand->SetState(0);
	}

	if (newState != NULL)
	{
		delete currentState;
		currentState = newState;

		if (currentState == dynamic_cast<BossOpen*>(currentState))
		{
			gun->Charge(x + 20, y - 30, SHOOT_DOWN, 5);
			gun->Charge(x + 20, y - 30, SHOOT_DOWNLEFT, 5);
			gun->Charge(x + 20, y - 30, SHOOT_DOWNRIGHT, 5);
		}
	}
}

void BossStage3::Render()
{
	if (!appear) return;
	AnimationID = currentState->GetAnimationID();
	AniHandler->Render(AnimationID, x - 100, y);
	if (inExplodeAnimation)
	{
		switch (explodeState)
		{
			case 0:
			{
				effectHandler->Render(EXPLODE_EFFECT_ANIMATION, x + 12, y - 30);
				break;
			}
			case 1:
			{
				float start = x - EXPLODE_EFFECT_WIDTH - 15;
				for (int i = 0; i < 4; i++)
					effectHandler->Render(EXPLODE_EFFECT_ANIMATION, start + EXPLODE_EFFECT_WIDTH * i, y + EXPLODE_EFFECT_WIDTH);
				break;
			}
			default:
			{
				effectHandler->Render(EXPLODE_EFFECT_ANIMATION, x - 15, y - EXPLODE_EFFECT_WIDTH * (explodeState - 2));
				effectHandler->Render(EXPLODE_EFFECT_ANIMATION, x - 15 + EXPLODE_EFFECT_WIDTH, y - EXPLODE_EFFECT_WIDTH * (explodeState - 2));
			}
		}

	}
	gun->Render();
	leftHand->Render();
	rightHand->Render();
}

void BossStage3::SetPosition(float x, float y)
{
	GameObject::SetPosition(x, y);
	leftHand->SetPosition(x -85, y - 65);
	rightHand->SetPosition(x + 125, y - 65);
}

BossStage3::~BossStage3()
{
	delete leftHand;
	delete rightHand;
	delete currentState;
	delete gun;
}

void BossStage3::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (destroy || !appear) return;

	Player* player = Player::GetInstance();
	int dmg = player->GetGunDMG();
	hp -= dmg;

	if (hp <= 0 && !inExplodeAnimation)
	{
		inExplodeAnimation = true;
		leftHand->Destroy();
		rightHand->Destroy();
		explodeStart = GetTickCount64();
		SoundManager::GetInstance()->Play(BOSS_DESTROY);
	}
}
