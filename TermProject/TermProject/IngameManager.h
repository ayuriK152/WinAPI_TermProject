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

namespace Game {
	static HDC hDC, mDC;
	static PAINTSTRUCT ps;
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static RECT rt;
	static HBITMAP hBitmap;

	static Player* player;
	static vector<Bullet*> bullets;
	static POINT mousePoint, centerOffset;
	static CImage cursor, heart, bullet;
	static Map* map;
	static bool checkKeyInput[4], checkMovableDirection[4];
	static int currentMapIdx;
	static void (CALLBACK* animationRefresh)(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
	static void (CALLBACK* positionRefresh)(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	void PlayAnimation(HDC hDC);

	double DistanceByPoint(POINT p1, POINT p2);

	double TanByPoint(POINT p1, POINT p2);

	void Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene);

	void CALLBACK AnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	void CALLBACK PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
}