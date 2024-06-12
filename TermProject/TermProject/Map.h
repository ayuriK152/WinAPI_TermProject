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
	POINT mapSize;
	vector<vector<bool>> pathData;
	vector<vector<int>> floorData;
	vector<vector<int>> ceilData;
	

public:
	vector<Room> rooms;
	CImage tilemapBmp;
	bool isTilemapLoaded;

	Map(HDC hDC);

	~Map();

	void CheckMovableDirection(bool flags[], POINT playerPosition, RECT playerHitbox);
	
	bool IsCollideWall(RECT hitbox);

	void DrawFloor(HDC hDC, POINT offset, RECT clientRt);

	void DrawCeil(HDC hDC, POINT offset, RECT rt);
};