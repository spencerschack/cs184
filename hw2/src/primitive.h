#ifndef PRIMITIVE_H
#define PRIMITIVE_H

// Forward declare primitive because it is used in intersection.h.
class Primitive;

#include "ray.h"
#include "intersection.h"
#include "local_geo.h"
#include "brdf.h"

class Primitive {

public:

	bool intersect(Ray& ray, float& t_hit, Intersection& in);

	void getBRDF(LocalGeo& local, BRDF& brdf);

};

#endif