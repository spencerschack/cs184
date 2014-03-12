#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray {

public:

	Ray();

	Ray(Point position, Vector direction);

	Ray(Point position, Vector direction, float t_min, float t_max);

	Point position;
	
	Vector direction;

	float t_min, t_max;

};

#endif