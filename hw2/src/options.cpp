#include <fstream>
#include <sstream>

#include "options.h"
#include "scene.h"
#include "matrix.h"
#include "transformation.h"
#include "geometric_primitive.h"
#include "sphere.h"

using namespace std;

string Options::parse_string() {
	if(line.empty()) {
		printf("Not enough arguments.\n");
		fail();
	}
	unsigned int index = line.find(' ');
	if(index == -1) { index = line.length(); }
	string str = line.substr(0, index);
	if(index < line.length()) {
		line = line.substr(index + 1);
	}
	return str;
}

int Options::parse_int() {
	return atoi(parse_string().c_str());
}

unsigned int Options::parse_uint() {
	int n = parse_int();
	if(n < 0) {
		printf("Expected positive number, got: '%d'\n.", n);
		fail();
	}
	return (unsigned int) n;
}

float Options::parse_float() {
	return atof(parse_string().c_str());
}

void Options::fail() {
	commands.close();
	exit(1);
}

Options::Options(char* commands_filename) {
	ifstream commands(commands_filename);
	while(getline(commands, line)) {
		if(line.empty() || line[0] == '#') { continue; }
		string command = parse_string();
		if(command == "size") {
			width = parse_uint();
			height = parse_uint();
		} else if(command == "maxdepth") {
			maxdepth = parse_uint();
		} else if(command == "output") {
			filename = parse_string();
		} else if(command == "camera") {
			camera_position_x = parse_float();
			camera_position_y = parse_float();
			camera_position_z = parse_float();
			camera_direction_x = parse_float();
			camera_direction_y = parse_float();
			camera_direction_z = parse_float();
			camera_up_x = parse_float();
			camera_up_y = parse_float();
			camera_up_z = parse_float();
			camera_fov_y = parse_float();
		} else if(command == "sphere") {
			Matrix translate = Matrix::Translation(
				parse_float(),
				parse_float(),
				parse_float());
			Matrix scale = Matrix::Scale(parse_float());
			Matrix matrix = translate * scale;
			Transformation transformation(matrix);
			Sphere sphere;
			GeometricPrimitive* primitive = new GeometricPrimitive(transformation, sphere);
			root_primitive.primitives.push_back(primitive);
		}
	}
	if(width == 0) {
		printf("Must specify a non-zero width, got: '%d'.\n", width);
		fail();
	}
	if(height == 0) {
		printf("Must specify a non-zero height, got: '%d'.\n", height);
		fail();
	}
	if(filename.empty()) {
		printf("Must specify a filename.\n");
		fail();
	}
	if(maxdepth == 0) { maxdepth = 5; }
	commands.close();
}
