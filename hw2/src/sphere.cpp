#include <cmath>
#include <float.h>

#include "sphere.h"

// Returns intersection point and normal to it if given ray intersects the sphere
bool Sphere::intersect(Ray& ray, float& t_hit, LocalGeo& local) const {
	// ray.position is a Point, but this formula treats it as a vector.
	Vector ray_position = Vector(ray.position.x, ray.position.y, ray.position.z);
	float a = ray.direction.dot(ray.direction);
	float b = 2.0 * ray.direction.dot(ray_position);
	float c = ray_position.dot(ray_position) - 1.0; // - radius ^ 2
	float discriminant = pow(b, 2.0) - 4.0 * a * c;
	if(discriminant < FLT_EPSILON) { return false; }
	discriminant = sqrt(discriminant);
	float q = (b < 0.0 ? -b - discriminant : -b + discriminant) / 2.0;
	float t0 = q / a;
	float t1 = c / q;
	if(t0 > t1) {
		float tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	if(t1 < FLT_EPSILON) { return false; }
	t0 = t0 < 0.0 ? t1 : t0;
	if(t0 > ray.t_max || t0 < ray.t_min) { return false; }
	t_hit = t0;
	local.position = ray.position + ray.direction * t_hit;
	// Because all spheres are radius 1 positioned at (0,0,0), the normal at
	// the intersection can be calculated by simply normalizing the
	// intersection position.
	local.normal = Normal(local.position.x, local.position.y, local.position.z);
	return true;
};