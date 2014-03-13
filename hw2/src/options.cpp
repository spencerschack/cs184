#include <fstream>

#include "options.h"
#include "scene.h"

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

Options::Options(char* commands_filename, Scene& scene) {
	ifstream commands(commands_filename);
	while(getline(commands, line)) {
		if(line.empty() || line[0] == '#') { continue; }
		string command = parse_string();
		if(command == "size") {
			scene.width = parse_uint();
			scene.height = parse_uint();
		} else if(command == "maxdepth") {
			scene.maxdepth = parse_uint();
		} else if(command == "output") {
			scene.filename = parse_string();
		} else if(command == "camera") {
			scene.camera.position.x = parse_float();
			scene.camera.position.y = parse_float();
			scene.camera.position.z = parse_float();
			scene.camera.direction.x = parse_float();
			scene.camera.direction.y = parse_float();
			scene.camera.direction.z = parse_float();
			scene.camera.up.x = parse_float();
			scene.camera.up.y = parse_float();
			scene.camera.up.z = parse_float();
			scene.camera.fov = parse_float();
		} else if(command == "sphere") {

		}
	}
	if(scene.width == 0) {
		printf("Must specify a non-zero width, got: '%d'.\n", scene.width);
		fail();
	}
	if(scene.height == 0) {
		printf("Must specify a non-zero height, got: '%d'.\n", scene.height);
		fail();
	}
	if(scene.filename.empty()) {
		printf("Must specify a filename.\n");
		fail();
	}
	commands.close();
}
