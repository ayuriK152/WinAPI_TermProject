#pragma once
#include "datas.h"
#include "values.h"

class Creature {
protected:
	int originHP, currentHP;
	int animationIndex;
	bool isMoveDiagonal;
	POINT position;
	RECT sizeRect;
	CImage spriteBitmap;
	AnimationStatus animationStatus;

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

	virtual void SetSpriteBitmap(LPCTSTR fileName) = 0;

	virtual void PlayAnimation(HDC hDC) = 0;

	virtual int GetAnimationIndex() = 0;

	virtual void SetAnimationIndex(int value) = 0;

	virtual void UpdateAnimationIndex() = 0;

	virtual bool IsMoveDiagonal() = 0;

	virtual void SetMoveDiagonalCheck(bool value) = 0;

	virtual RECT GetSizeRect() = 0;
};

class Player : Creature {
private:
	POINT cameraRelativePosition;
	bool isRoll;

public:
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

	virtual void SetSpriteBitmap(LPCTSTR fileName);

	virtual void PlayAnimation(HDC hDC);

	virtual int GetAnimationIndex();

	virtual void SetAnimationIndex(int value);

	virtual void UpdateAnimationIndex();

	virtual bool IsMoveDiagonal();

	virtual void SetMoveDiagonalCheck(bool value);

	virtual RECT GetSizeRect();

	POINT GetCameraRelativePosition();

	void SetCameraRelativePosition(POINT position);

	void Roll(bool checkKeyInput[]);

	bool IsRolling();
};