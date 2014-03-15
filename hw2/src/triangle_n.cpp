#include "triangle_n.h"

TriangleN::TriangleN(LocalGeo x, LocalGeo y, LocalGeo z) : x(x), y(y), z(z) { };

bool TriangleN::intersect(Ray& ray, float& t_hit, LocalGeo& local) const {
	Vector edge1, edge2, edge3, pvec, qvec, tvec, pointOfInt, normal;
	float det, inv_det, t, u, v, c1, c2, c3;
	Normal n1, n2, n3;
	edge1 = Vector(y.position.x - x.position.x, y.position.y - x.position.y, y.position.z - x.position.z);
	edge2 = Vector(z.position.x - x.position.x, z.position.y - x.position.y, z.position.z - x.position.z);
	pvec = ray.direction.cross(edge2);
	det = edge1.dot(pvec);
	if(fabs(det) < 0.00001) { return false; }
	inv_det = 1.0 / det;
	tvec = ray.position - x.position;
	u = tvec.dot(pvec) * inv_det;
	if(u < 0.0 || u > 1.0) { return false; }
	qvec = tvec.cross(edge1);
	v = ray.direction.dot(qvec) * inv_det;
	if(v < 0.0 || u + v > 1.0) { return false; }
	t = edge2.dot(qvec) * inv_det;
	if(t < ray.t_min || t > ray.t_max) { return false; }
	t_hit = t;
	local.position = ray.position + ray.direction * t_hit;
	local.normal = (x.normal * (1.0 - u - v)) + (y.normal * u) + (z.normal * v);
	return true;
}