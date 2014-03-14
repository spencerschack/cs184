#include "../lib/lodepng/lodepng.h"
#include "../lib/lodepng/lodepng.cpp"

using namespace std;
using namespace lodepng;

Film::Film(const Options& options) :
	width(options.width), height(options.height), filename(options.filename) {
	film = vector<Color>(height * width);
};

void Film::commit(const Sample& sample, const Color& color) {
	int x = (int) sample.x, y = (int) sample.y;
	film.at(y * width + x) = color;
}

int Film::write_image() {
	int length = width * height, i;
	unsigned char image[3 * length];
	Color color;
	for(i = 0; i < length; i++) {
		color = film[i];
		image[(3 * i) + 0] = 255 * fmin(1.0, fmax(0.0, color.r));
		image[(3 * i) + 1] = 255 * fmin(1.0, fmax(0.0, color.g));
		image[(3 * i) + 2] = 255 * fmin(1.0, fmax(0.0, color.b));
	}
	return encode(filename, image, width, height, LCT_RGB);
}
