#include "camera.h"

Camera::Camera(Point position, Vector direction, Vector up) :
	position(position), direction(direction), up(up) { };

void Camera::generate_ray(const Sample& sample, Ray& ray) {
	printf("Camera::generate_ray is not implemented.\n");
	exit(1);
};