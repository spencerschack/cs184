#include <cmath>

class Normal {

public:

	float x, y, z;

	Normal () { }

	Normal(Vector* vector) {
		x = vector->x;
		y = vector->y;
		z = vector->z;
		normalize();
	}

	Normal(float x, float y, float z) : x(x), y(y), z(z) {
		normalize();
	}

	Normal(Normal* normal) {
		x = normal->x;
		y = normal->y;
		z = normal->z;
	}

	Vector* vector() {
		return new Vector(x, y, z);
	}

	void print() {
		printf("Normal<x: %f, y: %f, z: %f>\n", x, y, z);
	}

	Normal* operator+(Normal* normal) {
		return *new Normal(this) += normal;
	}

	Normal* operator+=(Normal* normal) {
		x += normal->x;
		y += normal->y;
		z += normal->z;
		normalize();
		return this;
	}

	Normal* operator-(Normal* normal) {
		return *new Normal(this) -= normal;
	}

	Normal* operator-=(Normal* normal) {
		x -= normal->x;
		y -= normal->y;
		z -= normal->z;
		normalize();
		return this;
	}

	Normal* operator*=(float factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		normalize();
		return this;
	}

	Normal* operator*(float factor) {
		return *new Normal(this) *= factor;
	}

	float dot(Normal* normal) {
		return x * normal->x +
		       y * normal->y +
		       z * normal->z;
	}

	float dot(Vector* vector) {
		return x * vector->x +
		       y * vector->y +
		       z * vector->z;
	}

private:

	void operator/=(float divisor) {
		x /= divisor;
		y /= divisor;
		z /= divisor;
	}

	float magnitude() {
		return sqrt(x * x + y * y + z * z);
	}

	void normalize() {
		*this /= magnitude();
	}

};