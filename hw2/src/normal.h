#ifndef NORMAL_H
#define NORMAL_H

#include "vector.h"

class Normal {

public:

	float x, y, z;

	Normal();

	Normal(float x, float y, float z) : x(x), y(y), z(z) { };

	Normal(Vector* vector);

	Normal(Normal* vector);

	Normal operator+(Normal normal);

	Normal operator-(Normal normal);

	Normal cross(Normal normal);

private:

	void normalize();

};

#endif