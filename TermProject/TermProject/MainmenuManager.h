#pragma once

#include <Windows.h>
#include <atlimage.h>
#include "datas.h"
#include "values.h"

namespace Menu {
	static HDC hDC, mDC;
	static PAINTSTRUCT ps;
	static HBRUSH hBrush, oldBrush;
	static HPEN hPen, oldPen;
	static RECT rt;
	static HBITMAP hBitmap;
	static CImage cursor;
	static POINT mousePoint;

	static CImage backgroundBmp;

	void Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene);

	void PlayAnimation(HDC hDC);
}