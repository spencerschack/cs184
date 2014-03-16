#include <cmath>

#include "normal.h"
#include "vector.h"

Normal::Normal() : x(0), y(0), z(0) { };

Normal::Normal(const Vector& vector) : x(vector.x), y(vector.y), z(vector.z) {
	normalize();
};

Normal::Normal(const Normal& normal) : x(normal.x), y(normal.y), z(normal.z) { };

void Normal::print() const {
	printf("Normal<x: %f, y: %f, z: %f>\n", x, y, z);
}

Normal Normal::operator=(const Normal& normal) {
	x = normal.x;
	y = normal.y;
	z = normal.z;
	return *this;
}

Normal Normal::operator+(const Normal& normal) const {
	return Normal(x + normal.x, y + normal.y, z + normal.z);
}

Normal Normal::operator-() const {
	return Normal(-x, -y, -z);
}

Normal Normal::operator-(const Normal& normal) const {
	return Normal(x - normal.x, y - normal.y, z - normal.z);
}

Vector Normal::operator*(float factor) const {
	return Vector(x * factor, y * factor, z * factor);
}

float Normal::dot(const Normal& normal) const {
	return x * normal.x + y * normal.y + z * normal.z;
}

Normal Normal::cross(const Normal& normal) const {
	return Normal(
		y * normal.z - z * normal.y,
		-x * normal.z + z * normal.x,
		x * normal.y - y * normal.x);
}

Normal Normal::reflect(const Normal& normal) const {
	return Normal(normal * dot(normal) * 2 - Vector(x, y, z));
}

void Normal::normalize() {
	float mag = sqrt(x * x + y * y + z * z);
	if(mag == 0) { return; }
	x /= mag;
	y /= mag;
	z /= mag;
}

float Normal::angle_with(const Vector& vector) const {
	return acos(dot(vector) / vector.magnitude());
}
