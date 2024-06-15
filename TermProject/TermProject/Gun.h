#pragma once
#include <atlimage.h>
#include "Bullet.h"
#include "datas.h"
#include "values.h"

class Gun {
private:
	GunType gunType;
	CImage sourceBitmap;
	CImage maskBitmap;
	POINT shootPosOffset, shootPos;
	POINT renderPoints[3];
	bool isFlip;
	double angle;
	int originBulletMount;
	int currentBulletMount;

public:
	Gun(GunType gunType, int originBulletMount);

	~Gun();

	void SetAngle(double angle);

	void Draw(HDC hDC, POINT offset);

	Bullet* Shoot(POINT shooterPosition, int decreaseMount);

	void Reload();

	void Rotate(POINT centerPos);
};