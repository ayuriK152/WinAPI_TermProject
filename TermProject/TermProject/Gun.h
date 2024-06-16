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
	bool isOnReload;
	double angle;
	int originBulletMount;
	int currentBulletMount;
	int reloadDelay;

public:
	Gun(GunType gunType, int originBulletMount);

	~Gun();

	void SetAngle(double angle);

	void Draw(HDC hDC, POINT offset);

	Bullet* Shoot(POINT shooterPosition, int decreaseMount, bool isHostile);

	int GetCurrentBulletMount();

	int GetCurrentReloadStatus();

	void IncreaseReloadCount();

	bool IsGunOnReLoad();
	
	bool IsGunCanReload();

	void Reload();

	void Rotate(POINT centerPos);
};