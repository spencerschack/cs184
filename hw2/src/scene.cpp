#include "scene.h"
#include "film.h"
#include "sampler.h"

Scene::Scene(Options options) : options(options) { };

int Scene::render() {
	RayTracer raytracer;
	Camera camera(options.camera_position, options.camera_direction, options.camera_up);
	Film film(options.width, options.height);
	Sampler sampler(options.width, options.height);
	Sample sample;
	Ray ray;
	Color color;
	while(sampler.generate_sample(sample)) {
		camera.generate_ray(sample, ray);
		raytracer.trace(ray, color);
		film.commit(sample, color);
	}
	return film.write_to_file(options.filename);
};