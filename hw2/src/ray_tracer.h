#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "ray.h"
#include "color.h"
#include "aggregate_primitive.h"

class RayTracer {

public:

	RayTracer();

	void trace(const Options& options, const Ray& ray, Color& color, unsigned int depth);

};

#endif