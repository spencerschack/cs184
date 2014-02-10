#include <cmath>

class Normal {

	float x, y, z;

	Normal(float x, float y, float z) : x(x), y(y), z(z) { }

	Normal(Normal* normal) {
		x = normal->x;
		y = normal->y;
		z = normal->z;
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