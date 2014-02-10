#include <cmath>

class Vector {

	float x, y, z;

	Vector(float x, float y, float z) : x(x), y(y), z(z) { }

	Vector(Vector* vector) {
		x = vector->x;
		y = vector->y;
		z = vector->z;
	}

	Vector* operator+(Vector* vector) {
		return *new Vector(this) += vector;
	}

	Vector* operator+=(Vector* vector) {
		x += vector->x;
		y += vector->y;
		z += vector->z;
		return this;
	}

	Vector* operator-(Vector* vector) {
		return *new Vector(this) -= vector;
	}

	Vector* operator-=(Vector* vector) {
		x -= vector->x;
		y -= vector->y;
		z -= vector->z;
		return this;
	}

	Vector* operator*(float factor) {
		return *new Vector(this) *= factor;
	}

	Vector* operator*=(float factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		return this;
	}

	Vector* operator/(float divisor) {
		return *new Vector(this) /= divisor;
	}

	Vector* operator/=(float divisor) {
		x /= divisor;
		y /= divisor;
		z /= divisor;
		return this;
	}

	float magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	Vector* normalized() {
		return (new Vector(this))->normalize();
	}

	Vector* normalize() {
		return *this /= magnitude();
	}

};