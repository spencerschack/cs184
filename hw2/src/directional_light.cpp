#include "directional_light.h"

DirectionalLight::DirectionalLight(float x, float y, float z, float r, float g, float g) {
	position = Point(x, y, z);
	color = Color(r, g, b);
}

void DirectionalLight::generate_ray(const LocalGeo& local, Ray& ray, Color& light) {
	light = color;
	ray.position = position;
	ray.direction = local.position - position;
}
