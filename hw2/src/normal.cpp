#include <cmath>

#include "normal.h"
#include "vector.h"

Normal::Normal() : x(0), y(0), z(0) { };

Normal::Normal(const Vector& vector) : x(vector.x), y(vector.y), z(vector.x) {
	normalize();
};

Normal::Normal(const Normal& normal) : x(normal.x), y(normal.y), z(normal.x) { };

Normal Normal::operator=(const Normal& normal) {
	x = normal.x;
	y = normal.y;
	z = normal.z;
	return *this;
}

Normal Normal::operator+(const Normal& normal) {
	return Normal(x + normal.x, y + normal.y, z + normal.z);
}

Normal Normal::operator-(const Normal& normal) {
	return Normal(x - normal.x, y - normal.y, z - normal.z);
}

Vector Normal::operator*(float factor) {
	return Vector(x * factor, y * factor, z * factor);
}

Normal Normal::cross(const Normal& normal) {
	return Normal(
		y * normal.z - z * normal.y,
		-x * normal.z + z * normal.x,
		x * normal.y - y * normal.x);
}

void Normal::normalize() {
	float mag = sqrt(x * x + y * y + z * z);
	if(mag == 0) { return; }
	x /= mag;
	y /= mag;
	z /= mag;
}
