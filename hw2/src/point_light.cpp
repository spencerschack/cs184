#include "point_light.h"

PointLight::PointLight(float x, float y, float z, float r, float g, float b) {
	position = Point(x, y, z);
	color = Color(r, g, b);
}

void PointLight::generate_ray(const LocalGeo& local, Ray& ray, Color& light) const {
	light = color;
	ray.position = local.position;
	ray.direction = local.position - position;
}
