#include <limits>

#include "ray.h"
#include "vector.h"

Ray::Ray() : t_min(0.00001), t_max(numeric_limits<float>::infinity()) { };

Ray Ray::reflect(const LocalGeo& local) const {
	Ray reflected;
	reflected.position = local.position;
	Vector normal = Vector(local.normal.x, local.normal.y, local.normal.z);
	reflected.direction = direction.reflect(normal);
	return reflected;
}