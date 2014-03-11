#ifndef VECTOR_H
#define VECTOR_H

class Vector {

public:

	Vector();

	Vector(float x, float y, float z);

	Vector(Vector* vector);

	float x, y, z;

	Vector operator+(Vector vector);

	Vector operator-(Vector vector);

	Vector operator*(float factor);

	Vector operator/(float divisor);

	float dot(Vector vector);

	Vector cross(Vector vector);

	float magnitude();

};

#endif