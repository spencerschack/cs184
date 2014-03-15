#include <cmath>

#include "camera.h"

Camera::Camera(const Options& options) {
	width = options.width;
	height = options.height;
	position = options.camera_position;
	Vector up = options.camera_up;
	z = options.camera_direction - options.camera_position;
	x = z.cross(up);
	y = x.cross(z);
	// Normalize to create an orthonormal basis.
	x.normalize();
	y.normalize();
	z.normalize();
	float world_height = tan(options.camera_fov_y * M_PI / 360);
	v = y * world_height;
	u = x * (width / height * world_height);
};

void Camera::generate_ray(const Sample& sample, Ray& ray) {
	ray.direction =
		(u * (2.0 * sample.x / width - 1.0)) +
		(v * (1.0 -  2.0 * sample.y / height)) + z;
	ray.position = position;
};