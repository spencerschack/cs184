#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "sample.h"

class Camera {

public:

	Point position;

	Vector direction, up;

	float fov;

	Camera();

	void generate_ray(const Sample& sample, Ray& ray);

};

#endif
