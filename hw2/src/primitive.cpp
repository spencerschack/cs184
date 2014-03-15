#include "primitive.h"
#include "intersection.h"

Primitive::Primitive() { };

bool Primitive::intersect(const Ray& ray, const Primitive* ignore) const {
	float t_hit;
	Intersection in;
	return intersect(ray, t_hit, in, ignore);
}
