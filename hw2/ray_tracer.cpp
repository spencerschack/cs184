// Standard libraries
#include <iostream>

// Our classes
#include "lib/options.cpp"
#include "lib/vector.cpp"
#include "lib/normal.cpp"

using namespace Eigen;
using namespace std;

int main(int argc, char* argv[]) {
	Options options = Options::parse(argc, argv);
	cout << options.filename;
	return 0;
}