#include "ray.h"
#include "vector.h"

Ray::Ray() { };

Ray::Ray(Point& position, Vector& direction) :
	position(position), direction(direction) { };

Ray::Ray(Point& position, Vector& direction, float t_min, float t_max) :
	position(position), direction(direction), t_min(t_min), t_max(t_max) { };

Ray Ray::reflect(const LocalGeo& local) const {
	Ray reflected;
	reflected.position = local.position;
	Vector normal = Vector(local.normal.x, local.normal.y, local.normal.z);
	reflected.direction = direction.reflect(normal);
	return reflected;
}