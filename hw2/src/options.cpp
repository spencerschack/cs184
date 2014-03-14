#include <fstream>
#include <sstream>

#include "options.h"
#include "scene.h"
#include "matrix.h"
#include "transformation.h"
#include "geometric_primitive.h"
#include "sphere.h"
#include "directional_light.h"

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
	Material material;
	material.brdf.ka = Color(0.2, 0.2, 0.2);
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
			camera_position.x = parse_float();
			camera_position.y = parse_float();
			camera_position.z = parse_float();
			camera_direction.x = parse_float();
			camera_direction.y = parse_float();
			camera_direction.z = parse_float();
			camera_up.x = parse_float();
			camera_up.y = parse_float();
			camera_up.z = parse_float();
			camera_fov_y = parse_float();
		} else if(command == "sphere") {
			Matrix translate = Matrix::Translation(
				parse_float(),
				parse_float(),
				parse_float());
			Matrix scale = Matrix::Scale(parse_float());
			Matrix matrix = translate * scale;
			Transformation transformation(matrix);
			Sphere* sphere = new Sphere();
			GeometricPrimitive* primitive =
				new GeometricPrimitive(transformation, sphere, material);
			root_primitive.primitives.push_back(primitive);
		} else if(command == "diffuse") {
			material.brdf.kd.r = parse_float();
			material.brdf.kd.g = parse_float();
			material.brdf.kd.b = parse_float();
		} else if(command == "ambient") {
			material.brdf.ka.r = parse_float();
			material.brdf.ka.g = parse_float();
			material.brdf.ka.b = parse_float();
		} else if(command == "specular") {
			material.brdf.ks.r = parse_float();
			material.brdf.ks.g = parse_float();
			material.brdf.ks.b = parse_float();
		} else if(command == "shininess") {
			material.brdf.sp = parse_float();
		} else if(command == "directional") {
			Light* light = new DirectionalLight(
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float(),
				parse_float());
			lights.push_back(light);
		} else {
			cout << "Unknown command: '" << command << "'.\n";
			exit(1);
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
	commands.close();
}
