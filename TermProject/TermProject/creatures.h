#pragma once
#include <atlImage.h>
#include "datas.h"

class Creature {
protected:
	int hp;
	int animationIndex;
	POINT position;
	CImage spriteBitmap;
	AnimationStatus animationStatus;

public:
	virtual int GetHp() = 0;

	virtual void SetHp(int value) = 0;

	virtual POINT GetPosition() = 0;

	virtual void SetPosition(int x, int y) = 0;

	virtual void Move(int x, int y) = 0;

	virtual AnimationStatus GetMoveStatus() = 0;

	virtual void SetMoveStatus(AnimationStatus status) = 0;

	virtual void SetSpriteBitmap(LPCTSTR fileName) = 0;

	virtual void PlayAnimation(HDC hDC) = 0;

	virtual void UpdateAnimationIndex() = 0;
};

class Player : Creature {
public:
	Player() {
		hp = 6;
		animationIndex = 0;
		position = { 0, 0 };
		animationStatus = Idle;
		spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
	}

	Player(int x, int y) {
		hp = 6;
		animationIndex = 0;
		position = { x, y };
		animationStatus = Idle;
		spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
	}

	~Player() {
		DeleteObject(spriteBitmap);
	}

	virtual int GetHp() { return hp; }

	virtual void SetHp(int value) { hp = value; }

	virtual POINT GetPosition() { return position; }

	virtual void SetPosition(int x, int y) { position = { x, y }; }

	virtual void Move(int x, int y) { position = { position.x + x, position.y + y }; }

	virtual AnimationStatus GetMoveStatus() { return animationStatus; }

	virtual void SetMoveStatus(AnimationStatus status) { animationStatus = status; }

	virtual void SetSpriteBitmap(LPCTSTR fileName) override { spriteBitmap.Load(fileName); }

	virtual void PlayAnimation(HDC hDC) {
		switch (animationStatus) {
			case Idle: {
				spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, 25 * animationIndex, 0, 25, 25);
				break;
			}
		}
	}

	virtual void UpdateAnimationIndex() {
		switch (animationStatus) {
			case Idle: {
				animationIndex = (animationIndex + 1) % 6;
				break;
			}
		}
	}
};