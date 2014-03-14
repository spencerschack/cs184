#include <cmath>

#include "ray_tracer.h"

RayTracer::RayTracer() { };

void RayTracer::trace(const Ray& ray, Color& color, unsigned int depth) {
	if(depth == 0) { return; }
	Vector dir = ray.direction;
	if(sqrt(dir.x * dir.x + dir.y * dir.y) < 0.05) {
		color.r = 1.0;
	}
};
