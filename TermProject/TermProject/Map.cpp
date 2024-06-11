#include "Map.h"
#include "datas.h"
#include "values.h"

Room::Room(int mapDataNum) {
	switch (mapDataNum) {
		case 0: {
			roomSize = { 22, 20 };
			mapPath = new int* [20];
			for (int y = 0; y < 20; y++) {
				mapPath[y] = new int[22];
			}

			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 22; x++) {
					mapPath[y][x] = MAP_DATA_INIT_PATH[y][x];
				}
			}

			break;
		}
	}
}

Room::~Room() {

}

void Room::CheckMovableDirection(bool flags[], POINT playerPosition, RECT playerHitbox) {
	if (MAP_DATA_INIT_PATH[(playerHitbox.top + 594) / 54][(playerPosition.x + 594) / 54] == 0) {
		flags[0] = true;
	}
	else {
		flags[0] = false;
	}
	if (MAP_DATA_INIT_PATH[(playerHitbox.bottom + 594) / 54][(playerPosition.x + 594) / 54] == 0) {
		flags[1] = true;
	}
	else {
		flags[1] = false;
	}
	if (MAP_DATA_INIT_PATH[(playerPosition.y + 594) / 54][(playerHitbox.left + 594) / 54] == 0) {
		flags[2] = true;
	}
	else {
		flags[2] = false;
	}
	if (MAP_DATA_INIT_PATH[(playerPosition.y + 594) / 54][(playerHitbox.right + 594) / 54] == 0) {
		flags[3] = true;
	}
	else {
		flags[3] = false;
	}
}

Map::Map(HDC hDC) {
	this->mapDataNum = mapDataNum;
	mapSize = { 3, 3 };
	tilemapBmp.Load(L"TileMap.bmp");

	rooms.push_back(Room(0));
}

Map::~Map() {
	for (int i = 0; i < rooms.size(); i++) {
		rooms[i].~Room();
	}
}

void Map::DrawFloor(HDC hDC, POINT offset, RECT rt) {
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, 54 * 30, 54 * 30);
	mapMemDC = CreateCompatibleDC(hDC);
	SelectObject(mapMemDC, hBitmap);

	for (int i = 0; i < rooms.size(); i++) {
		if (i == 0) {
			for (int y = 0; y < rooms[i].roomSize.y - 2; y++) {
				for (int x = 0; x < rooms[i].roomSize.x - 2; x++) {
					tilemapBmp.Draw(mapMemDC, (x + 1) * 54, (y + 3) * 54, 54, 54, TILEMAP_OFFSET_INITPLACE_START.x + x * 18, TILEMAP_OFFSET_INITPLACE_START.y + y * 18, 18, 18);
				}
			}
		}
		else {
			for (int y = 0; y < rooms[i].roomSize.y - 2; y++) {
				for (int x = 0; x < rooms[i].roomSize.x - 2; x++) {
					tilemapBmp.Draw(mapMemDC, x * 54, y * 54, 54, 54, MAP_DATA_FIRST[y][x] * 18, 0, 18, 18);
				}
			}
		}
	}

	for (int i = 0; i < rooms.size(); i++) {
		for (int y = 0; y < rooms[i].roomSize.y + 2; y++) {
			for (int x = 0; x < rooms[i].roomSize.x; x++) {
				if (MAP_DATA_INIT_LAYER_FIRST[y][x] == -1)
					continue;
				tilemapBmp.Draw(mapMemDC, x * 54, y * 54, 54, 54, MAP_DATA_INIT_LAYER_FIRST[y][x] * 18, 0, 18, 18);
			}
		}
	}

	StretchBlt(hDC, 0, 0, rt.right, rt.bottom, mapMemDC, -(offset.x - 594), -(offset.y - 594), rt.right, rt.bottom, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteObject(mapMemDC);
}