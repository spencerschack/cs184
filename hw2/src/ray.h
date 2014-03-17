#ifndef RAY_H
#define RAY_H

#include "point.h"
#include "vector.h"
#include "local_geo.h"

using namespace std;

class Ray {

public:

	Ray();

	Point position;
	
	Vector direction;

	float t_min, t_max;

	Ray reflect(const LocalGeo& local) const;

};

#endif