#include "Map.h"
#include "datas.h"
#include "values.h"

Room::Room(int mapDataNum) {
	switch (mapDataNum) {
		case 0: {
			roomSize = { 20, 22 };
			mapPath = new int* [20];
			for (int y = 0; y < 20; y++) {
				mapPath[y] = new int[22];
			}

			for (int y = 0; y < 20; y++) {
				for (int x = 0; x < 18; x++) {
					mapPath[y][x] = MAP_DATA_INIT_PATH[y][x];
				}
			}
			break;
		}
	}
}

Room::~Room() {

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
	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, rt.right, rt.bottom);
	mapMemDC[0] = CreateCompatibleDC(hDC);
	SelectObject(mapMemDC[0], hBitmap);

	for (int i = 0; i < rooms.size(); i++) {
		if (i == 0) {
			for (int y = 0; y < rooms[i].roomSize.y; y++) {
				for (int x = 0; x < rooms[i].roomSize.x; x++) {
					tilemapBmp.Draw(mapMemDC[0], x * 54, y * 54, 54, 54, TILEMAP_OFFSET_INITPLACE_START.x + x * 18, TILEMAP_OFFSET_INITPLACE_START.y + y * 18, 18, 18);
				}
			}
		}
		else {
			for (int y = 0; y < rooms[i].roomSize.y; y++) {
				for (int x = 0; x < rooms[i].roomSize.x; x++) {
					tilemapBmp.Draw(mapMemDC[0], x * 54, y * 54, 54, 54, MAP_DATA_FIRST[y][x] * 18, 0, 18, 18);
				}
			}
		}
	}

	StretchBlt(hDC, 0, 0, rt.right, rt.bottom, mapMemDC[0], -offset.x - 270, -offset.y, rt.right, rt.bottom, SRCCOPY);
	DeleteObject(hBitmap);
	DeleteObject(mapMemDC[0]);
}