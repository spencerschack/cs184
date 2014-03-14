#ifndef OPTIONS_H
#define OPTIONS_H

#include <vector>

#include "primitive.h"

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

	vector<Primitive*> primitives;

	string filename;

	unsigned int width, height, maxdepth;

	float camera_position_x, camera_position_y, camera_position_z,
		camera_direction_x, camera_direction_y, camera_direction_z,
		camera_up_x, camera_up_y, camera_up_z, camera_fov_y;

	Options(char* commands_filename);

};

#endif