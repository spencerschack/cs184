#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "sample.h"

class Camera {

public:

	Point position;

	Vector direction, up;

	Camera(Point position, Vector direction, Vector up);

	void generate_ray(const Sample& sample, Ray& ray);

};

#endif
