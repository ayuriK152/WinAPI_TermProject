#include <math.h>
#include "Bullet.h"

Bullet::Bullet(POINT position, int speed, double angle) {
	this->position = position;
	this->speed = speed;
	this->angle = angle;
}

Bullet::~Bullet() {

}

void Bullet::Move() {
	position.x -= (int)(sin(angle) * speed);
	position.y -= (int)(cos(angle) * speed);
}

POINT Bullet::GetPosition() {
	return position;
}