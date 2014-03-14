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

	GeometricPrimitive(Transformation& world_to_obj, Shape* s);

	bool intersect(const Ray& ray, float& t_hit, Intersection& in) const;

	void getBRDF(LocalGeo& local, BRDF& brdf) const;

};

#endif