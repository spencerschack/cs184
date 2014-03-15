#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "point.h"
#include "ray.h"
#include "color.h"
#include "aggregate_primitive.h"

class RayTracer {

public:

	RayTracer();

	void trace(const Options& options, const Ray& ray, Color& color, unsigned int depth);

	void trace(const Options& options, const Ray& ray, Color& color, unsigned int depth, const Primitive* ignore);

	Color shading(const LocalGeo& local, const BRDF& brdf, const Point& camera,
		const Ray& light_ray, const Color& light_color);

};

#endif