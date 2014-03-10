// Standard libraries
#include <stdio.h>

// Third-party libraries
#include "vendor/Eigen/Eigen"

// Our classes
#include "lib/options_parser.cpp"

using namespace Eigen;
using namespace std;

int main(int argc, char* argv[]) {
	parse_options(argc, argv);
	return 0;
}