#include <cmath>

#include "vector.h"

Vector::Vector() : x(0), y(0), z(0) { };

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) { };

Vector::Vector(const Vector& vector) : x(vector.x), y(vector.y), z(vector.z) { };

void Vector::print() {
	printf("Vector<x: %f, y: %f, z: %f>\n", x, y, z);
}

Vector Vector::operator=(const Vector& vector) {
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

Vector Vector::operator+(const Vector& vector) {
	return Vector(x + vector.x, y + vector.y, z + vector.z);
};

Vector Vector::operator-(const Vector& vector) {
	return Vector(x - vector.x, y - vector.y, z - vector.z);
};

Vector Vector::operator-() {
	return Vector(-x, -y, -z);
}

Vector Vector::operator*(float factor) {
	return Vector(x * factor, y * factor, z * factor);
};

Vector Vector::operator/(float divisor) {
	return Vector(x / divisor, y / divisor, z / divisor);
};

float Vector::dot(const Vector& vector) {
	return x * vector.x + y * vector.y + z * vector.z;
}

Vector Vector::cross(const Vector& vector) {
	return Vector(
		y * vector.z - z * vector.y,
		-x * vector.z + z * vector.x,
		x * vector.y - y * vector.x);
}

float Vector::magnitude() {
	return sqrt(x * x + y * y + z * z);
}

void Vector::normalize() {
	float mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}
