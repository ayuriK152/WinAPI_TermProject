#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <atlImage.h>
#include "creatures.h"
#include "values.h"

using namespace std;

void CALLBACK AnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void PlayAnimation(HDC hDC);

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;

	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

HDC mDC;
HBITMAP hBitmap;
RECT rt;

static Player* player;
static bool checkKeyInput[4];

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	srand((unsigned int)time(NULL));
	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	static bool isDrag;

	switch (uMsg) {
		case WM_CREATE: {
			GetClientRect(hWnd, &rt);

			player = new Player(rt.right / 2, rt.bottom / 2);
			player->SetSpriteBitmap(L"The Pilot.bmp");

			SetTimer(hWnd, 1000, 75, AnimationRefresh);
			SetTimer(hWnd, 1001, 10, PositionRefresh);
			break;
		}

		case WM_PAINT: {
			hDC = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);

			PlayAnimation(hDC);

			EndPaint(hWnd, &ps);
			break;
		}

		case WM_KEYDOWN: {
			if (wParam == 'w' || wParam == 'W') {
				checkKeyInput[0] = true;
			}
			else if (wParam == 's' || wParam == 'S') {
				checkKeyInput[1] = true;
			}
			if (wParam == 'a' || wParam == 'A') {
				checkKeyInput[2] = true;
			}
			else if (wParam == 'd' || wParam == 'D') {
				checkKeyInput[3] = true;
			}
			break;
		}

		case WM_KEYUP: {
			if (wParam == 'w' || wParam == 'W') {
				checkKeyInput[0] = false;
			}
			else if (wParam == 's' || wParam == 'S') {
				checkKeyInput[1] = false;
			}
			if (wParam == 'a' || wParam == 'A') {
				checkKeyInput[2] = false;
			}
			else if (wParam == 'd' || wParam == 'D') {
				checkKeyInput[3] = false;
			}
			break;
		}

		case WM_LBUTTONDOWN: {
			isDrag = true;

			break;
		}

		case WM_LBUTTONUP: {
			isDrag = false;

			break;
		}

		case WM_MOUSEMOVE: {

			break;
		}

		case WM_CHAR: {
			break;
		}

		case WM_COMMAND: {

			break;
		}

		case WM_DESTROY: {
			delete player;
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void CALLBACK AnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	player->UpdateAnimationIndex();
}

void CALLBACK PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (checkKeyInput[0]) {
		player->Move(0, -playerMoveSPeed);
	}
	if (checkKeyInput[1]) {
		player->Move(0, playerMoveSPeed);
	}
	if (checkKeyInput[2]) {
		player->Move(-playerMoveSPeed, 0);
	}
	if (checkKeyInput[3]) {
		player->Move(playerMoveSPeed, 0);
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

void PlayAnimation(HDC hDC) {
	hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	mDC = CreateCompatibleDC(hDC);
	SelectObject(mDC, hBitmap);

	player->PlayAnimation(mDC);
	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);
	DeleteObject(mDC);
}