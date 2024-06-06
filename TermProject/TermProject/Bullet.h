#pragma once
#include <wtypes.h>

class Bullet {
private:
	int speed;
	double angle;
	POINT position;

public:
	Bullet(POINT position, int speed, double angle);

	~Bullet();

	void Move();

	POINT GetPosition();
};
