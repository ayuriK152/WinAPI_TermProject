#pragma once
#include <atlImage.h>
#include "creatures.h"

Player::Player() {
	originHP = 8;
	currentHP = 8;
	animationIndex = 0;
	isMoveDiagonal = false;
	isRoll = false;
	isGunOnDelay = false;
	position = { 0, 0 };
	hitboxRect = {
		position.x - (PLAYER_CHARACTER_SIZE / 2 - 14), 
		position.y - PLAYER_CHARACTER_SIZE / 2, 
		position.x + (PLAYER_CHARACTER_SIZE / 2 - 14),
		position.y + PLAYER_CHARACTER_SIZE / 2 
	};
	if (playerSpriteBmp.IsNull())
		playerSpriteBmp.Load(L"The Pilot.bmp");
	playerSpriteBmp.SetTransparentColor(RGB(144, 187, 187));
	leftAnimationBmp.Create(300, 150, 32, 0);
	leftAnimationBmp.SetTransparentColor(RGB(144, 187, 187));
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 100; x++) {
			leftAnimationBmp.SetPixel(x, y, playerSpriteBmp.GetPixel(150 + (x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_IDLE_LEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 100; x++) {
			leftAnimationBmp.SetPixel(x, y + 25, playerSpriteBmp.GetPixel(150 + (x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 300; x++) {
			leftAnimationBmp.SetPixel(x, y + 50, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_MOVE_LEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 300; x++) {
			leftAnimationBmp.SetPixel(x, y + 75, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 225; x++) {
			leftAnimationBmp.SetPixel(x, y + 100, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_ROLL_LEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 225; x++) {
			leftAnimationBmp.SetPixel(x, y + 125, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_ROLL_UPLEFT.y + y));
		}
	}
	animationStatus = IdleDown;
	guns.push_back(new Gun(AutoHandgun, 6));
	currentGunIdx = 0;
	playerSpriteBmp.SetTransparentColor(RGB(144, 187, 187));
	if (reloadBar.IsNull())
		reloadBar.Load(L"ReloadBar.bmp");
}

Player::Player(int x, int y) {
	originHP = 8;
	currentHP = 8;
	animationIndex = 0;
	isMoveDiagonal = false;
	isRoll = false;
	isGunOnDelay = false;
	position = { x, y };
	hitboxRect = {
		position.x - PLAYER_CHARACTER_SIZE / 2,
		position.y - PLAYER_CHARACTER_SIZE / 2,
		position.x + PLAYER_CHARACTER_SIZE / 2,
		position.y + PLAYER_CHARACTER_SIZE / 2
	};
	if (playerSpriteBmp.IsNull())
		playerSpriteBmp.Load(L"The Pilot.bmp");
	playerSpriteBmp.SetTransparentColor(RGB(144, 187, 187));
	leftAnimationBmp.Create(300, 150, 32, 0);
	leftAnimationBmp.SetTransparentColor(RGB(144, 187, 187));
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 100; x++) {
			leftAnimationBmp.SetPixel(x, y, playerSpriteBmp.GetPixel(150 + (x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_IDLE_LEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 100; x++) {
			leftAnimationBmp.SetPixel(x, y + 25, playerSpriteBmp.GetPixel(150 + (x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_IDLE_UPLEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 300; x++) {
			leftAnimationBmp.SetPixel(x, y + 50, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_MOVE_LEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 300; x++) {
			leftAnimationBmp.SetPixel(x, y + 75, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_MOVE_UPLEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 225; x++) {
			leftAnimationBmp.SetPixel(x, y + 100, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_ROLL_LEFT.y + y));
		}
	}
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 225; x++) {
			leftAnimationBmp.SetPixel(x, y + 125, playerSpriteBmp.GetPixel((x / 25 + 1) * 25 - 1 - x % 25, ANIMATION_OFFSET_PLAYER_ROLL_UPLEFT.y + y));
		}
	}
	animationStatus = IdleDown;
	guns.push_back(new Gun(AutoHandgun, 6));
	currentGunIdx = 0;
	if (reloadBar.IsNull())
		reloadBar.Load(L"ReloadBar.bmp");
}

Player::~Player() {
	DeleteObject(playerSpriteBmp);
}

int Player::GetOriginHp() { return originHP; }

int Player::GetCurrentHp() { return currentHP; }

void Player::SetCurrentHp(int value) {
	currentHP = value;
}

void Player::GetDamge(int value) {
	currentHP -= value;
	if (currentHP <= 0) {
		animationStatus = Death;
	}
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

void Player::PlayAnimation(HDC hDC) {
	switch (animationStatus) {
		case IdleUp: {
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_UP.y, 25, 25);
			break;
		}

		case IdleDown: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_DOWN.y, 25, 25);
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			break;
		}

		case IdleLeft: {
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 0, 25, 25);
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			break;
		}

		case IdleRight: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_RIGHT.y, 25, 25);
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			break;
		}

		case IdleUpLeft: {
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 25, 25, 25);
			break;
		}

		case IdleUpRight: {
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_IDLE_UPRIGHT.y, 25, 25);
			break;
		}

		case MoveUp: {
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_UP.y, 25, 25);
			break;
		}

		case MoveDown: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_DOWN.y, 25, 25);
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			break;
		}

		case MoveLeft: {
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 50, 25, 25);
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			break;
		}

		case MoveRight: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_RIGHT.y, 25, 25);
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			break;
		}

		case MoveUpLeft: {
			guns[currentGunIdx]->Draw(hDC, gunPosition, true); leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 75, 25, 25);
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 75, 25, 25);
			break;
		}

		case MoveUpRight: {
			guns[currentGunIdx]->Draw(hDC, gunPosition, true);
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_MOVE_UPRIGHT.y, 25, 25);
			break;
		}

		case RollUp: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_UP.y, 25, 25);
			break;
		}

		case RollDown: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_DOWN.y, 25, 25);
			break;
		}

		case RollLeft: {
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 100, 25, 25);
			break;
		}

		case RollRight: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.y, 25, 25);
			break;
		}

		case RollUpLeft: {
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 125, 25, 25);
			break;
		}

		case RollUpRight: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_UPRIGHT.y, 25, 25);
			break;
		}

		case RollDownLeft: {
			leftAnimationBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, 25 * animationIndex, 100, 25, 25);
			break;
		}

		case RollDownRight: {
			playerSpriteBmp.Draw(hDC, cameraRelativePosition.x - PLAYER_CHARACTER_SIZE / 2, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2, PLAYER_CHARACTER_SIZE, PLAYER_CHARACTER_SIZE, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_ROLL_RIGHT.y, 25, 25);
			break;
		}
	}

	if (guns[currentGunIdx]->IsGunOnReLoad()) {
		guns[currentGunIdx]->IncreaseReloadCount();
		if (guns[currentGunIdx]->GetCurrentReloadStatus() / 2 >= 1) {
			reloadBar.Draw(hDC, cameraRelativePosition.x - 41, cameraRelativePosition.y - PLAYER_CHARACTER_SIZE / 2 - 29, guns[currentGunIdx]->GetCurrentReloadStatus() / 2 * 3, 21, 0, 0, guns[currentGunIdx]->GetCurrentReloadStatus() / 2, 7);
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
	return guns[currentGunIdx]->Shoot({ (gunPosition.x - cameraRelativePosition.x) + position.x, (gunPosition.y - cameraRelativePosition.y) + position.y }, 1, false);
}

void Player::AnimationRefresh(bool checkKeyInput[], POINT mousePoint) {
	AnimationStatus pastStatus = GetMoveStatus();
	double tanValue = TanByPoint(GetCameraRelativePosition(), mousePoint);

	if (mousePoint.x < GetCameraRelativePosition().x && (tanValue >= TAN_22_5 && tanValue <= TAN_67_5)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			SetMoveStatus(IdleUpLeft);
		else
			SetMoveStatus(MoveUpLeft);
	}
	else if (mousePoint.x > GetCameraRelativePosition().x && (tanValue <= -TAN_22_5 && tanValue >= -TAN_67_5)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			SetMoveStatus(IdleUpRight);
		else
			SetMoveStatus(MoveUpRight);
	}
	else if (mousePoint.x < GetCameraRelativePosition().x && ((tanValue <= TAN_22_5 && tanValue >= 0) || tanValue >= -TAN_67_5 && tanValue <= 0)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			SetMoveStatus(IdleLeft);
		else
			SetMoveStatus(MoveLeft);
	}
	else if (mousePoint.x > GetCameraRelativePosition().x && ((tanValue >= -TAN_22_5 && tanValue <= 0) || tanValue <= TAN_67_5 && tanValue >= 0)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			SetMoveStatus(IdleRight);
		else
			SetMoveStatus(MoveRight);
	}
	else if (mousePoint.y < GetCameraRelativePosition().y) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			SetMoveStatus(IdleUp);
		else
			SetMoveStatus(MoveUp);
	}
	else if (mousePoint.y > GetCameraRelativePosition().y) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			SetMoveStatus(IdleDown);
		else
			SetMoveStatus(MoveDown);
	}
	if (pastStatus != GetMoveStatus()) {
		SetAnimationIndex(0);
	}
	UpdateAnimationIndex();
}

