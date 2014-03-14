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
	if(!brdf.kr.black()) {
		// TODO: reflection.
	}
};

Color RayTracer::shading(const LocalGeo& local, const BRDF& brdf,
	const Point& camera, const Ray& light_ray, const Color& light_color) {
	Color color;
	Normal light_normal(light_ray.direction);
	// Diffuse.
	color += brdf.kd * light_color * fmax(0.0, local.normal.dot(light_normal));
	// Specular.
	Normal viewer = Normal(local.position - camera);
	Normal reflection = light_normal.reflect(local.normal);
	Color specular = brdf.ks * light_color * pow(fmax(0.0, viewer.dot(reflection)), brdf.sp);
	color += specular;
	return color;
}
