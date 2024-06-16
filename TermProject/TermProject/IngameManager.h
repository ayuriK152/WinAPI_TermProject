#pragma once

#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <atlImage.h>
#include "resource.h"
#include "Creatures.h"
#include "Bullet.h"
#include "values.h"
#include "Map.h"
#include "Utils.h"

namespace Game {
	static HDC hDC, mDC;
	static PAINTSTRUCT ps;
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static RECT rt;
	static HBITMAP hBitmap;

	static Player* player;
	static vector<Enemy*> enemys;
	static vector<Bullet*> bullets;
	static POINT mousePoint, centerOffset;
	static CImage cursor, heart, bullet;
	static CImage enemyBullet;
	static Map* map;
	static bool checkKeyInput[4], checkMovableDirection[4];
	static int currentMapIdx;

	void PlayAnimation(HDC hDC);

	void Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene);

	void CALLBACK PlayerAnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	void CALLBACK PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	void CALLBACK EnemyAnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	void CALLBACK EnemyAIRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
}