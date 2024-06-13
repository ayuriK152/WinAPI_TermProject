#include <math.h>
#include "Bullet.h"

Bullet::Bullet(POINT position, POINT size, int speed, double angle, bool isHostile) {
	this->position = position;
	this->size = size;
	this->speed = speed;
	this->angle = angle;
	this->isHostile = isHostile;
}

Bullet::~Bullet() {

}

void Bullet::Move() {
	position.x -= (int)(sin(angle) * speed);
	position.y -= (int)(cos(angle) * speed);
	hitboxRect = {
		position.x - size.x / 2,
		position.y - size.y / 2,
		position.x + size.x / 2,
		position.y + size.y / 2
	};
}

POINT Bullet::GetPosition() {
	return position;
}

RECT Bullet::GetHitboxRect() {
	return hitboxRect;
}