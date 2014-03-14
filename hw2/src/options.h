#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>
#include <fstream>

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

	vector<Light*> lights;

	string filename;

	unsigned int width, height, maxdepth = 5;

	Point camera_position;

	Vector camera_direction, camera_up;

	float camera_fov_y;

	Options(char* commands_filename);

};

#endif