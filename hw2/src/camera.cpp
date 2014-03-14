#include <cmath>

#include "camera.h"

Camera::Camera(const Options& options) {
	width = options.width;
	height = options.height;
	position = options.camera_position;
	Vector up = options.camera_up;
	z = options.camera_direction;
	x = up.cross(z);
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
		// Subtract 0.5 to center the view plane and the sampler.
		(v * (sample.x / width - 0.5)) +
		// Must subtract ratio from 0.5 because sample coordinates have the
		// origin in the upper left and the world coordinats have it in the
		// center.
		(u * (0.5 - sample.y / height)) +
		// Add the camera's direction to the view plane to move it 1 unit away
		// along the z-axis;
		z;
	ray.position = position;
};