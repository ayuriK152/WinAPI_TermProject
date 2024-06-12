#pragma once
#include <wtypes.h>

class Bullet {
private:
	int speed;
	double angle;
	POINT position;
	POINT size;
	RECT hitboxRect;

public:
	Bullet(POINT position, POINT size, int speed, double angle);

	~Bullet();

	void Move();

	POINT GetPosition();

	RECT GetHitboxRect();
};
