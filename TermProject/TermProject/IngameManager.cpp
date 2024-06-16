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
	currentMapIdx = map->GetCurrentRoomIndex(player->GetPosition());
	int currentEnemyCount = 0;
	for (int i = 0; i < enemys.size(); i++) {
		if (enemys[i]->mapIndex == currentMapIdx - 1) {
			if (enemys[i]->GetMoveStatus() != Death) {
				currentEnemyCount += 1;
			}
			if (!enemys[i]->isActivate) {
				enemys[i]->isActivate = true;
			}
		}
		map->CheckMovableDirection(enemys[i]->checkMovableDirection, enemys[i]->GetPosition(), enemys[i]->GetHitboxRect());
	}
	if (currentEnemyCount > 0) {
		map->isOnCombat = true;
	}
	else {
		map->isOnCombat = false;
	}

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
	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("PF스타더스트 Bold"));
	oldFont = (HFONT)SelectObject(mDC, hFont);

	if (!isGamePaused) {
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
				if (IsCollide(player->GetHitboxRect(), bullets[j]->GetHitboxRect()) && bullets[j]->IsHostile() && !player->IsRolling()) {
					player->GetDamge(1);
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

		HPEN hPen = (HPEN)SelectObject(mDC, CreatePen(PS_SOLID, 0, RGB(0, 0, 0)));
		HBRUSH hBrush = (HBRUSH)SelectObject(mDC, CreateSolidBrush(RGB(0, 0, 0)));
		Rectangle(mDC, bulletMountRt.left, bulletMountRt.top, bulletMountRt.right, bulletMountRt.bottom);
		SetBkColor(mDC, RGB(0, 0, 0));
		SetTextColor(mDC, RGB(255, 255, 255));
		TCHAR bulletMount[20];
		switch (player->GetCurrentGunType()) {
			case AutoHandgun: {
				DrawText(mDC, L"자동권총", 4, &bulletMountRt, DT_LEFT | DT_TOP | DT_SINGLELINE);
				break;
			}
		}
		wsprintf(bulletMount, L"%d / %d", player->GetCurrentGunBulletAmount(), player->GetCurrentGunOriginBulletAmount());
		DrawText(mDC, bulletMount, -1, &bulletMountRt, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

		for (int i = 0; i < player->GetOriginHp() / 2; i++) {
			if (player->GetCurrentHp() - (i + 1) * 2 == -1)
				heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
			else if (player->GetCurrentHp() - (i + 1) * 2 <= -2)
				heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 2, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
			else
				heart.Draw(mDC, 20 + i * PLAYER_HEART_SIZE * 3, 20, PLAYER_HEART_SIZE * 3, PLAYER_HEART_SIZE * 3, 0, 0, PLAYER_HEART_SIZE, PLAYER_HEART_SIZE);
		}
	}

	else {
		DrawText(mDC, L"일시정지", lstrlen(L"일시정지"), &pausedRt, DT_CENTER | DT_TOP | DT_SINGLELINE);
		DrawText(mDC, L"메인화면으로 가려면 Q를 누르세요", lstrlen(L"메인화면으로 가려면 Q를 누르세요"), &pausedRt, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	}

	cursor.Draw(mDC, mousePoint.x - CURSOR_SIZE / 2, mousePoint.y - CURSOR_SIZE / 2, CURSOR_SIZE, CURSOR_SIZE);

	BitBlt(hDC, 0, 0, rt.right, rt.bottom, mDC, 0, 0, SRCCOPY);

	SelectObject(hDC, oldFont);
	DeleteObject(hFont);
	DeleteObject(hBitmap);
	DeleteDC(mDC);
}

void Game::Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene) {
	srand((unsigned int)time(NULL));

	switch (uMsg) {
	case WM_GAMESCENECHANGED: {
		hDC = GetDC(hWnd);
		GetClientRect(hWnd, &rt);

		isGamePaused = false;
		player = new Player();
		if (heart.IsNull())
			heart.Load(L"heart.bmp");
		heart.SetTransparentColor(RGB(0, 255, 0));

		SetTimer(hWnd, POSITION_REFRESH_ID, POSITION_REFRESH_DURATION, PositionRefresh);
		SetTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER, ANIMATION_REFRESH_DURATION, PlayerAnimationRefresh);

		if (cursor.IsNull()) {
			cursor.Load(L"Cursor.bmp");
			cursor.SetTransparentColor(RGB(0, 255, 0));
			mousePoint = { rt.right / 2, rt.bottom / 2 };
		}

		if (bullet.IsNull())
			bullet.Load(L"bullet.bmp");
		bullet.SetTransparentColor(RGB(0, 255, 0));
		if (enemyBullet.IsNull())
			enemyBullet.Load(L"EnemyBullet.bmp");
		enemyBullet.SetTransparentColor(RGB(0, 255, 0));

		player->SetCameraRelativePosition(mousePoint, rt);
		centerOffset = { player->GetCameraRelativePosition().x - player->GetPosition().x, player->GetCameraRelativePosition().y - player->GetPosition().y };

		map = new Map(hDC);
		for (int y = 0; y < map->mapSize.y; y++) {
			for (int x = 0; x < map->mapSize.x; x++) {
				switch (map->MonsterSpawnTileCheck({ x, y })) {
					case 1: {
						enemys.push_back(new Enemy(BulletJunior, 54 * x - 540, 54 * y - 540, y / 22));
						break;
					}
					case 10: {
						enemys.push_back(new Enemy(Boss, 54 * x - 540, 54 * y - 540, 10));
						break;
					}
				}
			}
		}
		for (int i = 0; i < enemys.size(); i++) {
			SetTimer(hWnd, ANIMATION_REFRESH_ID_ENEMY + i, ANIMATION_REFRESH_DURATION_ENEMY, EnemyAnimationRefresh);
			SetTimer(hWnd, AI_REFRESH_ID_ENEMY + i, AI_REFRESH_REFRESH_DURATION, EnemyAIRefresh);
		}
		currentMapIdx = 0;
		bulletMountRt = { rt.right - 200, rt.bottom - 60, rt.right, rt.bottom };
		pausedRt = { rt.left, rt.bottom / 2 - 150, rt.right, rt.bottom / 2 + 150 };
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
			if (wParam == VK_ESCAPE) {
				if (!isGamePaused) {
					isGamePaused = true;
					KillTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER);
					for (int i = 0; i < enemys.size(); i++) {
						KillTimer(hWnd, ANIMATION_REFRESH_ID_ENEMY + i);
						KillTimer(hWnd, AI_REFRESH_ID_ENEMY + i);
					}
				}
				else {
					isGamePaused = false;
					SetTimer(hWnd, ANIMATION_REFRESH_ID_PLAYER, ANIMATION_REFRESH_DURATION, PlayerAnimationRefresh);
					for (int i = 0; i < enemys.size(); i++) {
						SetTimer(hWnd, ANIMATION_REFRESH_ID_ENEMY + i, ANIMATION_REFRESH_DURATION_ENEMY, EnemyAnimationRefresh);
						SetTimer(hWnd, AI_REFRESH_ID_ENEMY + i, AI_REFRESH_REFRESH_DURATION, EnemyAIRefresh);
					}
				}
			}
			if (wParam == 'q' || wParam == 'Q') {
				if (isGamePaused) {
					*gameScene = MainMenu;
					DeleteObject(hDC);
					DeleteObject(mDC);
					DeleteObject(hBrush);
					DeleteObject(oldBrush);
					DeleteObject(hPen);
					DeleteObject(oldPen);
					DeleteObject(hBitmap);
					DeleteObject(hFont);
					DeleteObject(oldFont);
					for (int i = 0; i < enemys.size(); i++) {
						delete enemys[i];
					}
					enemys.clear();
					SendMessage(hWnd, WM_GAMESCENECHANGED, wParam, lParam);
				}
			}
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
			mousePoint = { LOWORD(lParam), HIWORD(lParam) };
			if (isGamePaused) {
				break;
			}
			if (player->IsCurrentGunOnReload() || player->IsRolling()) {
				break;
			}
			if (player->GetCurrentGunBulletAmount() == 0) {
				player->ReloadCurrentGun();
				break;
			}
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