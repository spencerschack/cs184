#ifndef OPTIONS_H
#define OPTIONS_H

#include "scene.h"

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

	Options(char* commands, Scene& scene);

};

#endif