#ifndef AGGREGATE_PRIMITIVE_H
#define AGGREGATE_PRIMITIVE_H

#include <vector>
#include <limits>

#include "primitive.h"

using namespace std;

class AggregatePrimitive : public Primitive {

public:

	vector<Primitive*> primitives;

	bool intersect(const Ray& ray, float& t_hit, Intersection& in, const Primitive* ignore) const;

	bool intersect(const Ray& ray, const Primitive* ignore) const;

	void getBRDF(LocalGeo& local, BRDF& brdf) const;

};

#endif