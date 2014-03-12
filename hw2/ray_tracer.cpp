// Standard libraries
#include <iostream>

// Our classes
#include "src/options.cpp"
#include "src/vector.cpp"
#include "src/point.cpp"
#include "src/normal.cpp"
#include "src/color.cpp"
#include "src/ray.cpp"
#include "src/sample.cpp"
#include "src/matrix.cpp"
#include "src/film.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	Options options(argc, argv);
	cout << options.filename;
	Film film = Film(options.width, options.height);
	return 0;
}