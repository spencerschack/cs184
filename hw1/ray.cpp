#include <cmath>

class Ray {

public:

	Vector position;
	Normal direction;
	float t_min, t_max;

	Ray() { }
	Ray(Vector p, Normal d) : position(p), direction(d) { }
	Ray(Vector p, Normal d, float t_min, float t_max) : position(p), direction(d), t_min(t_min), t_max(t_max) { }

};