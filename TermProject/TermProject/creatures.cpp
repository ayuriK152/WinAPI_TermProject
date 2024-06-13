#pragma once
#include <atlImage.h>
#include "creatures.h"

Player::Player() {
	originHP = 8;
	currentHP = 8;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { 0, 0 };
	hitboxRect = {
		position.x - (PLAYER_CHARACTER_SIZE / 2 - 14), 
		position.y - PLAYER_CHARACTER_SIZE / 2, 
		position.x + (PLAYER_CHARACTER_SIZE / 2 - 14),
		position.y + PLAYER_CHARACTER_SIZE / 2 
	};
	animationStatus = IdleDown;
	guns.push_back(new Gun(AutoHandgun, 6));
	spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
}

Player::Player(int x, int y) {
	originHP = 8;
	currentHP = 8;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { x, y };
	hitboxRect = {
		position.x - PLAYER_CHARACTER_SIZE / 2,
		position.y - PLAYER_CHARACTER_SIZE / 2,
		position.x + PLAYER_CHARACTER_SIZE / 2,
		position.y + PLAYER_CHARACTER_SIZE / 2
	};
	animationStatus = IdleDown;
	guns.push_back(new Gun(AutoHandgun, 6));
	spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
}

Player::~Player() {
	DeleteObject(spriteBitmap);
}

int Player::GetOriginHp() { return originHP; }

int Player::GetCurrentHp() { return currentHP; }

void Player::SetCurrentHp(int value) {
	currentHP = value;
}

void Player::GetDamge(int value) {
	currentHP -= value;
}

void Player::GetHeal(int value) {
	currentHP += value;
}

POINT Player::GetPosition() { return position; }

void Player::SetPosition(int x, int y) { position = { x, y }; }

void Player::Move(int x, int y) {
	position = { position.x + x, position.y + y };
	hitboxRect = {
		position.x - PLAYER_CHARACTER_SIZE / 2,
		position.y - PLAYER_CHARACTER_SIZE / 2,
		position.x + PLAYER_CHARACTER_SIZE / 2,
		position.y + PLAYER_CHARACTER_SIZE / 2
	};
}

AnimationStatus Player::GetMoveStatus() { return animationStatus; }

void Player::SetMoveStatus(AnimationStatus status) { animationStatus = status; }

void Player::SetSpriteBitmap(LPCTSTR fileName) { spriteBitmap.Load(fileName); }

void Player::PlayAnimation(HDC hDC) {
	switch (animationStatus) {
		case IdleUp: {
			guns[0]->Draw(hDC, gunPosition);
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_UP.y, 25, 25);
			break;
		}
		case IdleDown: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_DOWN.y, 25, 25);
			guns[0]->Draw(hDC, gunPosition);
			break;
		}
		case IdleLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_IDLE_LEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_IDLE_LEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			guns[0]->Draw(hDC, gunPosition);
			DeleteObject(temp);
			break;
		}
		case IdleRight: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_RIGHT.y, 25, 25);
			guns[0]->Draw(hDC, gunPosition);
			break;
		}
		case IdleUpLeft: {
			guns[0]->Draw(hDC, gunPosition);
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case IdleUpRight: {
			guns[0]->Draw(hDC, gunPosition);
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT.y, 25, 25);
			break;
		}
		case MoveUp: {
			guns[0]->Draw(hDC, gunPosition);
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_UP.y, 25, 25);
			break;
		}
		case MoveDown: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_DOWN.y, 25, 25);
			guns[0]->Draw(hDC, gunPosition);
			break;
		}
		case MoveLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_MOVE_LEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_MOVE_LEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			guns[0]->Draw(hDC, gunPosition);
			DeleteObject(temp);
			break;
		}
		case MoveRight: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_RIGHT.y, 25, 25);
			guns[0]->Draw(hDC, gunPosition);
			break;
		}
		case MoveUpLeft: {
			guns[0]->Draw(hDC, gunPosition);
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case MoveUpRight: {
			guns[0]->Draw(hDC, gunPosition);
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT.y, 25, 25);
			break;
		}
		case RollUp: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_UP.y, 25, 25);
			break;
		}
		case RollDown: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_DOWN.y, 25, 25);
			break;
		}
		case RollLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_ROLL_LEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_ROLL_LEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case RollRight: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.y, 25, 25);
			break;
		}
		case RollUpLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_ROLL_UPLEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_ROLL_UPLEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case RollUpRight: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT.y, 25, 25);
			break;
		}
		case RollDownLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_ROLL_LEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_ROLL_LEFT.y + y));
				}
			}
			temp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case RollDownRight: {
			spriteBitmap.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.y, 25, 25);
			break;
		}
	}
}

int Player::GetAnimationIndex() {
	return animationIndex;
}

void Player::SetAnimationIndex(int value) {
	animationIndex = value;
}

