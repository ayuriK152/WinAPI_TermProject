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

using namespace std;

void CALLBACK AnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void CALLBACK PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
void PlayAnimation(HDC hDC);
double DistanceByPoint(POINT p1, POINT p2);
double TanByPoint(POINT p1, POINT p2);

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1600, 900, NULL, (HMENU)NULL, hInstance, NULL);
	ShowCursor(false);
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
static vector<Bullet> bullets;
static POINT mousePoint, centerOffset;
static CImage cursor, heart, bullet;
static bool checkKeyInput[4];

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	srand((unsigned int)time(NULL));
	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	switch (uMsg) {
		case WM_CREATE: {
			GetClientRect(hWnd, &rt);

			player = new Player(rt.right / 2, rt.bottom / 2);
			player->SetSpriteBitmap(L"The Pilot.bmp");
			heart.Load(L"heart.bmp");
			heart.SetTransparentColor(RGB(0, 255, 0));

			SetTimer(hWnd, 1000, ANIMATION_REFRESH_DURATION, AnimationRefresh);
			SetTimer(hWnd, 1001, POSITION_REFRESH_DURATION, PositionRefresh);

			cursor.Load(L"Cursor.bmp");
			cursor.SetTransparentColor(RGB(0, 255, 0));

			bullet.Load(L"bullet.bmp");
			bullet.SetTransparentColor(RGB(0, 255, 0));
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
			mousePoint = { LOWORD(lParam), HIWORD(lParam) };

			bullets.push_back(Bullet(player->GetPosition(), 15, atan2(player->GetCameraRelativePosition().x - mousePoint.x, player->GetCameraRelativePosition().y - mousePoint.y)));
			break;
		}

		case WM_LBUTTONUP: {

			break;
		}

		case WM_RBUTTONDOWN: {
			if (player->IsRolling())
				break;
			player->Roll(checkKeyInput);
			KillTimer(hWnd, 1000);
			SetTimer(hWnd, 1000, ANIMATION_REFRESH_DURATION_PLAYER_ROLL, AnimationRefresh);
			break;
		}

		case WM_MOUSEMOVE: {
			mousePoint = { LOWORD(lParam), HIWORD(lParam) };
			player->SetCameraRelativePosition({ rt.right / 2 - (mousePoint.x - rt.right / 2) * 3 / 7, rt.bottom / 2 - (mousePoint.y - rt.bottom / 2) * 2 / 3 });
			centerOffset = { player->GetCameraRelativePosition().x - player->GetPosition().x, player->GetCameraRelativePosition().y - player->GetPosition().y };
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
	if (player->IsRolling()) {
		player->UpdateAnimationIndex();

		if (!player->IsRolling()) {
			KillTimer(hWnd, 1000);
			SetTimer(hWnd, 1000, ANIMATION_REFRESH_DURATION, AnimationRefresh);
		}
		return;
	}

	AnimationStatus pastStatus = player->GetMoveStatus();
	double tanValue = TanByPoint(player->GetCameraRelativePosition(), mousePoint);

	if (mousePoint.x < player->GetCameraRelativePosition().x && (tanValue >= TAN_22_5 && tanValue <= TAN_67_5)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			player->SetMoveStatus(IdleUpLeft);
		else
			player->SetMoveStatus(MoveUpLeft);
	}
	else if (mousePoint.x > player->GetCameraRelativePosition().x && (tanValue <= -TAN_22_5 && tanValue >= -TAN_67_5)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			player->SetMoveStatus(IdleUpRight);
		else
		player->SetMoveStatus(MoveUpRight);
	}
	else if (mousePoint.x < player->GetCameraRelativePosition().x && ((tanValue <= TAN_22_5 && tanValue >= 0) || tanValue >= -TAN_67_5 && tanValue <= 0)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			player->SetMoveStatus(IdleLeft);
		else
			player->SetMoveStatus(MoveLeft);
	}
	else if (mousePoint.x > player->GetCameraRelativePosition().x && ((tanValue >= -TAN_22_5 && tanValue <= 0) || tanValue <= TAN_67_5 && tanValue >= 0)) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			player->SetMoveStatus(IdleRight);
		else
			player->SetMoveStatus(MoveRight);
	}
	else if (mousePoint.y < player->GetCameraRelativePosition().y) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			player->SetMoveStatus(IdleUp);
		else
			player->SetMoveStatus(MoveUp);
	}
	else if (mousePoint.y > player->GetCameraRelativePosition().y) {
		if (!checkKeyInput[0] && !checkKeyInput[1] && !checkKeyInput[2] && !checkKeyInput[3])
			player->SetMoveStatus(IdleDown);
		else
			player->SetMoveStatus(MoveDown);
	}
	if (pastStatus != player->GetMoveStatus()) {
		player->SetAnimationIndex(0);
	}
	player->UpdateAnimationIndex();
}

