#include "primitive.h"

Primitive::Primitive() { };

bool Primitive::intersect(const Ray& ray, float& t_hit, Intersection& in) {
	printf("Primitive::intersect should not be called.\n");
	exit(1);
}

void Primitive::getBRDF(LocalGeo& local, BRDF& brdf) {
	printf("Primitive::getBRDF should not be called.\n");
	exit(1);
}