void Player::PositionRefresh(bool checkKeyInput[], bool checkMovableDirection[]) {
	if (IsRolling()) {
		int moveSpeed = 0;
		if (GetAnimationIndex() > 6)
			moveSpeed = IsMoveDiagonal() ? PLAYER_ROLL_END_SPEED_DIAGONAL : PLAYER_ROLL_END_SPEED;
		else if (GetAnimationIndex() > 4)
			moveSpeed = IsMoveDiagonal() ? PLAYER_ROLL_ING_SPEED_DIAGONAL : PLAYER_ROLL_ING_SPEED;
		else
			moveSpeed = IsMoveDiagonal() ? PLAYER_ROLL_START_SPEED_DIAGONAL : PLAYER_ROLL_START_SPEED;

		switch (GetMoveStatus()) {
			case RollUp: {
				if (!checkMovableDirection[0])
					Move(0, -moveSpeed);
				break;
			}

			case RollDown: {
				if (!checkMovableDirection[1])
					Move(0, moveSpeed);
				break;
			}

			case RollLeft: {
				if (!checkMovableDirection[2])
					Move(-moveSpeed, 0);
				break;
			}

			case RollRight: {
				if (!checkMovableDirection[3])
					Move(moveSpeed, 0);
				break;
			}

			case RollUpLeft: {
				if (!checkMovableDirection[0])
					Move(0, -moveSpeed);
				if (!checkMovableDirection[2])
					Move(-moveSpeed, 0);
				break;
			}

			case RollUpRight: {
				if (!checkMovableDirection[0])
					Move(0, -moveSpeed);
				if (!checkMovableDirection[3])
					Move(moveSpeed, 0);
				break;
			}

			case RollDownLeft: {
				if (!checkMovableDirection[1])
					Move(0, moveSpeed);
				if (!checkMovableDirection[2])
					Move(-moveSpeed, 0);
				break;
			}

			case RollDownRight: {
				if (!checkMovableDirection[1])
					Move(0, moveSpeed);
				if (!checkMovableDirection[3])
					Move(moveSpeed, 0);
				break;
			}
		}
	}

	else {
		if (checkKeyInput[0] && !checkMovableDirection[0]) {
			if (checkKeyInput[2] || checkKeyInput[3]) {
				SetMoveDiagonalCheck(true);
				Move(0, -PLAYER_MOVE_SPEED_DIAGONAL);
			}
			else {
				SetMoveDiagonalCheck(false);
				Move(0, -PLAYER_MOVE_SPEED);
			}
		}
		if (checkKeyInput[1] && !checkMovableDirection[1]) {
			if (checkKeyInput[2] || checkKeyInput[3]) {
				SetMoveDiagonalCheck(true);
				Move(0, PLAYER_MOVE_SPEED_DIAGONAL);
			}
			else {
				SetMoveDiagonalCheck(false);
				Move(0, PLAYER_MOVE_SPEED);
			}
		}
		if (checkKeyInput[2] && !checkMovableDirection[2]) {
			if (checkKeyInput[0] || checkKeyInput[1]) {
				SetMoveDiagonalCheck(true);
				Move(-PLAYER_MOVE_SPEED_DIAGONAL, 0);
			}
			else {
				SetMoveDiagonalCheck(false);
				Move(-PLAYER_MOVE_SPEED, 0);
			}
		}
		if (checkKeyInput[3] && !checkMovableDirection[3]) {
			if (checkKeyInput[0] || checkKeyInput[1]) {
				SetMoveDiagonalCheck(true);
				Move(PLAYER_MOVE_SPEED_DIAGONAL, 0);
			}
			else {
				SetMoveDiagonalCheck(false);
				Move(PLAYER_MOVE_SPEED, 0);
			}
		}
	}
}

