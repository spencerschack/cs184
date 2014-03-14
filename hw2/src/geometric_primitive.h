#ifndef GEOMETRIC_PRIMITIVE
#define GEOMETRIC_PRIMITIVE

#include "primitive.h"
#include "transformation.h"
#include "shape.h"
#include "ray.h"
#include "brdf.h"
#include "material.h"

class GeometricPrimitive : public Primitive {

public:

	Material material;

	Transformation obj_to_world, world_to_obj;

	Shape* shape;

	GeometricPrimitive(Transformation& obj_to_world, Shape* s, Material& material);

	bool intersect(const Ray& ray, float& t_hit, Intersection& in) const;

	bool intersect(const Ray& ray, const Primitive* ignore) const;

	void getBRDF(LocalGeo& local, BRDF& brdf) const;

	bool is_base_class = true;

};

#endif