#include "triangle_n.h"

TriangleN::TriangleN(LocalGeo x, LocalGeo y, LocalGeo z) : x(x), y(y), z(z) { };

bool TriangleN::intersect(Ray& ray, float& t_hit, LocalGeo& local) const {
	return false;
};