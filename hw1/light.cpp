#include <cmath>

class Light {

public:

	Vector position;
	Color color;

	Light(float x, float y, float z, float r, float g, float b) {
		position = Vector(x, y, z);
		color = Color(r, g, b);
	}

};