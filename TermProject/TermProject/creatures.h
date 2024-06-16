#pragma once
#include <vector>
#include "datas.h"
#include "values.h"
#include "Gun.h"
#include "Utils.h"

using namespace std;

static CImage bulletJuniorSpriteBmp;
static POINT cameraRelativeOffset;
static CImage playerSpriteBmp;

class Creature {
protected:
	int originHP, currentHP;
	int animationIndex;
	int gunDelay;
	double angle;
	bool isMoveDiagonal;
	bool isGunOnDelay;
	POINT position;
	RECT hitboxRect;
	AnimationStatus animationStatus;
	vector<Gun*> guns;
	POINT gunPosition;

public:
	virtual int GetOriginHp() = 0;

	virtual int GetCurrentHp() = 0;

	virtual void SetCurrentHp(int value) = 0;

	virtual void GetDamge(int value) = 0;

	virtual void GetHeal(int value) = 0;

	virtual POINT GetPosition() = 0;

	virtual void SetPosition(int x, int y) = 0;

	virtual void Move(int x, int y) = 0;

	virtual AnimationStatus GetMoveStatus() = 0;

	virtual void SetMoveStatus(AnimationStatus status) = 0;

	virtual void PlayAnimation(HDC hDC) = 0;

	virtual int GetAnimationIndex() = 0;

	virtual void SetAnimationIndex(int value) = 0;

	virtual void UpdateAnimationIndex() = 0;

	virtual bool IsMoveDiagonal() = 0;

	virtual void SetMoveDiagonalCheck(bool value) = 0;

	virtual RECT GetHitboxRect() = 0;

	virtual Bullet* FireGun() = 0;
};

class Player : Creature {
private:
	CImage reloadBar;
	CImage leftAnimationBmp;
	POINT cameraRelativePosition;
	bool isRoll;
	int currentGunIdx;

public:
	bool checkMovableDirection[4];

	Player();

	Player(int x, int y);

	~Player();

	virtual int GetOriginHp();

	virtual int GetCurrentHp();

	virtual void SetCurrentHp(int value);

	virtual void GetDamge(int value);

	virtual void GetHeal(int value);

	virtual POINT GetPosition();

	virtual void SetPosition(int x, int y);

	virtual void Move(int x, int y);

	virtual AnimationStatus GetMoveStatus();

	virtual void SetMoveStatus(AnimationStatus status);

	virtual void PlayAnimation(HDC hDC);

	virtual int GetAnimationIndex();

	virtual void SetAnimationIndex(int value);

	virtual void UpdateAnimationIndex();

	virtual bool IsMoveDiagonal();

	virtual void SetMoveDiagonalCheck(bool value);

	virtual RECT GetHitboxRect();

	virtual Bullet* FireGun();

	void AnimationRefresh(bool checkKeyInput[], POINT mousePoint);

	void PositionRefresh(bool checkKeyInput[], bool checkMovableDirection[]);

	POINT GetCameraRelativePosition();

	void SetCameraRelativePosition(POINT position, RECT rt);

	void SetCameraRelativeOffset();

	void Roll(bool checkKeyInput[]);

	bool IsRolling();

	int GetCurrentGunBulletAmount();

	int GetCurrentGunOriginBulletAmount();

	GunType GetCurrentGunType();

	void ReloadCurrentGun();

	bool IsCurrentGunCanReload();

	bool IsCurrentGunOnReload();
};

class Enemy : Creature {
private:
	EnemyType enemyType;
	CImage moveRightBmp;
	POINT destPosition;
	int distanceToPlayer;

public:
	bool checkMovableDirection[4];
	bool isActivate;
	int mapIndex;

	Enemy(EnemyType enemyType, int mapIndex);

	Enemy(EnemyType enemyType, int x, int y, int mapIndex);

	~Enemy();

	virtual int GetOriginHp();

	virtual int GetCurrentHp();

	virtual void SetCurrentHp(int value);

	virtual void GetDamge(int value);

	virtual void GetHeal(int value);

	virtual POINT GetPosition();

	virtual void SetPosition(int x, int y);

	virtual void Move(int x, int y);

	virtual AnimationStatus GetMoveStatus();

	virtual void SetMoveStatus(AnimationStatus status);

	virtual void PlayAnimation(HDC hDC);

	virtual int GetAnimationIndex();

	virtual void SetAnimationIndex(int value);

	virtual void UpdateAnimationIndex();

	virtual bool IsMoveDiagonal();

	virtual void SetMoveDiagonalCheck(bool value);

	virtual RECT GetHitboxRect();

	virtual Bullet* FireGun();

	void AI();

	void SetDestination(POINT playerPosition);

	bool IsCanFire();
};