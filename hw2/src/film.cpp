#include "film.h"

using namespace std;

Film::Film(int width, int height) : width(width), height(height) {
	film = vector<Color>(height * width);
};

// ATTENTION: the following method is not bound-checked, if you attempt to write
// of the end of film, the program may SEGFAULT.
void Film::commit(Sample sample, Color color) {
	film[sample.y * width + sample.x] = color;
}

void Film::writeToFile(char* filename) {
	printf("Film::writeToFile has not been implemented.\n");
	exit(1);
}
