#pragma once
#include "Bullet.h"
#include <vector>
using namespace std;

class Gun
{
private:
	vector<Bullet*> bullets;
	ULONGLONG lastShootTime = -1;
	int chargeTime = 80;
	int bulletType = 1;
	float spd = 0.1;
	int dmg = 1;
public:
	void Charge(float bulletX, float bulletY, int direction, int bulletType = 1);
	void SetChargeTime(int chargeTime) { this->chargeTime = chargeTime; }
	void SetSpeed(float spd) { this->spd = spd;}
	void SetDMG(int dmg) { this->dmg = dmg; }
	int GetDMG() { return this->dmg; }
	void SetBulletType(int bulletType) { this->bulletType = bulletType; }
	int GetBulletType() { return this->bulletType; }

	void Update(DWORD dt);
	void Render();
};

