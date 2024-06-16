#pragma once
#include <atlimage.h>
#include <vector>

using namespace std;

class Passage {

};

class Room {
public:
	vector<vector<int>> pathData;
	vector<vector<int>> floorData;
	vector<vector<int>> ceilData;
	vector<vector<int>> monsterData;
	int roomIndex;
	POINT roomSize;
	POINT drawOffset;

	Room(int mapDataNum);

	~Room();
};

class Map {
private:
	HDC mapFloorMemDC;
	HDC mapWallMemDC;
	vector<vector<int>> pathData;
	vector<vector<int>> floorData;
	vector<vector<int>> ceilData;
	vector<vector<int>> monsterData;
	

public:
	vector<Room> rooms;
	POINT mapSize;
	CImage tilemapBmp;
	bool isTilemapLoaded;

	Map(HDC hDC);

	~Map();

	void CheckMovableDirection(bool flags[], POINT playerPosition, RECT playerHitbox);

	int GetCurrentRoomIndex(POINT playerPosition);
	
	bool IsCollideWall(RECT hitbox);

	void DrawFloor(HDC hDC, POINT offset, RECT clientRt);

	void DrawCeil(HDC hDC, POINT offset, RECT rt);

	int MonsterSpawnTileCheck(POINT position);
};