#include <cmath>

#include "camera.h"

Camera::Camera(const Options& options) {
	width = options.width;
	height = options.height;
	position = options.camera_position;
	Vector up = options.camera_up;
	z = options.camera_direction;
	x = z.cross(up);
	y = x.cross(z);
	// Normalize to create an orthonormal basis.
	x.normalize();
	y.normalize();
	z.normalize();
	// Assumes the view plane is 1 unit away from the camera position.
	float world_height = tan(options.camera_fov_y * M_PI / 180);
	v = y * world_height;
	u = x * (width / height * world_height);
};

void Camera::generate_ray(const Sample& sample, Ray& ray) {
	ray.direction =
		(u * (0.5 - sample.x / width)) +
		(v * (0.5 - sample.y / height)) + z;
	ray.position = position;
};