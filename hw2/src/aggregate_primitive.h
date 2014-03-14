#ifndef AGGREGATE_PRIMITIVE_H
#define AGGREGATE_PRIMITIVE_H

#include <vector>
#include <limits>

#include "primitive.h"

using namespace std;

class AggregatePrimitive {

public:

	vector<Primitive*> primitives;

	bool intersect(Ray& ray, float& t_hit, Intersection& in);

	void getBRDF(LocalGeo& local, BRDF& brdf);

};

#endif