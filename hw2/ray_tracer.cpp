// Standard libraries
#include <iostream>

// Our classes
#include "src/options.cpp"
#include "src/vector.cpp"
#include "src/normal.cpp"
#include "src/ray.cpp"
#include "src/matrix.cpp"

using namespace std;

int main(int argc, char* argv[]) {
	Options options = Options::parse(argc, argv);
	cout << options.filename;
	return 0;
}