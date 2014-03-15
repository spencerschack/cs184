#include <cmath>

#include "triangle.h"

// Vertexes are ALWAYS in teh counter clockwise direction
Triangle::Triangle(Point v1, Point v2, Point v3) : v1(v1), v2(v2), v3(v3) { };
Triangle::Triangle(LocalGeo l1, LocalGeo l2, LocalGeo l3) : l1(l1), l2(l2), l3(l3) {
	printf("Check this implementation!");
};

// Returns intersection point and normal to it if given ray intersects the sphere
// Need to implement "Intersection with ray at t outside range [t_min, t_max] should return false"
bool Triangle::intersect(Ray& ray, float& t_hit, LocalGeo& local) const {
	Vector edge1, edge2, edge3, pvec, qvec, tvec, pointOfInt, normal;
	float det, inv_det, t, u, v, c1, c2, c3;
	edge1 = Vector(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	edge2 = Vector(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
	pvec = ray.direction.cross(edge2);
	det = edge1.dot(pvec);
	if(fabs(det) < 0.00001) { return false; }
	inv_det = 1.0 / det;
	tvec = ray.position - v1;
	u = tvec.dot(pvec) * inv_det;
	if(u < 0.0 || u > 1.0) { return false; }
	qvec = tvec.cross(edge1);
	v = ray.direction.dot(qvec) * inv_det;
	if(v < 0.0 || u + v > 1.0) { return false; }
	t = edge2.dot(qvec) * inv_det;
	if(t < ray.t_min || t > ray.t_max) { return false; }
	t_hit = t;
	local.position = ray.position + ray.direction * t_hit;
	local.normal = Normal(edge1.cross(edge2));
	return true;
}
