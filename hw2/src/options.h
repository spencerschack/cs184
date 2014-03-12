#ifndef OPTIONS_H
#define OPTIONS_H

class Options {

private:

	int argc, index;

	char** argv;

public:

	Options(int argc, char* argv[]);

	char* next(bool skipAssert = false);

	char* filename;

	int width, height;

};

#endif