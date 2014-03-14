#include <cmath>
#include <cfloat>

#include "triangle.h"

Triangle::Triangle(Point v1, Point v2, Point v3) : v1(v1), v2(v2), v3(v3) { };

// Returns intersection point and normal to it if given ray intersects the sphere
// Need to implement "Intersection with ray at t outside range [t_min, t_max] should return false"
bool Triangle::intersect(Ray& ray, float& t_hit, LocalGeo& local) {
	Vector edge1, edge2, edge3, pvec, qvec, tvec, pointOfInt, normal;
	float det, inv_det, t, u, v, c1, c2, c3;
	edge1 = Vector(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	edge2 = Vector(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
	pvec = ray.direction.cross(edge2);
	det = edge1.dot(pvec);
	if(fabs(det) < FLT_EPSILON) { return false; }
	inv_det = 1.0 / det;
	tvec = ray.position - v1;
	u = tvec.dot(pvec) * inv_det;
	if(u < 0.0 || u > det) { return false; }
	qvec = tvec.cross(edge1);
	v = ray.direction.dot(qvec) * inv_det;
	if(v < 0.0 || u + v > 1.0) { return false; }
	t_hit = edge2.dot(qvec) * inv_det;
	local.position = ray.position + ray.direction * t_hit;
	local.normal = Normal(edge1.cross(edge2));
	return true;
}