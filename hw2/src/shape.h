#ifndef SHAPE_H
#define SHAPE_H

class Shape {

public:

	Shape();

	bool intersect(const Ray& ray, float* t_hit, LocalGeo& local);

};

#endif