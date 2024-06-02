#pragma once
#include <atlImage.h>
#include "creatures.h"

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
		case Up: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_UP.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_UP.y, 25, 25);
			break;
		}
		case Down: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_DOWN.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_DOWN.y, 25, 25);
			break;
		}
		case Left: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_LEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_LEFT.y + y));
				}
			}
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case Right: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_RIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_RIGHT.y, 25, 25);
			break;
		}
		case UpLeft: {
			CImage temp;
			temp.Create(25, 25, 32, 0);
			temp.SetTransparentColor(RGB(144, 187, 187));
			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 25; x++) {
					temp.SetPixel(x, y, spriteBitmap.GetPixel(ANIMATION_OFFSET_PLAYER_UPLEFT.x + 25 * (animationIndex + 1) - 1 - x, ANIMATION_OFFSET_PLAYER_UPLEFT.y + y));
				}
			}
			temp.Draw(hDC, position.x, position.y, 50, 50, 0, 0, 25, 25);
			DeleteObject(temp);
			break;
		}
		case UpRight: {
			spriteBitmap.Draw(hDC, position.x, position.y, 50, 50, ANIMATION_OFFSET_PLAYER_UPRIGHT.x + 25 * animationIndex, ANIMATION_OFFSET_PLAYER_UPRIGHT.y, 25, 25);
			break;
		}
	}
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
		default: {
			animationIndex = (animationIndex + 1) % 6;
			break;
		}
	}
}