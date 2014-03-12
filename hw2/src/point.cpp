#include "point.h"

Point::Point() : x(0), y(0), z(0) { };

Point::Point(float x, float y, float z) : x(x), y(y), z(z) { };

Vector Point::operator-(Point point) {
	return Vector(x - point.x, y - point.y, z - point.z);
};

Point Point::operator+(Vector vector) {
	return Point(x + vector.x, y + vector.y, z + vector.z);
}
