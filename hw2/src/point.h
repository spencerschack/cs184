#ifndef POINT_H
#define POINT_H

#include "vector.h"

class Point {

public:

	float x, y, z;

	Point();

	Point(float x, float y, float z);

	void print() const;

	Vector operator-(const Point& point) const;

	Point operator+(const Vector& vector) const;

	Point operator=(const Point& point);

};

#endif