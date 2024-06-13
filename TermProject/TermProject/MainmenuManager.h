#pragma once

#include <Windows.h>
#include "datas.h"

namespace Menu {
	void Play(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, GameScene* gameScene);
}