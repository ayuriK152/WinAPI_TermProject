#pragma once

#include <windows.h>
#include <math.h>

double DistanceByPoint(POINT p1, POINT p2);

double TanByPoint(POINT p1, POINT p2);

bool IsCollide(RECT rt1, RECT rt2);