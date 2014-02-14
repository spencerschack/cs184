#include <cmath>

class Vector {

public:

	float x, y, z;

	Vector() : x(0), y(0), z(0) { }

	Vector(float x, float y, float z) : x(x), y(y), z(z) { }

	Vector(Vector* vector) {
		x = vector->x;
		y = vector->y;
		z = vector->z;
	}

	void print() {
		printf("Vector<x: %f, y: %f, z: %f>\n", x, y, z);
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

	float dot(Vector* vector) {
		return x * vector->x +
		       y * vector->y +
		       z * vector->z;
	}

	Vector* cross(Vector* vector) {
		return new Vector(
			y * vector->z - z * vector->y,
			-x * vector->z + z * vector->x,
			x * vector->y - y * vector->x
		);
	}

	Vector* reflect(Vector* vector) {
		float coeff = dot(vector) * 2;
		Vector* reflection = new Vector(vector);
		*reflection *= coeff;
		*reflection -= this;
		return reflection;
	}

};