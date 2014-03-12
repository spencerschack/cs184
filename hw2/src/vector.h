#ifndef VECTOR_H
#define VECTOR_H

class Vector {

public:

	Vector();

	Vector(float x, float y, float z);

	Vector(const Vector& vector);

	float x, y, z;

	Vector operator+(const Vector& vector);

	Vector operator-(const Vector& vector);

	Vector operator*(float factor);

	Vector operator/(float divisor);

	float dot(const Vector& vector);

	Vector cross(const Vector& vector);

	float magnitude();

};

#endif