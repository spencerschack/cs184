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

	float parse_float();

	void fail();

public:

	AggregatePrimitive root_primitive;

	vector<Light*> lights;

	string filename;

	std::vector<Triangle*> triangles;

	std::vector<Triangle*> trianglesN;

	std::vector<Sphere*> spheres;

	unsigned int width, height, maxdepth, maxvertex = 0, maxvertexnormal = 0;

	Point camera_position;

	Vector camera_direction, camera_up;

	float camera_fov_y;

	Options(char* commands_filename);

	float im[16] = {1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1};

	bool push = false;
};

#endif