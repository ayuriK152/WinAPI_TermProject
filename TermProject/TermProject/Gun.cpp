#include "Gun.h"

Gun::Gun(GunType gunType, int originBulletMount) {
	this->gunType = gunType;
	this->originBulletMount = originBulletMount;
	isFlip = false;
	isOnReload = false;
	reloadDelay = 0;
	currentBulletMount = originBulletMount;

	switch (gunType) {
		case AutoHandgun: {
			sourceBitmap.Load(L"AutoHandgun.bmp");
			maskBitmap.Load(L"AutoHandgunMask.bmp");
			reversedBitmap.Create(16, 16, 32, 0);
			for (int y = 0; y < 16; y++) {
				for (int x = 0; x < 16; x++) {
					reversedBitmap.SetPixel(x, y, sourceBitmap.GetPixel(15 - x, y));
				}
			}
			shootPosOffset = { 6, -3 };
			break;
		}
	}

	sourceBitmap.SetTransparentColor(RGB(0, 255, 0));
	reversedBitmap.SetTransparentColor(RGB(0, 255, 0));
}

Gun::~Gun() {

}

void Gun::SetAngle(double angle) {
	this->angle = angle;
}

HBITMAP hBitmap;
HDC mDC;
HBRUSH hBrush;

void Gun::Draw(HDC hDC, POINT offset, bool isRotate) {
	if (isRotate) {
		hBitmap = CreateCompatibleBitmap(hDC, 1920, 1080);
		mDC = CreateCompatibleDC(hDC);
		SelectObject(mDC, hBitmap);
		Rotate(offset);

		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(mDC, hBrush);

		Rectangle(mDC, 0, 0, 1920, 1080);
		sourceBitmap.PlgBlt(mDC, renderPoints, 0, 0, sourceBitmap.GetWidth(), sourceBitmap.GetHeight());
		TransparentBlt(hDC, 0, 0, 1920, 1080, mDC, 0, 0, 1920, 1080, RGB(0, 255, 0));

		DeleteObject(hBrush);
		DeleteObject(hBitmap);
		DeleteDC(mDC);
	}
	else {
		if (sinf(-angle) < 0) {
			reversedBitmap.Draw(hDC, offset.x - 56, offset.y - 24, 48, 48);
		}
		else {
			sourceBitmap.Draw(hDC, offset.x + 8, offset.y - 24, 48, 48);
		}
	}
}

Bullet* Gun::Shoot(POINT shooterPosition, int decreaseMount, bool isHostile) {
	currentBulletMount -= decreaseMount;
	if (isHostile) {
		return new Bullet({ shootPos.x + shooterPosition.x, shootPos.y + shooterPosition.y }, { 45, 45 }, 15, angle, isHostile);
	}
	return new Bullet({ shootPos.x + shooterPosition.x, shootPos.y + shooterPosition.y }, { 45, 45 }, 25, angle, isHostile);
}

int Gun::GetCurrentBulletMount() {
	return currentBulletMount;
}

int Gun::GetOriginBulletMount() {
	return originBulletMount;
}

int Gun::GetCurrentReloadStatus() {
	return reloadDelay;
}

GunType Gun::GetGunType() {
	return gunType;
}

void Gun::IncreaseReloadCount() {
	if (reloadDelay < PLAYER_GUN_RELOAD_TIME) {
		reloadDelay += 1;
	}
	else {
		isOnReload = false;
		currentBulletMount = originBulletMount;
		reloadDelay = 0;
	}
}

bool Gun::IsGunOnReLoad() {
	return isOnReload;
}

bool Gun::IsGunCanReload() {
	if (currentBulletMount < originBulletMount)
		return true;
	return false;
}

void Gun::Reload() {
	if (!isOnReload)
		isOnReload = true;
}

void Gun::Rotate(POINT offset) {
	float sin = sinf(-angle);
	float cos = cosf(-angle);
	POINT originPos = { -sourceBitmap.GetWidth() / 2 * 3, sourceBitmap.GetHeight() / 2 * 3 };
	if (sin < 0) {
		shootPos.x = (LONG)((shootPosOffset.x * cos + shootPosOffset.y * sin)) * 3;
		shootPos.y = (LONG)((-shootPosOffset.y * cos + shootPosOffset.x * sin)) * 3;
		originPos.x = -originPos.x;
	}
	else {
		shootPos.x = (LONG)((shootPosOffset.x * cos - shootPosOffset.y * sin));
		shootPos.y = (LONG)((shootPosOffset.y * cos + shootPosOffset.x * sin));
	}

	// Upper-Left
	renderPoints[0].x = (LONG)((originPos.x * cos - originPos.y * sin) + offset.x);
	renderPoints[0].y = (LONG)((originPos.y * cos + originPos.x * sin) + offset.y);
	// Upper-Right
	renderPoints[2].x = (LONG)((-originPos.x * cos - originPos.y * sin) + offset.x);
	renderPoints[2].y = (LONG)((originPos.y * cos - originPos.x * sin) + offset.y);
	// Lower-Left
	renderPoints[1].x = (LONG)((originPos.x * cos + originPos.y * sin) + offset.x);
	renderPoints[1].y = (LONG)((-originPos.y * cos + originPos.x * sin) + offset.y);

}