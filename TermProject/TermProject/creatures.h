#pragma once
#include "datas.h"

class Creature {
protected:
	int hp;
	POINT position;
	HBITMAP spriteBitmap;
	MoveStatus moveStatus;

public:
	int GetHp() {
		return hp;
	}

	void SetHp(int value) {
		hp = value;
	}

	POINT GetPosition() {
		return position;
	}

	void SetPosition(int x, int y) {
		position = { x, y };
	}

	void Move(int x, int y) {
		position = { position.x + x, position.y + y };
	}

	MoveStatus GetMoveStatus() {
		return moveStatus;
	}

	void SetMoveStatus(MoveStatus status) {
		moveStatus = status;
	}

	void SetSpriteBitmap(HBITMAP spriteBitmap) {
		this->spriteBitmap = spriteBitmap;
	}
};

class Player : Creature {
public:
	Player() {
		hp = 6;
		position = { 0, 0 };
		moveStatus = None;
	}

	Player(int x, int y) {
		hp = 6;
		position = { x, y };
		moveStatus = None;
	}

	~Player() {

	}
};