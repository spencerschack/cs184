#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "light.h"
#include "color.h"
#include "point.h"

class DirectionalLight : public Light {

public:

	Color color;

	Point position;

	DirectionalLight(float x, float y, float z, float r, float g, float b);

	void generate_ray(const LocalGeo& local, Ray& ray, Color& color) const;

};

#endif