#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

class Sphere : public Shape {

public:

	bool intersect(Ray& ray, float& t_hit, LocalGeo& local);

};

#endif