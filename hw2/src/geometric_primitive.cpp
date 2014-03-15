#include "geometric_primitive.h"

GeometricPrimitive::GeometricPrimitive(Transformation& obj_to_world, Shape* shape, Material& material) :
	obj_to_world(obj_to_world), shape(shape), material(material) {
	world_to_obj = obj_to_world.inverse();
};

bool GeometricPrimitive::intersect(const Ray& ray, float& t_hit, Intersection& in, const Primitive* ignore) const {
	if(this == ignore) { return false; }
	Ray obj_ray = world_to_obj * ray;
	LocalGeo obj_local;
	float t_test;
	if(!shape->intersect(obj_ray, t_test, obj_local)) { return false; }
	t_hit = t_test;
	in.primitive = this;
	in.local = obj_to_world * obj_local;
	return true;
}

bool GeometricPrimitive::intersect(const Ray& ray, const Primitive* ignore) const {
	return Primitive::intersect(ray, ignore);
}

void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF& brdf) const {
	material.getBRDF(local, brdf);
}