POINT Player::GetCameraRelativePosition() {
	return cameraRelativePosition;
}

void Player::SetCameraRelativePosition(POINT mousePoint, RECT rt) {
	angle = atan2(cameraRelativePosition.x - mousePoint.x, cameraRelativePosition.y - mousePoint.y);
	cameraRelativePosition = { rt.right / 2 - (mousePoint.x - rt.right / 2) * 3 / 7, rt.bottom / 2 - (mousePoint.y - rt.bottom / 2) * 2 / 3 };
	gunPosition = { -(long)(sin(angle) * CREATURE_GUN_HOLDING_DISTANCE) + cameraRelativePosition.x, -(long)(cos(angle) * CREATURE_GUN_HOLDING_DISTANCE) + cameraRelativePosition.y };
	guns[currentGunIdx]->SetAngle(angle);
}

void Player::SetCameraRelativeOffset() {
	cameraRelativeOffset = { cameraRelativePosition.x - position.x, cameraRelativePosition.y - position.y };
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

int Player::GetCurrentGunBulletAmount() {
	return guns[currentGunIdx]->GetCurrentBulletMount();
}

int Player::GetCurrentGunOriginBulletAmount() {
	return guns[currentGunIdx]->GetOriginBulletMount();
}

GunType Player::GetCurrentGunType() {
	return guns[currentGunIdx]->GetGunType();
}

void Player::ReloadCurrentGun() {
	return guns[currentGunIdx]->Reload();
}

bool Player::IsCurrentGunCanReload() {
	return guns[currentGunIdx]->IsGunCanReload();
}

bool Player::IsCurrentGunOnReload() {
	return guns[currentGunIdx]->IsGunOnReLoad();
}

Enemy::Enemy(EnemyType enemyType, int mapIndex) {
	this->enemyType = enemyType;
	this->mapIndex = mapIndex;
	isActivate = false;
	gunDelay = 0;
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

		case Boss: {
			originHP = 50;
			break;
		}
	}
	currentHP = originHP;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { 0, 0 };
	switch (enemyType) {
		case BulletJunior: {
			if (bulletJuniorSpriteBmp.IsNull()) {
				bulletJuniorSpriteBmp.Load(L"BulletJunior.bmp");
				bulletJuniorSpriteBmp.SetTransparentColor(RGB(0, 152, 239));
			}
			hitboxRect = {
				position.x - ENEMY_BULLETJUNIOR_SIZE / 2,
				position.y - ENEMY_BULLETJUNIOR_SIZE / 2,
				position.x + ENEMY_BULLETJUNIOR_SIZE / 2,
				position.y + ENEMY_BULLETJUNIOR_SIZE / 2
			};
			guns.push_back(new Gun(AutoHandgun, 6));
			break;
		}
		case Boss: {
			if (bossSpriteBmp.IsNull()) {
				bossSpriteBmp.Load(L"Boss.bmp");
				bossSpriteBmp.SetTransparentColor(RGB(0, 152, 239));
			}
			hitboxRect = {
				position.x - 150 / 2,
				position.y - 189 / 2,
				position.x + 150 / 2,
				position.y + 189 / 2
			};
			guns.push_back(new Gun(AutoHandgun, 6));
			break;
		}
	}
	moveRightBmp.Create(150, 25, 32, 0);
	moveRightBmp.SetTransparentColor(RGB(0, 152, 239));
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 150; x++) {
			moveRightBmp.SetPixel(x, y, bulletJuniorSpriteBmp.GetPixel(149 - x, 25 + y));
		}
	}
	animationStatus = IdleDown;
}

