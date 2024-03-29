#include "aggregate_primitive.h"

bool AggregatePrimitive::intersect(const Ray& ray, float& t_hit, Intersection& in, const Primitive* ignore) const {
	int len = primitives.size(), i;
	float t_min = std::numeric_limits<float>::infinity(), t_test;
	Intersection in_min, in_test;
	bool intersected = false;
	for(i = 0; i < len; i++) {
		if(primitives[i]->intersect(ray, t_test, in_test, ignore)) {
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

bool AggregatePrimitive::intersect(const Ray& ray, const Primitive* ignore) const {
	return Primitive::intersect(ray, ignore);
}

void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF& brdf) const {
	printf("AggregatePrimitive::getBRDF should not be called.\n");
	exit(1);
}