#ifndef OPTIONS_H
#define OPTIONS_H

class Options {

private:

	int argc, index;

	char** argv;

	bool has_next();

	char* next();

public:

	Options(int argc, char* argv[]);

	char* filename;

	int width, height;

};

#endif