void CALLBACK PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	centerOffset = { player->GetCameraRelativePosition().x - player->GetPosition().x, player->GetCameraRelativePosition().y - player->GetPosition().y };
	if (player->IsRolling()) {
		int moveSpeed = 0;
		if (player->GetAnimationIndex() > 6)
			moveSpeed = player->IsMoveDiagonal() ? PLAYER_ROLL_END_SPEED_DIAGONAL : PLAYER_ROLL_END_SPEED;
		else if (player->GetAnimationIndex() > 4)
			moveSpeed = player->IsMoveDiagonal() ? PLAYER_ROLL_ING_SPEED_DIAGONAL : PLAYER_ROLL_ING_SPEED;
		else
			moveSpeed = player->IsMoveDiagonal() ? PLAYER_ROLL_START_SPEED_DIAGONAL : PLAYER_ROLL_START_SPEED;

		switch (player->GetMoveStatus()) {
			case RollUp: {
				player->Move(0, -moveSpeed);
				break;
			}
			case RollDown: {
				player->Move(0, moveSpeed);
				break;
			}
			case RollLeft: {
				player->Move(-moveSpeed, 0);
				break;
			}
			case RollRight: {
				player->Move(moveSpeed, 0);
				break;
			}
			case RollUpLeft: {
				player->Move(-moveSpeed, -moveSpeed);
				break;
			}
			case RollUpRight: {
				player->Move(moveSpeed, -moveSpeed);
				break;
			}
			case RollDownLeft: {
				player->Move(-moveSpeed, moveSpeed);
				break;
			}
			case RollDownRight: {
				player->Move(moveSpeed, moveSpeed);
				break;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}

	else {
		if (checkKeyInput[0]) {
			if (checkKeyInput[2] || checkKeyInput[3]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(0, -PLAYER_MOVE_SPEED_DIAGONAL);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(0, -PLAYER_MOVE_SPEED);
			}
		}
		if (checkKeyInput[1]) {
			if (checkKeyInput[2] || checkKeyInput[3]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(0, PLAYER_MOVE_SPEED_DIAGONAL);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(0, PLAYER_MOVE_SPEED);
			}
		}
		if (checkKeyInput[2]) {
			if (checkKeyInput[0] || checkKeyInput[1]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(-PLAYER_MOVE_SPEED_DIAGONAL, 0);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(-PLAYER_MOVE_SPEED, 0);
			}
		}
		if (checkKeyInput[3]) {
			if (checkKeyInput[0] || checkKeyInput[1]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(PLAYER_MOVE_SPEED_DIAGONAL, 0);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(PLAYER_MOVE_SPEED, 0);
			}
		}
	}
	InvalidateRect(hWnd, NULL, FALSE);
}

void PlayAnimation(HDC hDC) {
	hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	mDC = CreateCompatibleDC(hDC);
	SelectObject(mDC, hBitmap);

	player->PlayAnimation(mDC);
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].Move();
		bullet.Draw(mDC, bullets[i].GetPosition().x - 13 + centerOffset.x, bullets[i].GetPosition().y - 13 + centerOffset.y, 27, 27);
	}
	cursor.Draw(mDC, mousePoint.x - 16, mousePoint.y - 16, 33, 33);

	for (int i = 0; i < player->GetOriginHp() / 2; i++) {
		if (player->GetCurrentHp() - (i + 1) * 2 == -1)
			heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
		else if (player->GetCurrentHp() - (i + 1) * 2 <= -2)
			heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 2,  0,PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
		else
			heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, 0, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
	}
	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);
	DeleteObject(mDC);
}

double DistanceByPoint(POINT p1, POINT p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double TanByPoint(POINT p1, POINT p2) {
	return (double)(p2.y - p1.y) / (p2.x - p1.x);
}