Enemy::Enemy(EnemyType enemyType, int x, int y, int mapIndex) {
	this->enemyType = enemyType;
	this->mapIndex = mapIndex;
	isActivate = false;
	gunDelay = 0;
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

		case Boss: {
			originHP = 50;
			break;
		}
	}
	currentHP = originHP;
	animationIndex = 0;
	isMoveDiagonal = false;
	position = { x, y };
	switch (enemyType) {
		case BulletJunior: {
			if (bulletJuniorSpriteBmp.IsNull()) {
				bulletJuniorSpriteBmp.Load(L"BulletJunior.bmp");
				bulletJuniorSpriteBmp.SetTransparentColor(RGB(0, 152, 239));
			}
			hitboxRect = {
				position.x - ENEMY_BULLETJUNIOR_SIZE / 2,
				position.y - ENEMY_BULLETJUNIOR_SIZE / 2,
				position.x + ENEMY_BULLETJUNIOR_SIZE / 2,
				position.y + ENEMY_BULLETJUNIOR_SIZE / 2
			};
			guns.push_back(new Gun(AutoHandgun, 6));
			break;
		}
		case Boss: {
			if (bossSpriteBmp.IsNull()) {
				bossSpriteBmp.Load(L"Boss.bmp");
				bossSpriteBmp.SetTransparentColor(RGB(0, 152, 239));
			}
			hitboxRect = {
				position.x - 150 / 2,
				position.y - 189 / 2,
				position.x + 150 / 2,
				position.y + 189 / 2
			};
			guns.push_back(new Gun(AutoHandgun, 6));
			break;
		}
	}
	moveRightBmp.Create(150, 25, 32, 0);
	moveRightBmp.SetTransparentColor(RGB(0, 152, 239));
	for (int y = 0; y < 25; y++) {
		for (int x = 0; x < 150; x++) {
			moveRightBmp.SetPixel(x, y, bulletJuniorSpriteBmp.GetPixel(149 - x, 25 + y));
		}
	}
	animationStatus = IdleDown;
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
	if (currentHP <= 0) {
		animationStatus = Death;
	}
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


