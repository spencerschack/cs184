#include "scene.h"
#include "film.h"
#include "sampler.h"

Scene::Scene() { };

int Scene::render() {
	RayTracer raytracer;
	Film film(width, height);
	Sampler sampler(width, height);
	Sample sample;
	Ray ray;
	Color color;
	while(sampler.generate_sample(sample)) {
		camera.generate_ray(sample, ray);
		raytracer.trace(ray, color, maxdepth);
		film.commit(sample, color);
	}
	return film.write_to_file(filename);
};