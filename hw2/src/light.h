#ifndef LIGHT_H
#define LIGHT_H

#include "local_geo.h"
#include "light_ray.h"

class Light {

public:

	Light();

	LightRay generateRay(const LocalGeo& local);
	
};

#endif