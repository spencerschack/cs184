#include <cmath>

#include "vector.h"

Vector::Vector() : x(0), y(0), z(0) { };

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) { };

Vector::Vector(const Vector& vector) : x(vector.x), y(vector.y), z(vector.z) { };

void Vector::print() const {
	printf("Vector<x: %f, y: %f, z: %f>\n", x, y, z);
}

Vector Vector::operator=(const Vector& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

Vector Vector::operator+(const Vector& vector) const {
	return Vector(x + vector.x, y + vector.y, z + vector.z);
};

Vector Vector::operator-(const Vector& vector) const {
	return Vector(x - vector.x, y - vector.y, z - vector.z);
};

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

Vector Vector::operator*(float factor) const {
	return Vector(x * factor, y * factor, z * factor);
};

Vector Vector::operator/(float divisor) const {
	return Vector(x / divisor, y / divisor, z / divisor);
};

float Vector::dot(const Vector& vector) const {
	return x * vector.x + y * vector.y + z * vector.z;
}

Vector Vector::cross(const Vector& vector) const {
	return Vector(
		y * vector.z - z * vector.y,
		-x * vector.z + z * vector.x,
		x * vector.y - y * vector.x);
}

float Vector::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

void Vector::normalize() {
	float mag = magnitude();
	if(mag == 0) { return; }
	x /= mag;
	y /= mag;
	z /= mag;
}
