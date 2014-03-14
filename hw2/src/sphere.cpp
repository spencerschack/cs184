#include <cmath>

class Sphere : public Shape {

public:
	Point center;

	Sphere(Point p) {
		center = p;
	}

    // Returns intersection point and normal to it if given ray intersects the sphere
	// Need to implement "Intersection with ray at t outside range [t_min, t_max] should return false"
	bool Sphere::intersect(const Ray& ray, float* t_hit, LocalGeo& local) {
		float a = ray.direction.dot(&ray.direction);
		float b = 2 * ray.direction.dot(&ray.position);
		float c = ray.position.dot(&ray.position) - 1; // - radius ^ 2
		float discriminant = pow(b, 2) - 4 * a * c;
		if(discriminant < 0) return false;
		discriminant = sqrt(discriminant);
		float q = (b < 0 ? -b - discriminant : -b + discriminant) / 2.0;
		float t0 = q / a;
		float t1 = c / q;
		if(t0 > t1) {
			float tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if(t1 < 0) return false;
		float t = t0 < 0 ? t1 : t0;
		t_hit = t0;
		// Store in LocalGeo
		local = new LocalGeo(ray.position, new normal(ray.position + (*ray.direction.vector() * t));
		return true;
//		return ray.position + (*ray.direction.vector() * t);
	}
}