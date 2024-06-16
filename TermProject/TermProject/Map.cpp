#include "Map.h"
#include "datas.h"
#include "values.h"

Room::Room(int mapDataNum) {
	roomIndex = mapDataNum;
	switch (mapDataNum) {
		case 0: {
			roomSize = { 22, 22 };
			drawOffset = { 0, 0 };

			for (int y = 0; y < 22; y++) {
				pathData.push_back({});
				floorData.push_back({});
				ceilData.push_back({});
				monsterData.push_back({});
				for (int x = 0; x < 22; x++) {
					pathData[y].push_back(MAP_DATA_INIT_PATH[y][x]);
					floorData[y].push_back(MAP_DATA_INIT_LAYER_FIRST[y][x]);
					ceilData[y].push_back(MAP_DATA_INIT_LAYER_SECOND[y][x]);
					monsterData[y].push_back(0);
				}
			}

			break;
		}
		case 1: {
			roomSize = { 22, 22 };
			drawOffset = { 0, 1 };

			for (int y = 0; y < 22; y++) {
				pathData.push_back({});
				floorData.push_back({});
				ceilData.push_back({});
				monsterData.push_back({});
				for (int x = 0; x < 22; x++) {
					pathData[y].push_back(MAP_DATA_NO1_PATH[y][x]);
					floorData[y].push_back(MAP_DATA_NO1_LAYER_FIRST[y][x]);
					ceilData[y].push_back(MAP_DATA_NO1_LAYER_SECOND[y][x]);
					monsterData[y].push_back(MAP_DATA_NO1_MONSTER[y][x]);
				}
			}

			break;
		}
		case 2: {
			roomSize = { 22, 22 };
			drawOffset = { 0, 1 };

			for (int y = 0; y < 22; y++) {
				pathData.push_back({});
				floorData.push_back({});
				ceilData.push_back({});
				monsterData.push_back({});
				for (int x = 0; x < 22; x++) {
					pathData[y].push_back(MAP_DATA_NO2_PATH[y][x]);
					floorData[y].push_back(MAP_DATA_NO2_LAYER_FIRST[y][x]);
					ceilData[y].push_back(MAP_DATA_NO2_LAYER_SECOND[y][x]);
					monsterData[y].push_back(MAP_DATA_NO1_MONSTER[y][x]);
				}
			}

			break;
		}
		case 3: {
			roomSize = { 22, 22 };
			drawOffset = { 0, 1 };

			for (int y = 0; y < 22; y++) {
				pathData.push_back({});
				floorData.push_back({});
				ceilData.push_back({});
				monsterData.push_back({});
				for (int x = 0; x < 22; x++) {
					pathData[y].push_back(MAP_DATA_NO3_PATH[y][x]);
					floorData[y].push_back(MAP_DATA_NO3_LAYER_FIRST[y][x]);
					ceilData[y].push_back(MAP_DATA_NO3_LAYER_SECOND[y][x]);
					monsterData[y].push_back(MAP_DATA_NO1_MONSTER[y][x]);
				}
			}

			break;
		}
	}
}

Room::~Room() {

}

void Map::CheckMovableDirection(bool flags[], POINT playerPosition, RECT playerHitbox) {
	if (pathData[(playerHitbox.top + 594) / 54][(playerPosition.x + 594) / 54] == 0) {
		flags[0] = true;
	}
	else {
		flags[0] = false;
	}
	if (pathData[(playerHitbox.bottom + 594) / 54][(playerPosition.x + 594) / 54] == 0) {
		flags[1] = true;
	}
	else {
		flags[1] = false;
	}
	if (pathData[(playerPosition.y + 594) / 54][(playerHitbox.left + 594) / 54] == 0) {
		flags[2] = true;
	}
	else {
		flags[2] = false;
	}
	if (pathData[(playerPosition.y + 594) / 54][(playerHitbox.right + 594) / 54] == 0) {
		flags[3] = true;
	}
	else {
		flags[3] = false;
	}
}

