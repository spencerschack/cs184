#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {

public:

	Ray();

	Ray(Vector position, Vector direction);

	Ray(Vector position, Vector direction, float t_min, float t_max);

	Vector position, direction;

	float t_min, t_max;

};

#endif