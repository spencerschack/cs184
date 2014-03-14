#include "sample.h"

Sample::Sample() : x(0), y(0) { };

Sample::Sample(float x, float y) : x(x), y(y) { };

void Sample::print() {
	printf("Sample<x: %f, y: %f>\n", x, y);
}