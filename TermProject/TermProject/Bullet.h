#pragma once
#include <wtypes.h>

class Bullet {
private:
	int speed;
	double angle;
	bool isHostile;
	POINT position;
	POINT size;
	RECT hitboxRect;

public:
	Bullet(POINT startPosition, POINT size, int speed, double angle, bool isHostile);

	~Bullet();

	void Move();

	POINT GetPosition();

	RECT GetHitboxRect();

	bool IsHostile();
};