void Player::UpdateAnimationIndex() {
	switch (animationStatus) {
		case IdleLeft: {
			animationIndex = (animationIndex + 1) % 4;
			break;
		}
		case IdleRight: {
			animationIndex = (animationIndex + 1) % 4;
			break;
		}
		case IdleUpLeft: {
			animationIndex = (animationIndex + 1) % 4;
			break;
		}
		case IdleUpRight: {
			animationIndex = (animationIndex + 1) % 4;
			break;
		}
		case RollUp: {
			if (animationIndex >= 8) {
				animationStatus = MoveUp;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollDown: {
			if (animationIndex >= 8) {
			animationStatus = MoveDown;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollLeft: {
			if (animationIndex >= 8) {
				animationStatus = MoveLeft;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollRight: {
			if (animationIndex >= 8) {
				animationStatus = MoveRight;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollUpLeft: {
			if (animationIndex >= 8) {
				animationStatus = MoveUpLeft;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollUpRight: {
			if (animationIndex >= 8) {
				animationStatus = MoveUpRight;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollDownLeft: {
			if (animationIndex >= 8) {
				animationStatus = MoveLeft;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		case RollDownRight: {
			if (animationIndex >= 8) {
				animationStatus = MoveRight;
				animationIndex = 0;
				isRoll = false;
			}
			animationIndex = animationIndex + 1;
			break;
		}
		default: {
			animationIndex = (animationIndex + 1) % 6;
			break;
		}
	}
}

bool Player::IsMoveDiagonal() {
	return isMoveDiagonal;
}

void Player::SetMoveDiagonalCheck(bool value) {
	isMoveDiagonal = value;
}

RECT Player::GetHitboxRect() {
	return hitboxRect;
}

Bullet* Player::FireGun() {
	return guns[0]->Shoot({ (gunPosition.x - cameraRelativePosition.x) + position.x, (gunPosition.y - cameraRelativePosition.y) + position.y });
}

POINT Player::GetCameraRelativePosition() {
	return cameraRelativePosition;
}

void Player::SetCameraRelativePosition(POINT mousePoint, RECT rt) {
	angle = atan2(cameraRelativePosition.x - mousePoint.x, cameraRelativePosition.y - mousePoint.y);
	cameraRelativePosition = { rt.right / 2 - (mousePoint.x - rt.right / 2) * 3 / 7, rt.bottom / 2 - (mousePoint.y - rt.bottom / 2) * 2 / 3 };
	gunPosition = { -(long)(sin(angle) * CREATURE_GUN_HOLDING_DISTANCE) + cameraRelativePosition.x, -(long)(cos(angle) * CREATURE_GUN_HOLDING_DISTANCE) + cameraRelativePosition.y };
	guns[0]->SetAngle(angle);
}

void Player::Roll(bool checkKeyInput[]) {
	if (checkKeyInput[0]) {
		if (checkKeyInput[2])
			animationStatus = RollUpLeft;
		else if (checkKeyInput[3])
			animationStatus = RollUpRight;
		else
			animationStatus = RollUp;
	}
	else if (checkKeyInput[1]) {
		if (checkKeyInput[2])
			animationStatus = RollDownLeft;
		else if (checkKeyInput[3])
			animationStatus = RollDownRight;
		else
			animationStatus = RollDown;
	}
	else if (checkKeyInput[2]) {
		animationStatus = RollLeft;
	}
	else if (checkKeyInput[3]) {
		animationStatus = RollRight;
	}
	else {
		return;
	}
	SetAnimationIndex(0);
	isRoll = true;
}

bool Player::IsRolling() {
	return isRoll;
}

Enemy::Enemy(EnemyType enemyType) {
	switch (enemyType) {
		case BulletJunior: {
			originHP = ENEMY_HP_BULLETJUNIOR;
			break;
		}
		case ShotgunRed: {
			originHP = ENEMY_HP_SHOTGUNRED;
			break;
		}
		case ShotgunBlue: {
			originHP = ENEMY_HP_SHOTGUNBLUE;
			break;
		}
	}
	currentHP = originHP;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { 0, 0 };
	hitboxRect = {
		position.x - (PLAYER_CHARACTER_SIZE / 2 - 14),
		position.y - PLAYER_CHARACTER_SIZE / 2,
		position.x + (PLAYER_CHARACTER_SIZE / 2 - 14),
		position.y + PLAYER_CHARACTER_SIZE / 2
	};
	animationStatus = IdleDown;
	spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
}

Enemy::Enemy(EnemyType enemyType, int x, int y) {

}

Enemy::~Enemy() {

}

int Enemy::GetOriginHp() { return originHP; }

int Enemy::GetCurrentHp() { return currentHP; }

void Enemy::SetCurrentHp(int value) {
	currentHP = value;
}

void Enemy::GetDamge(int value) {
	currentHP -= value;
}

void Enemy::GetHeal(int value) {
	currentHP += value;
}

POINT Enemy::GetPosition() { return position; }

void Enemy::SetPosition(int x, int y) { position = { x, y }; }

void Enemy::Move(int x, int y) {
	position = { position.x + x, position.y + y };
	hitboxRect = {
		position.x - PLAYER_CHARACTER_SIZE / 2,
		position.y - PLAYER_CHARACTER_SIZE / 2,
		position.x + PLAYER_CHARACTER_SIZE / 2,
		position.y + PLAYER_CHARACTER_SIZE / 2
	};
}

AnimationStatus Enemy::GetMoveStatus() { return animationStatus; }

void Enemy::SetMoveStatus(AnimationStatus status) { animationStatus = status; }

void Enemy::SetSpriteBitmap(LPCTSTR fileName) { spriteBitmap.Load(fileName); }


void Enemy::PlayAnimation(HDC hDC) {

}

int Enemy::GetAnimationIndex() {
	return animationIndex;
}

void Enemy::SetAnimationIndex(int value) {
	animationIndex = value;
}

void Enemy::UpdateAnimationIndex() {

}

bool Enemy::IsMoveDiagonal() {
	return isMoveDiagonal;
}

void Enemy::SetMoveDiagonalCheck(bool value) {
	isMoveDiagonal = value;
}
RECT Enemy::GetHitboxRect() {
	return hitboxRect;
}

Bullet* Enemy::FireGun() {
	return guns[0]->Shoot(position);
}