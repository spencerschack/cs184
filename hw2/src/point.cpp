#include "point.h"

Point::Point() : x(0), y(0), z(0) { };

Point::Point(float x, float y, float z) : x(x), y(y), z(z) { };

void Point::print() const {
	printf("Point<x: %f, y: %f, z: %f>\n", x, y, z);
}

Vector Point::operator-(const Point& point) const {
	return Vector(x - point.x, y - point.y, z - point.z);
};

Point Point::operator+(const Vector& vector) const {
	return Point(x + vector.x, y + vector.y, z + vector.z);
}

Point Point::operator=(const Point& point) {
	x = point.x;
	y = point.y;
	z = point.z;
	return *this;
}
