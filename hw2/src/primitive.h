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

	Primitive();

	virtual bool intersect(const Ray& ray, float& t_hit, Intersection& in, const Primitive* ignore) const = 0;

	bool intersect(const Ray& ray, const Primitive* ignore) const;

	virtual void getBRDF(LocalGeo& local, BRDF& brdf) const = 0;

};

#endif