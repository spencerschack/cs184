#ifndef TRIANGLE_N_H
#define TRIANGLE_N_H

#include "shape.h"
#include "local_geo.h"

class TriangleN : public Shape {

	LocalGeo x, y, z;

public:

	TriangleN(LocalGeo x, LocalGeo y, LocalGeo z);

	bool intersect(Ray& ray, float& t_hit, LocalGeo& local) const;

};

#endif