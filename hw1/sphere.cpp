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

	void draw() {
		glBegin(GL_POINTS);

		int i,    j,
		    minI, minJ,
		    maxI, maxJ;
		float height;
		float radiusSquared = pow(radius, 2);
		Color color;

		minI = (int) floor(position.x - radius);
		maxI = (int) ceil(position.x + radius);

		for(i = minI; i < maxI; i++) {
			height = sqrt(radiusSquared - pow(i - position.x, 2));
			minJ = (int) floor(position.y - height);
			maxJ = (int)  ceil(position.y + height);
			for(j = minJ; j < maxJ; j++) {
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
				glColor3f(color.r, color.g, color.b);
				glVertex2f(i + 0.5, j + 0.5);
			}
		}

		glEnd();
	}

};