#ifndef POINT_H
#define POINT_H

#include "vector.h"

class Point {

public:

	float x, y, z;

	Point();

	Point(float x, float y, float z);

	Vector operator-(Point point);

	Point operator+(Vector vector);

};

#endif