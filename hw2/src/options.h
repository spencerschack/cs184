#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include <fstream>
#include <stack>

#include "primitive.h"
#include "aggregate_primitive.h"
#include "light.h"

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

	vector<Light> lights;

	string filename;

	std::stack<Matrix> transformStack;

	std::vector<Point> v;

	std::vector<LocalGeo> vn;

	std::vector<Triangle> triangles;

	std::vector<Triangle> trianglesN;

	stf::vector<Sphere> spheres;

	unsigned int width, height, maxdepth, maxvertex = 0, maxvertexnormal = 0;

	float camera_position_x, camera_position_y, camera_position_z,
		camera_direction_x, camera_direction_y, camera_direction_z,
		camera_up_x, camera_up_y, camera_up_z, camera_fov_y;

	Options(char* commands_filename);

	float im[16] = {1,0,0,0,0,1,0,1,0,0,1,0,0,0,0,1};
	Matrix identity = new Matrix(im);
	transformStack.push(identity);
};

#endif