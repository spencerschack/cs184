#include <fstream>

#include "options.h"

using namespace std;

Options::Options(char* commands) {
	ifstream file(commands);
	for(string line; getline(file, line);) {
		cout << line << "\n";
	}
	if(width == 0) {
		printf("Must specify a non-zero width.\n");
		goto fail;
	}
	if(height == 0) {
		printf("Must specify a non-zero height.\n");
		goto fail;
	}
	if(filename.empty()) {
		printf("Must specify a filename.\n");
		goto fail;
	}
	return;
	fail:
		file.close();
		exit(1);
}
