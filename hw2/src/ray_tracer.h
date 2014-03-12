#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "ray.h"
#include "color.h"

class RayTracer {

public:

	RayTracer();

	Color trace(const Ray& ray, int depth);

};

#endif