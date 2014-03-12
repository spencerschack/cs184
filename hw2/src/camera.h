#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "sample.h"

class Camera {

public:

	Camera();

	Ray generateRay(const Sample& sample);

};

#endif