void Enemy::PlayAnimation(HDC hDC) {
	switch (enemyType) {
		case BulletJunior: {
			switch (animationStatus) {
				case Death: {
					bulletJuniorSpriteBmp.Draw(hDC, (cameraRelativeOffset.x + position.x) - ENEMY_BULLETJUNIOR_SIZE / 2, (cameraRelativeOffset.y + position.y) - ENEMY_BULLETJUNIOR_SIZE / 2, ENEMY_BULLETJUNIOR_SIZE, ENEMY_BULLETJUNIOR_SIZE, 25 * animationIndex, 11 * 25, 25, 25);
					break;
				}

				case IdleUp: {
					guns[0]->Draw(hDC, gunPosition, false);
					bulletJuniorSpriteBmp.Draw(hDC, (cameraRelativeOffset.x + position.x) - ENEMY_BULLETJUNIOR_SIZE / 2, (cameraRelativeOffset.y + position.y) - ENEMY_BULLETJUNIOR_SIZE / 2, ENEMY_BULLETJUNIOR_SIZE, ENEMY_BULLETJUNIOR_SIZE, 25 * animationIndex + 100, 0, 25, 25);
					break;
				}

				case IdleDown: {
					bulletJuniorSpriteBmp.Draw(hDC, (cameraRelativeOffset.x + position.x) - ENEMY_BULLETJUNIOR_SIZE / 2, (cameraRelativeOffset.y + position.y) - ENEMY_BULLETJUNIOR_SIZE / 2, ENEMY_BULLETJUNIOR_SIZE, ENEMY_BULLETJUNIOR_SIZE, 25 * animationIndex, 0, 25, 25);
					guns[0]->Draw(hDC, gunPosition, false);
					break;
				}

				case MoveRight: {
					moveRightBmp.Draw(hDC, (cameraRelativeOffset.x + position.x) - ENEMY_BULLETJUNIOR_SIZE / 2, (cameraRelativeOffset.y + position.y) - ENEMY_BULLETJUNIOR_SIZE / 2, ENEMY_BULLETJUNIOR_SIZE, ENEMY_BULLETJUNIOR_SIZE, 25 * animationIndex, 0, 25, 25);
					guns[0]->Draw(hDC, gunPosition, false);
					break;
				}

				case MoveLeft: {
					bulletJuniorSpriteBmp.Draw(hDC, (cameraRelativeOffset.x + position.x) - ENEMY_BULLETJUNIOR_SIZE / 2, (cameraRelativeOffset.y + position.y) - ENEMY_BULLETJUNIOR_SIZE / 2, ENEMY_BULLETJUNIOR_SIZE, ENEMY_BULLETJUNIOR_SIZE, 25 * animationIndex, 25, 25, 25);
					guns[0]->Draw(hDC, gunPosition, false);
					break;
				}
			}
			break;
		}
		case Boss: {
			switch (animationStatus) {
				default: {
					bossSpriteBmp.Draw(hDC, (cameraRelativeOffset.x + position.x) - 150 / 2, (cameraRelativeOffset.y + position.y) - 189 / 2, 150, 189, 0, 0, 50, 63);
					break;
				}
			}
			break;
		}
	}
}

