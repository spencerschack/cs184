#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "point.h"
#include "normal.h"
#include "ray.h"
#include "sample.h"
#include "options.h"

class Camera {

private:

	float width, height;

	Point position;

	Vector x, y, z;

	Vector u, v;

public:

	Camera(const Options& options);

	void generate_ray(const Sample& sample, Ray& ray);

};

#endif
