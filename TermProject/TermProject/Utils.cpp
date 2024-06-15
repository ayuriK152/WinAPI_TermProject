#include "Utils.h"

double DistanceByPoint(POINT p1, POINT p2) {
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double TanByPoint(POINT p1, POINT p2) {
	return (double)(p2.y - p1.y) / (p2.x - p1.x);
}

bool IsCollide(RECT rt1, RECT rt2) {
	if (rt1.left < rt2.right && rt1.right > rt2.left && rt1.top < rt2.bottom && rt1.bottom > rt2.top)
		return true;
	return false;
}