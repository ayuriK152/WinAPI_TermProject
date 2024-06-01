#pragma once
#include <atlImage.h>
#include "creatures.h"
#include "datas.h"
#include "values.h"

Player::Player() {
	hp = 6;
	animationIndex = 0;
	position = { 0, 0 };
	animationStatus = IdleDown;
	spriteBitmap.SetTransparentColor(RGB(144, 187, 187));
}

Player::Player(int x, int y) {
	hp = 6;
	animationIndex = 0;
	position = { 0, 0 };
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
		case IdleDown: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, animationOffsetPlayerIdle.x + 25 * animationIndex, animationOffsetPlayerIdle.y, 25, 25);
			break;
		}
		case Up: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, animationOffsetPlayerUp.x + 25 * animationIndex, animationOffsetPlayerUp.y, 25, 25);
			break;
		}
		case Down: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, animationOffsetPlayerDown.x + 25 * animationIndex, animationOffsetPlayerDown.y, 25, 25);
			break;
		}
		case Left: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(animationOffsetPlayerLeft.x + 25 * (animationIndex + 1) - 1 - x, animationOffsetPlayerLeft.y + y));
				}
			}
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case Right: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, animationOffsetPlayerRight.x + 25 * animationIndex, animationOffsetPlayerRight.y, 25, 25);
			break;
		}
	}
}

void Player::SetAnimationIndex(int value) {
	animationIndex = value;
}

void Player::UpdateAnimationIndex() {
	switch (animationStatus) {
		default: {
			animationIndex = (animationIndex + 1) % 6;
			break;
		}
	}
}