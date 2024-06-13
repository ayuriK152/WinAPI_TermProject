#include "IngameManager.h"

void CALLBACK Game::AnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
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

void CALLBACK Game::PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	centerOffset = { player->GetCameraRelativePosition().x - player->GetPosition().x, player->GetCameraRelativePosition().y - player->GetPosition().y };

	map->CheckMovableDirection(checkMovableDirection, player->GetPosition(), player->GetHitboxRect());

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
				if (!checkMovableDirection[0])
					player->Move(0, -moveSpeed);
				break;
			}
			case RollDown: {
				if (!checkMovableDirection[1])
					player->Move(0, moveSpeed);
				break;
			}
			case RollLeft: {
				if (!checkMovableDirection[2])
					player->Move(-moveSpeed, 0);
				break;
			}
			case RollRight: {
				if (!checkMovableDirection[3])
					player->Move(moveSpeed, 0);
				break;
			}
			case RollUpLeft: {
				if (!checkMovableDirection[0])
					player->Move(0, -moveSpeed);
				if (!checkMovableDirection[2])
					player->Move(-moveSpeed, 0);
				break;
			}
			case RollUpRight: {
				if (!checkMovableDirection[0])
					player->Move(0, -moveSpeed);
				if (!checkMovableDirection[3])
					player->Move(moveSpeed, 0);
				break;
			}
			case RollDownLeft: {
				if (!checkMovableDirection[1])
					player->Move(0, moveSpeed);
				if (!checkMovableDirection[2])
					player->Move(-moveSpeed, 0);
				break;
			}
			case RollDownRight: {
				if (!checkMovableDirection[1])
					player->Move(0, moveSpeed);
				if (!checkMovableDirection[3])
					player->Move(moveSpeed, 0);
				break;
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}

	else {
		if (checkKeyInput[0] && !checkMovableDirection[0]) {
			if (checkKeyInput[2] || checkKeyInput[3]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(0, -PLAYER_MOVE_SPEED_DIAGONAL);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(0, -PLAYER_MOVE_SPEED);
			}
		}
		if (checkKeyInput[1] && !checkMovableDirection[1]) {
			if (checkKeyInput[2] || checkKeyInput[3]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(0, PLAYER_MOVE_SPEED_DIAGONAL);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(0, PLAYER_MOVE_SPEED);
			}
		}
		if (checkKeyInput[2] && !checkMovableDirection[2]) {
			if (checkKeyInput[0] || checkKeyInput[1]) {
				player->SetMoveDiagonalCheck(true);
				player->Move(-PLAYER_MOVE_SPEED_DIAGONAL, 0);
			}
			else {
				player->SetMoveDiagonalCheck(false);
				player->Move(-PLAYER_MOVE_SPEED, 0);
			}
		}
		if (checkKeyInput[3] && !checkMovableDirection[3]) {
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

void Game::PlayAnimation(HDC hDC) {
	hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	mDC = CreateCompatibleDC(hDC);
	SelectObject(mDC, hBitmap);

	map->DrawFloor(mDC, centerOffset, rt);

	player->PlayAnimation(mDC);
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Move();
		if (map->IsCollideWall(bullets[i]->GetHitboxRect())) {
			bullets.erase(bullets.begin() + i);
			i -= 1;
		}
		else {
			bullet.Draw(mDC, bullets[i]->GetPosition().x - 22 + centerOffset.x, bullets[i]->GetPosition().y - 22 + centerOffset.y, 45, 45);
		}
	}

	map->DrawCeil(mDC, centerOffset, rt);

	cursor.Draw(mDC, mousePoint.x - CURSOR_SIZE / 2, mousePoint.y - CURSOR_SIZE / 2, CURSOR_SIZE, CURSOR_SIZE);

	for (int i = 0; i < player->GetOriginHp() / 2; i++) {
		if (player->GetCurrentHp() - (i + 1) * 2 == -1)
			heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
		else if (player->GetCurrentHp() - (i + 1) * 2 <= -2)
			heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 2, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
		else
			heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, 0, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
	}

	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	DeleteObject(hBitmap);
	DeleteDC(mDC);
}

double Game::DistanceByPoint(POINT p1, POINT p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double Game::TanByPoint(POINT p1, POINT p2) {
	return (double)(p2.y - p1.y) / (p2.x - p1.x);
}

void Game::Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene) {
	srand((unsigned int)time(NULL));

	switch (uMsg) {
		case WM_GAMESCENECHANGED: {
			hDC = GetDC(hWnd);
			GetClientRect(hWnd, &rt);

			player = new Player();
			player->SetSpriteBitmap(L"The Pilot.bmp");
			heart.Load(L"heart.bmp");
			heart.SetTransparentColor(RGB(0, 255, 0));

			animationRefresh = AnimationRefresh;
			positionRefresh = PositionRefresh;
			SetTimer(hWnd, 1000, ANIMATION_REFRESH_DURATION, AnimationRefresh);
			SetTimer(hWnd, 1001, POSITION_REFRESH_DURATION, PositionRefresh);

			if (cursor.IsNull()) {
				cursor.Load(L"Cursor.bmp");
				cursor.SetTransparentColor(RGB(0, 255, 0));
				mousePoint = { rt.right / 2, rt.bottom / 2 };
			}

			bullet.Load(L"bullet.bmp");
			bullet.SetTransparentColor(RGB(0, 255, 0));

			player->SetCameraRelativePosition(mousePoint, rt);
			centerOffset = { player->GetCameraRelativePosition().x - player->GetPosition().x, player->GetCameraRelativePosition().y - player->GetPosition().y };

			map = new Map(hDC);
			currentMapIdx = 0;
			ReleaseDC(hWnd, hDC);
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
			bullets.push_back(player->FireGun());
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
			player->SetCameraRelativePosition(mousePoint, rt);
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
}