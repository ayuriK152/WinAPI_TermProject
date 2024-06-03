#pragma once
#include <atlImage.h>
#include "creatures.h"

Player::Player() {
	hp = 6;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { 0, 0 };
	animationStatus = IdleDown;
	spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
}

Player::Player(int x, int y) {
	hp = 6;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { x, y };
	animationStatus = IdleDown;
	spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
}

Player::~Player() {
	DeleteObject(spriteBitmap);
}

int Player::GetHp() { return hp; }

void Player::SetHp(int value) { hp = value; }

POINT Player::GetPosition() { return position; }

void Player::SetPosition(int x, int y) { position = { x, y }; }

void Player::Move(int x, int y) { position = { position.x + x, position.y + y }; }

AnimationStatus Player::GetMoveStatus() { return animationStatus; }

void Player::SetMoveStatus(AnimationStatus status) { animationStatus = status; }

void Player::SetSpriteBitmap(LPCTSTR fileName) { spriteBitmap.Load(fileName); }

void Player::PlayAnimation(HDC hDC) {
	switch (animationStatus) {
		case IdleUp: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_IDLE_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_UP.y, 25, 25);
			break;
		}
		case IdleDown: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_IDLE_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_DOWN.y, 25, 25);
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
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case IdleRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_IDLE_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_RIGHT.y, 25, 25);
			break;
		}
		case IdleUpLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT.y + y));
				}
			}
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case IdleUpRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT.y, 25, 25);
			break;
		}
		case MoveUp: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_MOVE_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_UP.y, 25, 25);
			break;
		}
		case MoveDown: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_MOVE_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_DOWN.y, 25, 25);
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
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case MoveRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_MOVE_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_RIGHT.y, 25, 25);
			break;
		}
		case MoveUpLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT.y + y));
				}
			}
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case MoveUpRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT.y, 25, 25);
			break;
		}
		case RollUp: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_ROLL_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_UP.y, 25, 25);
			break;
		}
		case RollDown: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_ROLL_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_DOWN.y, 25, 25);
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
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case RollRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.y, 25, 25);
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
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case RollUpRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT.y, 25, 25);
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
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case RollDownRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.y, 25, 25);
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