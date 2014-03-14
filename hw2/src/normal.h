#ifndef NORMAL_H
#define NORMAL_H

#include "vector.h"

class Normal {

public:

	float x, y, z;

	Normal();

	Normal(float x, float y, float z) : x(x), y(y), z(z) { };

	Normal(const Vector& vector);

	Normal(const Normal& vector);

	Normal operator=(const Normal& normal);

	Normal operator+(const Normal& normal) const;

	Normal operator-(const Normal& normal) const;

	Vector operator*(float factor) const;

	float dot(const Normal& normal) const;

	Normal cross(const Normal& normal) const;

	Normal reflect(const Normal& normal) const;

	void normalize();

};

#endif