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
#include "IngameManager.h"
#include "MainmenuManager.h"

using namespace std;

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 1600, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowCursor(false);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

static GameScene gameScene = MainMenu;
static HFONT hFont, oldFont;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_CREATE) {
		SendMessage(hWnd, WM_GAMESCENECHANGED, wParam, lParam);
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	switch (gameScene) {
		case MainMenu: {
			Menu::Play(hWnd, uMsg, wParam, lParam, &gameScene);
			break;
		}
		case Ingame: {
			Game::Play(hWnd, uMsg, wParam, lParam, &gameScene);
			break;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}