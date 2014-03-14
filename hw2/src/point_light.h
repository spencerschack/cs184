#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "light.h"
#include "ray.h"
#include "local_geo.h"

class PointLight : public Light {

public:

	PointLight(float x, float y, float z, float r, float g, float b);

	void generate_ray(const LocalGeo& local, Ray& ray, Color& color) const;

};

#endif