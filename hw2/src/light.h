#ifndef LIGHT_H
#define LIGHT_H

#include "local_geo.h"
#include "light_ray.h"

class Light {

public:

	Light();

	virtual void generate_ray(const LocalGeo& local, Ray& ray, Color& color) const = 0;
	
};

#endif