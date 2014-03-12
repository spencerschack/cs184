#include "light_ray.h"

LightRay::LightRay() { };

LightRay::LightRay(Ray& ray, Color& color) : ray(ray), color(color) { };