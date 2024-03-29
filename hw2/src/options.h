#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include <fstream>
#include <stack>

#include "primitive.h"
#include "aggregate_primitive.h"
#include "light.h"
#include "matrix.h"
#include "point.h"
#include "local_geo.h"
#include "sphere.h"
#include "triangle.h"

using namespace std;

class Options {

private:

	ifstream commands;

	string line;

	string parse_string();

	int parse_int();

	unsigned int parse_uint();

	unsigned int parse_pint();

	float parse_float();

	void fail();

public:

	bool antialias;

	AggregatePrimitive root_primitive;

	vector<Light*> lights;

	string filename;

	std::vector<Sphere*> spheres;

	unsigned int width, height, maxdepth;

	Point camera_position, camera_direction;

	Vector camera_up;

	float camera_fov_y;

	Options(char* commands_filename);
};

#endif