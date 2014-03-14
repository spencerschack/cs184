#include "ray_tracer.h"
#include "light.h"

RayTracer::RayTracer() { };

void RayTracer::trace(const Options& options, const Ray& ray, Color& color, unsigned int depth) {
	color.reset();
	if(depth == 0) { return; }
	float t_hit;
	Intersection in;
	const AggregatePrimitive& primitive = options.root_primitive;
	if(!primitive.intersect(ray, t_hit, in)) { return; }
	BRDF brdf;
	in.primitive->getBRDF(in.local, brdf);
	const vector<Light>& lights = options.lights;
	int len = lights.size(), i;
	for(i = 0; i < len; i++) {

	}
};
