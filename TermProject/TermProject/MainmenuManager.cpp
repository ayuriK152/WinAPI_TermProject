#include "MainmenuManager.h"

void Menu::Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene) {

	switch (uMsg) {
		case WM_GAMESCENECHANGED: {
			if (backgroundBmp.IsNull()) {
				backgroundBmp.Load(L"MainmenuBG.bmp");
			}

			if (cursor.IsNull()) {
				cursor.Load(L"Cursor.bmp");
				cursor.SetTransparentColor(RGB(0, 255, 0));
			}

			SetTimer(hWnd, 1000, POSITION_REFRESH_DURATION, NULL);
			break;
		}

		case WM_TIMER: {
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}

		case WM_PAINT: {
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);

			PlayAnimation(hDC);

			EndPaint(hWnd, &ps);
			break;
		}

		case WM_MOUSEMOVE: {
			mousePoint = { LOWORD(lParam), HIWORD(lParam) };
			break;
		}

		case WM_CHAR: {
			if (wParam == 'a') {
				*gameScene = Ingame;
				KillTimer(hWnd, 1000);
				SendMessage(hWnd, WM_GAMESCENECHANGED, wParam, lParam);
			}
			break;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
	}
}

void Menu::PlayAnimation(HDC hDC) {
	hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	mDC = CreateCompatibleDC(hDC);
	SelectObject(mDC, hBitmap);

	backgroundBmp.StretchBlt(mDC, 0, 0, rt.right, rt.bottom, 0, 0, 1920, 1080);

	cursor.Draw(mDC, mousePoint.x - CURSOR_SIZE / 2, mousePoint.y - CURSOR_SIZE / 2, CURSOR_SIZE, CURSOR_SIZE);

	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);
	DeleteDC(mDC);
}