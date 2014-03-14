#ifndef SHAPE_H
#define SHAPE_H

class Shape {

public:

	Shape();

	virtual bool intersect(Ray& ray, float& t_hit, LocalGeo& local);

	void intersect(LocalGeo& local, BRDF& brdf);

};

#endif