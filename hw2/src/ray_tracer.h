#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include "ray.h"
#include "color.h"

class RayTracer {

public:

	RayTracer();

	void trace(const Ray& ray, Color& color, int depth);

};

#endif