#include <cmath>

class Ray {

public:

	Vector position, direction;
	float t_min, t_max;

	Ray() { }
	Ray(Vector p, Vector d) : position(p), direction(d) { }
	Ray(Vector p, Vector d, float t_min, float t_max) : position(p), direction(d), t_min(t_min), t_max(t_max) { }

};