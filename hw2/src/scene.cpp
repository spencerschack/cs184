#include "scene.h"
#include "film.h"
#include "sampler.h"

Scene::Scene(const Options& options) : options(options) {};

int Scene::render() {
	RayTracer raytracer;
	Camera camera(options);
	Film film(options);
	Sampler sampler(options);
	Sample sample;
	Ray ray;
	Color color;
	while(sampler.generate_sample(sample)) {
		camera.generate_ray(sample, ray);
		raytracer.trace(ray, color, options.maxdepth);
		film.commit(sample, color);
	}
	return film.write_image();
};