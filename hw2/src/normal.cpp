#include "normal.h"
#include "vector.h"

Normal::Normal(Vector* v) : Vector(v) {
	normalize();
};

void Normal::normalize() {
	float mag = magnitude();
	if(mag == 0) { return; }
	x /= mag;
	y /= mag;
	z /= mag;
}