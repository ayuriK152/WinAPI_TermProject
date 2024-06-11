#pragma once
#include <atlimage.h>
#include <vector>

using namespace std;

class Room {
private:
	int** mapPath;
	int** mapLayer[2];

public:
	int roomIndex;
	POINT roomSize;

	Room(int mapDataNum);

	~Room();
};

class Map {
private:
	int mapDataNum;
	int** mapData;
	HDC mapMemDC[2];
	POINT mapSize;
	vector<Room> rooms;
	

public:
	CImage tilemapBmp;
	bool isTilemapLoaded;

	Map(HDC hDC);

	~Map();

	void DrawFloor(HDC hDC, POINT offset, RECT clientRt);
};