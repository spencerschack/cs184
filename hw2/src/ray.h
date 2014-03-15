#ifndef RAY_H
#define RAY_H

#include <limits>

#include "point.h"
#include "vector.h"
#include "local_geo.h"

using namespace std;

class Ray {

public:

	Ray();

	Ray(Point& position, Vector& direction);

	Ray(Point& position, Vector& direction, float t_min, float t_max);

	Point position;
	
	Vector direction;

	float t_min = 0.00001, t_max = numeric_limits<float>::infinity();

	Ray reflect(const LocalGeo& local) const;

};

#endif