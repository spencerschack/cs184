#include "ray_tracer.h"
#include "light.h"

RayTracer::RayTracer() { };

void RayTracer::trace(const Options& options, const Ray& ray, Color& color, unsigned int depth) {
	trace(options, ray, color, depth, NULL);
}

void RayTracer::trace(const Options& options, const Ray& ray, Color& color, unsigned int depth, const Primitive* ignore) {
	color.reset();
	float t_hit;
	Intersection in;
	const AggregatePrimitive& primitive = options.root_primitive;
	if(!primitive.intersect(ray, t_hit, in, ignore)) { return; }
	BRDF brdf;
	in.primitive->getBRDF(in.local, brdf);
	// Material ambient light.
	color += brdf.ka;
	// Material emissive light.
	color += brdf.ke;
	const vector<Light*>& lights = options.lights;
	Ray light_ray;
	Color light_color;
	int len = lights.size(), i;
	for(i = 0; i < len; i++) {
		lights[i]->generate_ray(in.local, light_ray, light_color);
		if(!primitive.intersect(light_ray, in.primitive)) {
			color += shading(in.local, brdf, options.camera_position, light_ray, light_color);
		}
	}
	if(!brdf.kr.black() && depth > 1) {
		Ray reflected_ray = ray.reflect(in.local);
		Color reflected_color;
		// Pass in.primitive to stop self reflection.
		trace(options, reflected_ray, reflected_color, depth - 1, in.primitive);
		color += brdf.kr * reflected_color;
	}
};

Color RayTracer::shading(const LocalGeo& local, const BRDF& brdf,
	const Point& camera, const Ray& light_ray, const Color& light_color) {
	Color color;
	Normal light_normal(light_ray.direction);
	// Diffuse.
	float diffuse_dot = local.normal.dot(light_normal);
	color += brdf.kd * light_color * fmax(0.0, diffuse_dot);
	// Specular.
	// Only include if the dot product of the diffuse term is positive.
	if(diffuse_dot > 0) {
		Normal viewer = Normal(camera - local.position);
		Normal reflection = light_normal.reflect(local.normal);
		Color specular = brdf.ks * light_color * pow(fmax(0.0, viewer.dot(reflection)), brdf.sp);
		color += specular;
	}
	return color;
}
