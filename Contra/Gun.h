#pragma once
#include "Bullet.h"
#include <vector>

using namespace std;

#define MAX_CAP 5

class Gun
{
private:
	vector<Bullet*> bullets;
	ULONGLONG lastShootTime = -1;
	ULONGLONG reloadStart = -1;

	int chargeTime = 80;
	int bulletType = 1;
	float spd = 0.1;
	int dmg = 1;
	int cap = MAX_CAP;
	int reloadTime = 0;
	bool canReload = true;

public:
	void Charge(float bulletX, float bulletY, int direction, int bulletType = 1);
	void SetChargeTime(int chargeTime) { this->chargeTime = chargeTime; }
	void SetSpeed(float spd) { this->spd = spd;}
	void SetDMG(int dmg) { this->dmg = dmg; }
	int GetDMG() { return this->dmg; }
	void SetBulletType(int bulletType) { this->bulletType = bulletType; }
	int GetBulletType() { return this->bulletType; }
	void SetReloadTime(int t) { reloadTime = t; }
	void NoReload() { canReload = false; }

	void Update(DWORD dt);
	void Render();
};

