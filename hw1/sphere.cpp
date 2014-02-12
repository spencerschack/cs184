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

};