#include "MainmenuManager.h"

void Menu::Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene) {
	RECT rt;
	PAINTSTRUCT ps;
	HDC hDC;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	switch (uMsg) {
		case WM_CREATE: {
			break;
		}

		case WM_PAINT: {
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);

			EndPaint(hWnd, &ps);
			break;
		}

		case WM_CHAR: {
			if (wParam == 'a') {
				*gameScene = Ingame;
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