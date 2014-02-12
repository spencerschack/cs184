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

	void draw(void (*setPixel)(int, int, float, float, float)) {
		glBegin(GL_POINTS);

		int i,    j,
		    minI, minJ,
		    maxI, maxJ;
		float radiusSquared = sqr(radius);
		Color color;

		minI = (int) floor(position.x - radius);
		maxI = (int) ceil(position.x + radius);

		for (i = minI; i < maxI; i++) {
			maxJ = (int) ceil(sqrt(radiusSquared - sqr(i - position.x)) + position.x);
			minJ = 2 * position.x - maxJ;
			for (j = minJ; j < maxJ; j++) {
				color = Color(ambientColor);
				/*
				for(k = 0; k < numPointLights; k++) {
					color += pointLights[k]->at(x, y);
				}
				for(k = 0; k < numDirectionalLights; k++) {
					color += directionalLights[k]->at(x, y);
				}
				setPixel(i, j, color.r, color.g, color.b);
				*/
				setPixel(i, j, color.r, color.g, color.b);
			}
		}

		glEnd();
	}

};