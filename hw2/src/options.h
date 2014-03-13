#ifndef OPTIONS_H
#define OPTIONS_H

#include "vector.h"
#include "point.h"

using namespace std;

class Options {

private:

public:

	Options(char* commands);

	string filename;

	unsigned int width, height;

	// Camera.
	Point camera_position;
	Vector camera_direction, camera_up;

};

#endif