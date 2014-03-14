#include "aggregate_primitive.h"

bool AggregatePrimitive::intersect(Ray& ray, float& t_hit, Intersection& in) {
	int len = primitives.size(), i;
	float t_min = std::numeric_limits<float>::infinity(), t_test;
	Intersection in_min, in_test;
	bool intersected = false;
	for (i = 0; i < len; i++) {
		if (primitives[i]->intersect(ray, t_test, in_test)) {
			intersected = true;
			if(t_test < t_min) {
				t_min = t_test;
				in_min = in_test;
			}
		}
	}
	if(intersected) {
		in = in_min;
		t_hit = t_min;
		return true;
	}
	return false;
}

void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF& brdf) {
	exit(1);
}