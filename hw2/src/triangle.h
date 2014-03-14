#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape {

public:

	Point v1, v2, v3;

	LocalGeo l1, l2, l3;

	Triangle(Point v1, Point v2, Point v3);

	Triangle(LocalGeo l1, LocalGeo l2, LocalGeo l3);

	bool intersect(Ray& ray, float& t_hit, LocalGeo& local) const;

};

#endif
