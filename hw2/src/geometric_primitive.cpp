#include "geometric_primitive.h"

GeometricPrimitive::GeometricPrimitive(Transformation& world_to_obj, Shape& shape) :
	world_to_obj(wto), shape(shape) {
	obj_to_world = world_to_obj.inverse();
};

bool GeometricPrimitive::intersect(Ray& ray, float& t_hit, Intersection& in) {
	Ray obj_ray = world_to_obj * ray;
	LocalGeo obj_local;
	float t_test;
	if(!shape.intersect(obj_ray, t_test, obj_local)) { return false; }
	t_hit = t_test;
	in.primitive = this;
	in.local = obj_to_world * obj_local;
	return true;
}

void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF& brdf) {
	material.getBRDF(local, brdf);
}