#include "IngameManager.h"

void CALLBACK Game::PlayerAnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	if (player->IsRolling()) {
		player->UpdateAnimationIndex();

		if (!player->IsRolling()) {
			KillTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER);
			SetTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER, ANIMATION_REFRESH_DURATION, PlayerAnimationRefresh);
		}
		return;
	}

	player->AnimationRefresh(checkKeyInput, mousePoint);
}

void CALLBACK Game::PositionRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	centerOffset = { player->GetCameraRelativePosition().x - player->GetPosition().x, player->GetCameraRelativePosition().y - player->GetPosition().y };
	player->SetCameraRelativeOffset();
	map->CheckMovableDirection(checkMovableDirection, player->GetPosition(), player->GetHitboxRect());

	player->PositionRefresh(checkKeyInput, checkMovableDirection);

	InvalidateRect(hWnd, NULL, FALSE);
}

void CALLBACK Game::EnemyAnimationRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	AnimationStatus pastStatus = enemys[idEvent - ANIMATION_REFRESH_ID_ENEMY]->GetMoveStatus();
	enemys[idEvent - ANIMATION_REFRESH_ID_ENEMY]->UpdateAnimationIndex();
}

void CALLBACK Game::EnemyAIRefresh(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	enemys[idEvent - AI_REFRESH_ID_ENEMY]->SetDestination(player->GetPosition());
}

void Game::PlayAnimation(HDC hDC) {
	hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	mDC = CreateCompatibleDC(hDC);
	SelectObject(mDC, hBitmap);

	map->DrawFloor(mDC, centerOffset, rt);

	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->PlayAnimation(mDC);
		if (enemys[i]->IsCanFire()) {
			bullets.push_back(enemys[i]->FireGun());
		}
		if (enemys[i]->GetMoveStatus() == Death)
			continue;
		for (int j = 0; j < bullets.size(); j++) {
			if (IsCollide(enemys[i]->GetHitboxRect(), bullets[j]->GetHitboxRect()) && !bullets[j]->IsHostile()) {
				enemys[i]->GetDamge(1);
				delete bullets[j];
				bullets.erase(bullets.begin() + j);
				j--;
				break;
			}
		}
		enemys[i]->AI();
	}

	player->PlayAnimation(mDC);

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Move();
		bool isCollide = false;
		if (map->IsCollideWall(bullets[i]->GetHitboxRect()) || isCollide) {
			delete bullets[i];
			bullets.erase(bullets.begin() + i);
			i -= 1;
		}
		else {
			if (bullets[i]->IsHostile()) {
				enemyBullet.Draw(mDC, bullets[i]->GetPosition().x - 22 + centerOffset.x, bullets[i]->GetPosition().y - 22 + centerOffset.y, 45, 45);
			}
			else {
				bullet.Draw(mDC, bullets[i]->GetPosition().x - 22 + centerOffset.x, bullets[i]->GetPosition().y - 22 + centerOffset.y, 45, 45);
			}
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

void Game::Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene) {
	srand((unsigned int)time(NULL));

	switch (uMsg) {
		case WM_GAMESCENECHANGED: {
			hDC = GetDC(hWnd);
			GetClientRect(hWnd, &rt);

			player = new Player();
			heart.Load(L"heart.bmp");
			heart.SetTransparentColor(RGB(0, 255, 0));

			enemys.push_back(new Enemy(BulletJunior, 200, 200));

			SetTimer(hWnd, POSITION_REFRESH_ID, POSITION_REFRESH_DURATION, PositionRefresh);
			SetTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER, ANIMATION_REFRESH_DURATION, PlayerAnimationRefresh);
			for (int i = 0; i < enemys.size(); i++) {
				SetTimer(hWnd, ANIMATION_REFRESH_ID_ENEMY + i, ANIMATION_REFRESH_DURATION_ENEMY, EnemyAnimationRefresh);
				SetTimer(hWnd, AI_REFRESH_ID_ENEMY + i, AI_REFRESH_REFRESH_DURATION, EnemyAIRefresh);
			}

			if (cursor.IsNull()) {
				cursor.Load(L"Cursor.bmp");
				cursor.SetTransparentColor(RGB(0, 255, 0));
				mousePoint = { rt.right / 2, rt.bottom / 2 };
			}

			bullet.Load(L"bullet.bmp");
			bullet.SetTransparentColor(RGB(0, 255, 0));
			enemyBullet.Load(L"EnemyBullet.bmp");
			enemyBullet.SetTransparentColor(RGB(0, 255, 0));

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
			if (wParam == 'r' || wParam == 'R') {
				if (player->IsCurrentGunCanReload()) {
					player->ReloadCurrentGun();
					break;
				}
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
			if (player->IsCurrentGunOnReload()) {
				break;
			}
			if (player->GetCurrentGunBulletAmount() == 0) {
				player->ReloadCurrentGun();
				break;
			}
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
			KillTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER);
			SetTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER, ANIMATION_REFRESH_DURATION_PLAYER_ROLL, PlayerAnimationRefresh);
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