int Enemy::GetAnimationIndex() {
	return animationIndex;
}

void Enemy::SetAnimationIndex(int value) {
	animationIndex = value;
}

void Enemy::UpdateAnimationIndex() {
	switch (animationStatus) {
		case Death: {
			animationIndex = 0;
			break;
		}

		case IdleUp: {
			animationIndex = (animationIndex + 1) % 2;
			break;
		}

		case IdleDown: {
			animationIndex = (animationIndex + 1) % 4;
			break;
		}
		
		default: {
			animationIndex = (animationIndex + 1) % 6;
			break;
		}
	}
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
	return guns[0]->Shoot(position, 0, true);
}

void Enemy::AI() {
	if (animationStatus == Death || !isActivate)
		return;

	angle = atan2(position.x - destPosition.x, position.y - destPosition.y);
	//gunPosition = { -(long)(sin(angle) * CREATURE_GUN_HOLDING_DISTANCE) + cameraRelativeOffset.x + position.x, -(long)(cos(angle) * CREATURE_GUN_HOLDING_DISTANCE) + cameraRelativeOffset.y + position.y };
	gunPosition = { cameraRelativeOffset.x + position.x, cameraRelativeOffset.y + position.y };
	guns[0]->SetAngle(angle);
	gunDelay += 1;

	distanceToPlayer = DistanceByPoint(destPosition, position);

	AnimationStatus oldStatus = animationStatus;

	// 일정 이상 접근시 더 이상 접근하지 않음. 제자리 사격
	if (distanceToPlayer <= ENEMY_STOP_DISTANCE) {
		animationStatus = IdleDown;
	}
	// 멀면 길찾기 시작.
	else {
		// 좌표 하나라도 겹치면 직선이동
		if (destPosition.x == position.x) {
			if (destPosition.y < position.y) {
				if (!checkMovableDirection[0])
					Move(0, -ENEMY_MOVE_SPEED_DEFAULT);
			}
			else {
				if (!checkMovableDirection[1])
					Move(0, ENEMY_MOVE_SPEED_DEFAULT);
			}
		}
		else if (destPosition.y == position.y) {
			if (destPosition.x < position.x) {
				if (!checkMovableDirection[2]) {
					Move(-ENEMY_MOVE_SPEED_DEFAULT, 0);
					animationStatus = MoveLeft;
				}
			}
			else {
				if (!checkMovableDirection[3]) {
					Move(ENEMY_MOVE_SPEED_DEFAULT, 0);
					animationStatus = MoveRight;
				}
			}
		}
		// 대각선 이동
		else {
			POINT moveMount;
			moveMount.x = abs(destPosition.x - position.x) < ENEMY_MOVE_SPEED_DEFAULT_DIAGONAL ? abs(destPosition.x - position.x) : ENEMY_MOVE_SPEED_DEFAULT_DIAGONAL;
			moveMount.y = abs(destPosition.y - position.y) < ENEMY_MOVE_SPEED_DEFAULT_DIAGONAL ? abs(destPosition.y - position.y) : ENEMY_MOVE_SPEED_DEFAULT_DIAGONAL;
			if (destPosition.x < position.x) {
				animationStatus = MoveLeft;
				if (checkMovableDirection[2])
					moveMount.x = 0;
				if (destPosition.y < position.y) {
					if (checkMovableDirection[0])
						moveMount.y = 0;
					Move(-moveMount.x, -moveMount.y);
				}
				else {
					if (checkMovableDirection[1])
						moveMount.y = 0;
					Move(-moveMount.x, moveMount.y);
				}
			}
			else {
				animationStatus = MoveRight;
				if (checkMovableDirection[3])
					moveMount.x = 0;
				if (destPosition.y < position.y) {
					if (checkMovableDirection[0])
						moveMount.y = 0;
					Move(moveMount.x, -moveMount.y);
				}
				else {
					if (checkMovableDirection[1])
						moveMount.y = 0;
					Move(moveMount.x, moveMount.y);
				}
			}
		}
	}

	if (animationStatus != oldStatus) {
		animationIndex = 0;
	}
}

void Enemy::SetDestination(POINT playerPosition) {
	destPosition = playerPosition;
}

bool Enemy::IsCanFire() {
	if (gunDelay >= ENEMY_GUN_DELAY_TIME) {
		gunDelay = 0;
		return true;
	}
	return false;
}