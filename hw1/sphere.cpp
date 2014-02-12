class Sphere {

public:

	Vector position;
	float radius;

	Color ambientColor;
	Color diffuseColor;
	Color specularColor;
	float specularPower;

	Sphere() { }

	Sphere(float x, float y, float z, float r) : radius(r) {
		position = Vector(x, y, z);
	}

	Vector* normal(Vector* vector) {
		return (vector - position).normalize();
	}

	Vector* intersect(Ray ray) {
		float a = ray.direction.dot(&ray.direction);
		float b = 2 * ray.direction.dot(&ray.position);
		float c = ray.position.dot(&ray.position) - pow(radius, 2);
		float discriminant = pow(b, 2) - 4 * a * c;
		if(discriminant < 0) return NULL;
		discriminant = sqrt(discriminant);
		float q = (b < 0 ? -b - discriminant : -b + discriminant) / 2.0;
		float t0 = q / a;
		float t1 = c / q;
		if(t0 > t1) {
			float tmp = t0;
			t0 = t1;
			t1 = tmp;
		}
		if(t1 < 0) return NULL;
		float t = t0 < 0 ? t1 : t0;
		return ray.position + ray.direction * t;
	}

};