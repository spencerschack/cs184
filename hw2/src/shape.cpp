#include "shape.h"

Shape::Shape() { };

bool Shape::intersect(Ray& ray, float& t_hit, LocalGeo& local) {
	return false;
};

void Shape::getBRDF(LocalGeo& local, BRDF& brdf1) {
	brdf1 = brdf;
};