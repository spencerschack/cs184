#ifndef LIGHT_RAY_H
#define LIGHT_RAY_H

#include "ray.h"
#include "color.h"

class LightRay {

public:

	Ray ray;

	Color color;

	LightRay();

	LightRay(Ray& ray, Color& color);

};

#endif