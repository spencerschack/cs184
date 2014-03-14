#ifndef VECTOR_H
#define VECTOR_H

class Vector {

public:

	Vector();

	Vector(float x, float y, float z);

	Vector(const Vector& vector);

	float x, y, z;

	void print();

	Vector operator=(const Vector& vector);

	Vector operator+(const Vector& vector) const;

	Vector operator-(const Vector& vector) const;

	Vector operator-() const;

	Vector operator*(float factor) const;

	Vector operator/(float divisor) const;

	float dot(const Vector& vector) const;

	Vector cross(const Vector& vector) const;

	float magnitude() const;

	void normalize();

};

#endif