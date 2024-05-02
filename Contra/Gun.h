#pragma once
#include "Bullet.h"
#include <vector>
using namespace std;

class Gun
{
private:
	vector<Bullet*> bullets;
	DWORD lastShootTime = -1;
	int chargeTime = 80;
	float spd;
public:
	Gun(float spd) { this->spd = spd; }
	void Charge(float bulletX, float bulletY, int direction, int bulletType = 1);
	void SetChargeTime(int chargeTime) { this->chargeTime = chargeTime; }
	void SetSpeed(float spd) { this->spd = spd;}
	void Update(DWORD dt);
	void Render();
};