bool Map::IsCollideWall(RECT hitbox) {
	if (pathData[(hitbox.top + 594) / 54][(hitbox.left + 594) / 54] == 0 ||
		pathData[(hitbox.top + 594) / 54][(hitbox.right + 594) / 54] == 0 ||
		pathData[(hitbox.bottom + 594) / 54][(hitbox.left + 594) / 54] == 0 ||
		pathData[(hitbox.bottom + 594) / 54][(hitbox.right + 594) / 54] == 0)
		return true;
	return false;
}

Map::Map(HDC hDC) {
	mapSize = { 22, 22 };
	tilemapBmp.Load(L"TileMap.bmp");

	rooms.push_back(Room(0));
	rooms.push_back(1);

	POINT drawOffset = { 0, 0 };
	for (int i = 0; i < rooms.size(); i++) {
		mapSize = { mapSize.x + (rooms[i].roomSize.x * rooms[i].drawOffset.x), mapSize.y + (rooms[i].roomSize.y * rooms[i].drawOffset.y) };
		drawOffset = { drawOffset.x + rooms[i].drawOffset.x, drawOffset.y + rooms[i].drawOffset.y };
		for (int y = 0; y < rooms[i].roomSize.y; y++) {
			pathData.push_back({});
			floorData.push_back({});
			ceilData.push_back({});
			monsterData.push_back({});
			for (int x = 0; x < rooms[i].roomSize.x; x++) {
				pathData[y + drawOffset.y * 22].push_back(rooms[i].pathData[y][x]);
				floorData[y + drawOffset.y * 22].push_back(rooms[i].floorData[y][x]);
				ceilData[y + drawOffset.y * 22].push_back(rooms[i].ceilData[y][x]);
				monsterData[y + drawOffset.y * 22].push_back(rooms[i].monsterData[y][x]);
			}
		}
	}

	HBITMAP hBitmap = CreateCompatibleBitmap(hDC, 54 * mapSize.x, 54 * mapSize.y);
	mapFloorMemDC = CreateCompatibleDC(hDC);

	SelectObject(mapFloorMemDC, hBitmap);
	for (int y = 0; y < 18; y++) {
		for (int x = 0; x < 20; x++) {
			tilemapBmp.Draw(mapFloorMemDC, (x + 1) * 54, (y + 3) * 54, 54, 54, TILEMAP_OFFSET_INITPLACE_START.x + x * 18, TILEMAP_OFFSET_INITPLACE_START.y + y * 18, 18, 18);
		}
	}
	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			if (floorData[y][x] == -1)
				continue;
			tilemapBmp.Draw(mapFloorMemDC, x * 54, y * 54, 54, 54, floorData[y][x] * 18, 0, 18, 18);
		}
	}

	DeleteObject(hBitmap);

	hBitmap = CreateCompatibleBitmap(hDC, 54 * mapSize.x, 54 * mapSize.y);
	mapWallMemDC = CreateCompatibleDC(hDC);
	SelectObject(mapWallMemDC, hBitmap);

	for (int y = 0; y < mapSize.y; y++) {
		for (int x = 0; x < mapSize.x; x++) {
			if (ceilData[y][x] == -1)
				continue;
			tilemapBmp.Draw(mapWallMemDC, x * 54, y * 54, 54, 54, ceilData[y][x] * 18, 0, 18, 18);
		}
	}

	DeleteObject(hBitmap);
}

Map::~Map() {
	for (int i = 0; i < rooms.size(); i++) {
		rooms[i].~Room();
	}
	DeleteObject(mapFloorMemDC);
	DeleteObject(mapWallMemDC);
}

int Map::GetCurrentRoomIndex(POINT playerPosition) {
	return pathData[(playerPosition.y + 594) / 54][(playerPosition.x + 594) / 54];
}

void Map::DrawFloor(HDC hDC, POINT offset, RECT rt) {
	StretchBlt(hDC, 0, 0, rt.right, rt.bottom, mapFloorMemDC, -(offset.x - 594), -(offset.y - 594), rt.right, rt.bottom, SRCCOPY);
}

void Map::DrawCeil(HDC hDC, POINT offset, RECT rt) {
	StretchBlt(hDC, 0, 0, rt.right, rt.bottom, mapWallMemDC, -(offset.x - 594), -(offset.y - 594), rt.right, rt.bottom, SRCPAINT);
}

int Map::MonsterSpawnTileCheck(POINT position) {
	return monsterData[position.y][position.x];
}